//8BF0CD

#include <stdio.h>

int main()
{
    int MAX_DENOMINATIONS, coinValue, valueAmount, centValue, loopCheck, multValue, arrayCheck = 0;
    int dummyVariable = 1;
    double totalValue = 0.0; 
    char coinLetter, firstCommand, secondCommand = '\0';

    /* Gathers information on how many "denominations" or coins there are. */
    printf("How many denominations? ");
    scanf("%d", &MAX_DENOMINATIONS);

    /* Setting array size to be the maximum denominations. */
    char identifiers[MAX_DENOMINATIONS];
    char commandChars[] = {'a', 'r', 's', 'q'};
    int values[MAX_DENOMINATIONS];
    int coinMultiplier[MAX_DENOMINATIONS];

    for (int i = 0; i < MAX_DENOMINATIONS; i++) {
        /* Initializes all of the arrays and gathers the currency and their values. */
        printf("Enter coin identifier and value in cents: ");
        scanf(" %c %d", &coinLetter, &coinValue); 
        identifiers[i] = coinLetter;
        values[i] = coinValue;
        coinMultiplier[i] = 0;
    }

    while (dummyVariable) {
        if (!loopCheck) {
            printf("Enter a command: ");
        }
        loopCheck = 1; // Makes it so that "Enter a command: " does not print too many times.

        int userInput = scanf(" %c", &firstCommand);

        if (userInput == 1) {
            if (firstCommand == 's') {
                printf("Identifier,Face Value,Count,Total Value\n");

                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    multValue = values[i] * coinMultiplier[i];
                    printf("%c,%d,%d,%d\n", identifiers[i], values[i], coinMultiplier[i], multValue); 
                    totalValue += (double) multValue / 100.0;
                }

                printf("Overall value of collection: $%.2lf\n", totalValue); //Prints the total value of the collection. 

                loopCheck = 0;
                continue;
            } 
            else if (firstCommand == 'q') {
                printf("Bye!\n");
                dummyVariable = 0;
                break;
            }
    
            if (firstCommand == 'a' || firstCommand == 'r') {
                int newInput = scanf(" %c %d", &secondCommand, &valueAmount);

                

                for (int i = 0; i < MAX_DENOMINATIONS; ++i) {
                    if (firstCommand == 'a') {
                        if (identifiers[i] == secondCommand) {
                            coinMultiplier[i] += valueAmount;
                            break;
                        }
                    }
                    else if (firstCommand == 'r') {
                        if (identifiers[i] == secondCommand) {
                            coinMultiplier[i] -= valueAmount;
                            break;
                        }
                    }

                }

                if (newInput != 2) {
                    printf("Invalid Input\n"); // Checks if there is too litle or too many inputs.
                    break;
                }
                loopCheck = 0;
                continue;
            }
        }
        else {
            printf("Invalid Input\n");
            dummyVariable = 0;
            break;
        }
    }
    
    

    return 0;
}
