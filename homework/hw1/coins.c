//8BF0CD

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int MAX_DENOMINATIONS, coin_value, value_amount, mult_value, array_check, loop_check = 0;
    int dummy_variable = 1;
    double total_value = 0.0; 
    char coin_letter, first_command, second_command = '\0';

    /* Gathers information on how many "denominations" or coins there are. */
    printf("How many denominations? ");
    int num_denomination = scanf("%d", &MAX_DENOMINATIONS);

    if (num_denomination != 1 || MAX_DENOMINATIONS < 0) {
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
        scanf(" %c %d", &coin_letter, &coin_value); 
        identifiers[i] = coin_letter;
        values[i] = coin_value;
        coin_multiplier[i] = 0;
    }

    while (dummy_variable == 1) {
        /* Continuously prompts for a new command whenever input or command is valid. */
        if (loop_check != 1) {
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
            } 
            /* Quits the program and prints "Bye!" if the user inputs quit button q. */
            else if (first_command == 'q') {
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
                        array_check = 1;
                        break;
                    }
                    else {
                        array_check = 0;
                    }
                }

                if (array_check == 0) {
                    fprintf(stderr, "Unknown coin identifier\n");  // Checks if there is too litle or too many inputs.
                    dummy_variable = 0;
                    return 2;
                }

                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    if (first_command == 'a') {
                        if (identifiers[i] == second_command) {
                            coin_multiplier[i] += value_amount;
                            break;
                        }
                    }
                    else if (first_command == 'r') {
                        if (identifiers[i] == second_command) {
                            coin_multiplier[i] -= value_amount;
                            break;
                        }
                    }
                }

                if (new_input != 2) {
                    fprintf(stderr, "Invalid input\n");  // Checks if there is too litle or too many inputs.
                    dummy_variable = 0;
                    return 1;
                }
                continue;
            }
            else {
                if (array_check) {
                    fprintf(stderr, "Invalid command\n");
                    dummy_variable = 0;
                    return 3;  
                }
                else  {
                    loop_check = 1;
                    dummy_variable = 0;
                    fprintf(stderr, "Invalid input3\n");
                    //printf("%d", user_input);
                    return 1; 
                }
            }
        }
        else {
            printf("Bye!\n");
            dummy_variable = 0;
            break;
        }
    }

    return 0; //Code successfuly ran with no errors. 
}
