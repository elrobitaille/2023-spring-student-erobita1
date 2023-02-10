//8BF0CD

#include <stdio.h>

int main() {
    int MAX_DENOMINATIONS = 0, coin_value = 0, value_amount = 0, mult_value = 0, loop_check = 0, array_check = 0;
    int dummy_variable = 1;
    double total_value = 0.0; 
    char coin_letter, first_command, second_command = '\0';

    /* Gathers information on how many "denominations" or coins there are. */
    printf("How many denominations? ");
    int num_denomination = scanf("%d", &MAX_DENOMINATIONS);

    if (num_denomination != 1 || MAX_DENOMINATIONS < 0 || MAX_DENOMINATIONS > 20) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Setting array size to be the maximum denominations. */
    char identifiers[MAX_DENOMINATIONS];
    int values[MAX_DENOMINATIONS];
    int coin_multiplier[MAX_DENOMINATIONS];

    for (int i = 0; i < MAX_DENOMINATIONS; i++) {
        /* Initializes all of the arrays and gathers the currency and their values. */
        printf("Enter coin identifier and value in cents: ");
        int read_input = scanf(" %c %d", &coin_letter, &coin_value); 

        if (read_input != 2) {
            loop_check = 1;
            array_check = 0; //Leads to "Invalid input" when length of read_input is invalid, like in d frotz. 
        } else { 
            array_check = 1; //Leads to "Invalid command when length of read_input is valid"
        }
        identifiers[i] = coin_letter;
        values[i] = coin_value;
        coin_multiplier[i] = 0;
    }

    while (dummy_variable) {
        /* Continuously prompts for a new command whenever input or command is valid. 
        Note that loop_check and dummy_variable are constantly set to 0 through out the code
        to ensure that the while loop and print statement of "Enter a command" do not excessively run. */ 
        if (loop_check == 0) {
            printf("Enter a command: ");
        }

        int user_input = scanf(" %c", &first_command);
        
        /* Scans if first user input value is valid. */
        if (user_input == 1) {
            if (first_command == 's') {
                printf("Identifier,Face Value,Count,Total Value\n");

                /* Prints out the coin identifiers, their values, and the total cost. */
                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    mult_value = values[i] * coin_multiplier[i];
                    printf("%c,%d,%d,%d\n", identifiers[i], values[i], coin_multiplier[i], mult_value); 
                    total_value += (double) mult_value / 100.0;
                }

                printf("Overall value of collection: $%.2lf\n", total_value); //Prints the total value of the collection. 
                continue;

            } else if (first_command == 'q') {
                /* Quits the program and prints "Bye!" if the user inputs quit button q. */
                printf("Bye!\n");
                dummy_variable = 0;
                break;
            }

            /* Grabs the commands a or r, which add or remove coins values. */
            if (first_command == 'a' || first_command == 'r') {
                int new_input = scanf(" %c %d", &second_command, &value_amount); 

                /* Checks through each identifier to see if the second command is a valid identifier.*/
                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    if (identifiers[i] == second_command) {
                        /* Sets array_check to 1 if the identifier is valid and is in array identifiers, else set 0. */
                        array_check = 1; 
                        break;
                    } else {
                        array_check = 0;
                    }
                }

                if (array_check == 0 && new_input == 2) {
                    /* Checks if there is too litle or too many inputs and makes sure input is correctly sized. */
                    fprintf(stderr, "Unknown coin identifier\n");  
                    dummy_variable = 0;
                    return 2;
                }

                /* This for loop iterates through the coins and adds ()'a') or removes ('r') the amount indicated to the total value. */
                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    if (first_command == 'a') {
                        if (identifiers[i] == second_command) {
                            coin_multiplier[i] += value_amount;
                            break;
                        }
                    } else if (first_command == 'r') {
                        if (identifiers[i] == second_command) {
                            coin_multiplier[i] -= value_amount;
                            break;
                        }
                    }
                }

                /* Checks if there is too litle or too many inputs.*/
                if (new_input != 2) {
                    fprintf(stderr, "Invalid input\n");  
                    dummy_variable = 0;
                    return 1;
                }
                continue;

            } else {
                /* Array_check will changed based on if invalid input (return 1) or invalid command (return 3) case is needed. 
                If array_check is 1, then exit code 3 is needed, else exit code 1. */
                if (array_check) {
                    fprintf(stderr, "Invalid command\n");
                    dummy_variable = 0;
                    return 3;  
                } else {
                    loop_check = 1;
                    dummy_variable = 0;
                    fprintf(stderr, "Invalid input\n");
                    return 1; 
                }
            }
        } else {
            /* Exits code and says bye. */
            printf("Bye!\n");
            dummy_variable = 0;
            break;
        }
    }

    return 0; //Code successfuly ran with no errors. 
}
