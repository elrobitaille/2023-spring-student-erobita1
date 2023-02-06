//8BF0CD

#include <stdio.h>

int main()
{
    int MAX_DENOMINATIONS, coinValue, valueAmount, loopCheck = 0;
    int dummyVariable = 1;
    char coinLetter, firstCommand, secondCommand = '\0';

    printf("How many denominations? ");
    scanf("%d", &MAX_DENOMINATIONS);


    char identifiers[MAX_DENOMINATIONS];
    int values[MAX_DENOMINATIONS];
    int coinMultiplier[MAX_DENOMINATIONS];

    for (int i = 0; i < MAX_DENOMINATIONS; i++) {
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
                    printf(" %c,%d,%d,%d\n", identifiers[i], values[i], coinMultiplier[i], values[i] * coinMultiplier[i]);
                }

                dummyVariable = 0;
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
