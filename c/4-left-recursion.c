#include <stdio.h>
#include <string.h>

int main() {
    char production[100];
    char non_terminal;
    char alpha[10][10], beta[10][10];
    int alpha_count = 0, beta_count = 0;

    printf("Enter production rule (e.g., E->E+T|T): ");
    if (scanf("%99s", production) != 1) {
        printf("Error reading input.\n");
        return 1;
    }

    non_terminal = production[0];

    if (production[1] != '-' || production[2] != '>') {
        printf("Invalid production format. Use '->'\n");
        return 1;
    }

    char *rhs = production + 3;
    char *token = strtok(rhs, "|");

    while (token != NULL) {
        if (token[0] == non_terminal) {
            strcpy(alpha[alpha_count], token + 1);
            alpha_count++;
        } else {
            strcpy(beta[beta_count], token);
            beta_count++;
        }
        token = strtok(NULL, "|");
    }

    if (alpha_count == 0) {
        printf("\nThe grammar does not contain immediate left recursion.\n");
    } else {
        printf("\n--- Grammars after eliminating Left Recursion ---\n");

        printf("%c -> ", non_terminal);
        for (int i = 0; i < beta_count; i++) {
            printf("%s%c'", beta[i], non_terminal);
            if (i < beta_count - 1) printf(" | ");
        }
        printf("\n");

        printf("%c' -> ", non_terminal);
        for (int i = 0; i < alpha_count; i++) {
            printf("%s%c' | ", alpha[i], non_terminal);
        }
        printf("e\n");
    }

    return 0;
}
