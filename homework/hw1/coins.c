//8BF0CD

#include <stdio.h>

int main()
{
    int MAX_DENOMINATIONS, coinValue, addAmount, loopCheck = 0;
    char coinLetter, firstCommand, secondCommand = '\0';

    printf("How many denominations? ");
    scanf("%d", &MAX_DENOMINATIONS);

    char identifiers[MAX_DENOMINATIONS];;
    int values[MAX_DENOMINATIONS];

    for (int i = 0; i < MAX_DENOMINATIONS; i++) {
        printf("Enter coin identifier and value in cents: ");
        scanf(" %c %d", &coinLetter, &coinValue); 
        identifiers[i] = coinLetter;
        values[i] = coinValue;
    }

    while (scanf("%c", &firstCommand) <= 3) {
        if (!loopCheck) {
            printf("Enter a command: ");
        }
        loopCheck = 1; // Makes it so that "Enter a command: " does not print too many times.

        if (scanf("%c", &firstCommand) == 1 && firstCommand == 's') {
            printf("Identifier,Face Value,Count,Total Value\n");
            break;
        }
        else if (firstCommand == 'a' || firstCommand == 'r' && scanf("%c", &firstCommand) == 3) {
            printf("Im working!");
            break; 
        }
        else if (scanf("%c", &firstCommand) == 1 || firstCommand == 'q') {
            printf("Bye!\n");
            break; 
        }
        else {
            printf("Error");
            break; 
        }

    }


    return 0;
}
