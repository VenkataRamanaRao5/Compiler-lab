#include <stdio.h>
#include <stdlib.h>

// Function to check if a character is valid
int isValid(int x, int inputArr[], int number) {
    int flag = 0;
    for (int i = 0; i < number; i++) {
        if (inputArr[i] == x) {
            flag = 1;
            break;
        }
    }
    return flag;
}

// Function to check if a state is a final state
int isFinal(int finalStates[], int state, int size) {
    for (int i = 0; i < size; i++) {
        if (finalStates[i] == state) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int numberOfStates;
    printf("Enter the number of states: ");
    scanf("%d", &numberOfStates);

    int numberOfInputs;
    printf("Enter the number of inputs {if (0,1) enter 2}: ");
    scanf("%d", &numberOfInputs);

    int inputArr[100];
    for (int i = 0; i < numberOfInputs; i++) {
        printf("Enter the %d input element: ", i + 1);
        scanf("%d", &inputArr[i]);
    }

    int numberOfFinal;
    printf("Enter the number of final states: ");
    scanf("%d", &numberOfFinal);

    int finalStates[100];
    for (int i = 0; i < numberOfFinal; i++) {
        printf("Enter %d final state: ", i + 1);
        scanf("%d", &finalStates[i]);
    }

    int input[100];
    int size;
    do {
        printf("Enter the size of the input: ");
        scanf("%d", &size);

        for (int i = 0; i < size; i++) {
            printf("Enter the %d character of the string: ", i + 1);
            scanf("%d", &input[i]);

            if (isValid(input[i], inputArr, numberOfInputs) == 0) {
                printf("Invalid character encountered!\n");
                exit(0);
            }
        }

        int adj[100][100];
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                adj[i][j] = -1;
            }
        }

        printf("\nSpecify -1 for transitions that are not allowed\n");
        for (int i = 0; i < numberOfStates; i++) {
            for (int j = 0; j < numberOfInputs; j++) {
                printf("Enter the state to go from %d when %d character: ", i, inputArr[j]);
                int temp;
                scanf("%d", &temp);
                adj[i][inputArr[j]] = temp;
            }
        }

        int state = 0;
        for (int i = 0; i < size; i++) {
            state = adj[state][input[i]];
            if (state == -1) {
                printf("Invalid transition, no such transition specified in rules\n");
                exit(0);
            }
        }

        if (isFinal(finalStates, state, numberOfFinal) == 1) {
            printf("The string is verified\n");
        } else {
            printf("The string is not valid\n");
        }
    } while (1);

    return 0;
}
