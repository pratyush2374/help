#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char infix[MAX], postfix[MAX], stack[MAX];
char operands[MAX][MAX];
int top = -1, ptop = -1, temp = 1;

int priority(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void infixToPostfix(char expr[])
{
    int i, j = 0;
    char ch;

    for (i = 0; expr[i] != '\0'; i++)
    {
        ch = expr[i];

        if (isalnum((unsigned char)ch))
            postfix[j++] = ch;

        else if (ch == '(')
            stack[++top] = ch;

        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = stack[top--];

            if (top != -1)
                top--;
        }
        else
        {
            while (top != -1 && stack[top] != '(' &&
                   priority(stack[top]) >= priority(ch))
                postfix[j++] = stack[top--];

            stack[++top] = ch;
        }
    }

    while (top != -1)
        postfix[j++] = stack[top--];

    postfix[j] = '\0';
}

void generateTAC(char lhs)
{
    int i;
    char left[MAX], right[MAX], result[MAX];

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)postfix[i]))
        {
            char value[2] = {postfix[i], '\0'};
            strcpy(operands[++ptop], value);
        }
        else
        {
            strcpy(right, operands[ptop--]);
            strcpy(left, operands[ptop--]);

            sprintf(result, "t%d", temp++);

            printf("%s = %s %c %s\n",
                   result, left, postfix[i], right);

            strcpy(operands[++ptop], result);
        }
    }

    printf("%c = %s\n", lhs, operands[ptop]);
}

int main(void)
{
    char input[MAX];
    char *equal;
    char lhs;

    printf("Enter an assignment expression: ");
    scanf("%99s", input);

    equal = strchr(input, '=');

    if (equal == NULL || equal != input + 1)
    {
        printf("Invalid assignment expression.\n");
        return 1;
    }

    lhs = input[0];

    infixToPostfix(equal + 1);

    printf("\nPostfix expression: %s\n", postfix);
    printf("\nThree Address Code:\n");

    generateTAC(lhs);

    return 0;
}
