//8BF0CD

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int MAX_DENOMINATIONS, coin_value, value_amount, cent_value, loop_check, mult_value, array_check, reach_check = 0;
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
    char command_chars[] = {'a', 'r', 's', 'q'};
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

    while (dummy_variable) {
        if (!loop_check) {
            printf("Enter a command: ");
        }
        
        loop_check = 1; // Makes it so that "Enter a command: " does not print too many times.

        int user_input = scanf(" %c", &first_command);
        
        /* Scans if first user input value is valid. */
        if (user_input == 1) {
            if (first_command == 's') {
                printf("Identifier,Face Value,Count,Total Value\n");

                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    mult_value = values[i] * coin_multiplier[i];
                    printf("%c,%d,%d,%d\n", identifiers[i], values[i], coin_multiplier[i], mult_value); 
                    total_value += (double) mult_value / 100.0;
                }

                printf("Overall value of collection: $%.2lf\n", total_value); //Prints the total value of the collection. 
                loop_check = 0;
                continue;
            } 
            else if (first_command == 'q') {
                printf("Bye!\n");
                dummy_variable = 0;
                break;
            }


            if (first_command == 'a' || first_command == 'r') {
                int new_input = scanf(" %c %d", &second_command, &value_amount); 

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
                    return 3;
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
                loop_check = 0;
                continue;
            }
            else {
                if (array_check) {
                    fprintf(stderr, "Invalid command\n");
                    dummy_variable = 0;
                    return 3;  
                }
                else  {
                    fprintf(stderr, "Invalid input\n");
                    dummy_variable = 0;
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

    return 0;
}
