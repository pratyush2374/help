#include <stdio.h>
#include <string.h>
#define MAX 100
typedef struct
{
    char label[50];
    char op;
    int left;
    int right;
    char value;
} Node;

Node nodes[MAX];
int nodeCount = 0;
int variable[256];

int createLeaf(char ch)
{
    int id = nodeCount++;

    nodes[id].label[0] = '\0';
    nodes[id].op = '\0';
    nodes[id].left = -1;
    nodes[id].right = -1;
    nodes[id].value = ch;

    return id;
}

int getNode(char ch)
{
    unsigned char c = (unsigned char)ch;

    if (variable[c] == -1)
        variable[c] = createLeaf(ch);

    return variable[c];
}

int createExpression(char op, int left, int right)
{
    int i;

    for (i = 0; i < nodeCount; i++)
    {
        if (nodes[i].op == op &&
            nodes[i].left == left &&
            nodes[i].right == right)
        {
            return i;
        }
    }

    int id = nodeCount++;

    nodes[id].label[0] = '\0';
    nodes[id].op = op;
    nodes[id].left = left;
    nodes[id].right = right;
    nodes[id].value = '\0';

    return id;
}

void removeLabel(char ch)
{
    int i;

    for (i = 0; i < nodeCount; i++)
    {
        char result[50] = "";
        char *token;

        char copy[50];
        strcpy(copy, nodes[i].label);

        token = strtok(copy, ",");

        while (token != NULL)
        {
            if (!(strlen(token) == 1 && token[0] == ch))
            {
                if (result[0] != '\0')
                    strcat(result, ",");

                strcat(result, token);
            }

            token = strtok(NULL, ",");
        }

        strcpy(nodes[i].label, result);
    }
}

void assignLabel(int id, char ch)
{
    char temp[2] = {ch, '\0'};

    if (nodes[id].label[0] != '\0')
        strcat(nodes[id].label, ",");

    strcat(nodes[id].label, temp);
}

int process(char *s)
{
    char lhs, op;
    int left, right, result;

    if (strlen(s) == 5 && s[1] == '=')
    {
        lhs = s[0];
        op = s[3];

        if (op != '+' && op != '-' &&
            op != '*' && op != '/')
            return 0;

        left = getNode(s[2]);
        right = getNode(s[4]);

        result = createExpression(op, left, right);
    }
    else if (strlen(s) == 3 && s[1] == '=')
    {
        lhs = s[0];
        result = getNode(s[2]);
    }
    else
    {
        return 0;
    }

    removeLabel(lhs);
    variable[(unsigned char)lhs] = result;
    assignLabel(result, lhs);

    return 1;
}

void displayTable(void)
{
    int i;

    printf("\nDAG NODE TABLE\n\n");
    printf("%-8s %-12s %-10s %-12s %-12s\n",
           "Node", "Label", "Operator", "Left", "Right");

    for (i = 0; i < nodeCount; i++)
    {
        char left[20] = "-";
        char right[20] = "-";
        char op[10] = "-";

        if (nodes[i].op != '\0')
        {
            sprintf(op, "%c", nodes[i].op);
            sprintf(left, "N%d", nodes[i].left);
            sprintf(right, "N%d", nodes[i].right);
        }

        printf("N%-7d %-12s %-10s %-12s %-12s\n",
               i,
               nodes[i].label[0] ? nodes[i].label :
                   (nodes[i].op == '\0' ?
                       (char[2]){nodes[i].value, '\0'} : "-"),
               op, left, right);
    }
}

int main(void)
{
    char s[100];
    int i;

    for (i = 0; i < 256; i++)
        variable[i] = -1;

    printf("Enter three-address statements:\n");
    printf("Examples: a=b+c, b=a-d\n");
    printf("Enter q to quit.\n\n");

    while (1)
    {
        printf("Enter statement: ");

        if (fgets(s, sizeof(s), stdin) == NULL)
            break;

        s[strcspn(s, "\n")] = '\0';

        int j, k = 0;
        for (j = 0; s[j]; j++)
            if (s[j] != ' ' && s[j] != '\t')
                s[k++] = s[j];
        s[k] = '\0';

        if (strcmp(s, "q") == 0)
            break;

        if (s[0] == '\0')
            continue;

        if (!process(s))
            printf("Invalid statement: %s\n", s);
    }

    displayTable();

    return 0;
}
