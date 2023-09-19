#include <stdio.h>

int main() 
{
    double num1, num2, result;
    char operator;

    printf("Enter first number:\n");
    scanf("%lf", &num1);

    printf("Enter an operator (+, -, *, /):\n");
    scanf(" %c", &operator);

    printf("Enter second number:\n");
    scanf("%lf", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) 
            {
                result = num1/num2;
            }
            else 
            {
                printf("Error: Division by zero is impossible.\n");
            }
            break;
        default:
            printf("Error: Invalid operator.\n");
    }

    printf("Result: %lf\n", result);

    return 0;
}
