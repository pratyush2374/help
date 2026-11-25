#include <stdio.h>
#include <stdbool.h>
#define MAX_STATES 20
#define MAX_SYMBOLS 10

int nStates, nSymbols, nFinal;
int transition[MAX_STATES][MAX_SYMBOLS];
int finalStates[MAX_STATES];
bool isFinal[MAX_STATES] = {false};

int groupID[MAX_STATES];
int nextGroupID[MAX_STATES];

void initializePartition() {
    for (int i = 0; i < nFinal; i++) {
        isFinal[finalStates[i]] = true;
    }

    for (int i = 0; i < nStates; i++) {
        if (isFinal[i]) {
            groupID[i] = 1;
        } else {
            groupID[i] = 0;
        }
    }
}

void refinePartitions() {
    bool changed;

    do {
        changed = false;
        int newGroupCount = 0;

        for (int i = 0; i < nStates; i++) {
            nextGroupID[i] = -1;
        }

        for (int i = 0; i < nStates; i++) {
            if (nextGroupID[i] != -1) continue;

            nextGroupID[i] = newGroupCount;

            for (int j = i + 1; j < nStates; j++) {
                if (nextGroupID[j] != -1) continue;

                if (groupID[i] == groupID[j]) {
                    bool behavesIdentically = true;

                    for (int s = 0; s < nSymbols; s++) {
                        int destI = transition[i][s];
                        int destJ = transition[j][s];

                        if (groupID[destI] != groupID[destJ]) {
                            behavesIdentically = false;
                            break;
                        }
                    }

                    if (behavesIdentically) {
                        nextGroupID[j] = newGroupCount;
                    }
                }
            }
            newGroupCount++;
        }

        for (int i = 0; i < nStates; i++) {
            if (groupID[i] != nextGroupID[i]) {
                changed = true;
            }
            groupID[i] = nextGroupID[i];
        }

    } while (changed);
}

void printMinimizedDFA() {
    printf("\n--- Minimized DFA Equivalent States ---\n");
    bool visited[MAX_STATES] = {false};

    for (int i = 0; i < nStates; i++) {
        if (visited[i]) continue;

        printf("{ %d", i);
        visited[i] = true;

        for (int j = i + 1; j < nStates; j++) {
            if (groupID[i] == groupID[j]) {
                printf(", %d", j);
                visited[j] = true;
            }
        }
        printf(" }\n");
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &nStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &nSymbols);

    printf("Enter transition table (State x Symbol):\n");
    for (int i = 0; i < nStates; i++) {
        for (int j = 0; j < nSymbols; j++) {
            printf("Transition for state %d on symbol %d: ", i, j);
            scanf("%d", &transition[i][j]);
        }
    }

    printf("Enter number of final states: ");
    scanf("%d", &nFinal);

    printf("Enter final states: ");
    for (int i = 0; i < nFinal; i++) {
        scanf("%d", &finalStates[i]);
    }

    initializePartition();
    refinePartitions();
    printMinimizedDFA();

    return 0;
}
