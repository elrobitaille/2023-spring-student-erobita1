//8BF0CD

#include <stdio.h>

int main()
{
    int MAX_DENOMINATIONS, coinValue = 0;
    char coinLetter = '\0';

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

    printf("%d\n", identifiers[0]);
    
    return 0;
}
