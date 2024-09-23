#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int main(void) {
        int numberOfStates = 0;
        printf("Enter the number of states: ");
        scanf("%d", &numberOfStates);

        int numberOfFinalStates = 0;
        printf("Enter the number of final states: ");
        scanf("%d", &numberOfFinalStates);
        int finalStates[MAX];
        for (int i = 0; i < numberOfFinalStates; i++) {
                printf("Enter the %d final state: ", i + 1);
                scanf("%d", &finalStates[i]);
        }

        int numberOfInputs = 0;
        printf("Enter the number of inputs: ");
        scanf("%d", &numberOfInputs);
        int inputArray[MAX];
        for (int i = 0; i < numberOfInputs; i++) {
                printf("Enter %d input: ", i + 1);
                scanf("%d", &inputArray[i]);
        }

        int adj[MAX][MAX];
        for (int i = 0; i < MAX; i++) {
                for (int j = 0; j < MAX; j++) {
                        adj[i][j] = -1;
                }
        }

        for (int i = 0; i < numberOfStates; i++) {
                for (int j = 0; j < numberOfInputs; j++) {
                        printf("Enter the transition [%d] on input [%d]: ", i, inputArray[j]);
                        scanf("%d", &adj[i][j]);
                }
        }
        for (int i = 0; i < numberOfStates; i++) {
                for (int j = 0; j < numberOfInputs; j++) {
                        printf("Enter the transition [%d] on input [%d]: ", i, inputArray[j]);
                        scanf("%d", &adj[i][j]);
                }
        }
        int statePartition[MAX];
        int numPartitions = 2;
        printf("NUmber of states: %d",numberOfStates);
        for (int i = 0; i < numberOfStates; i++) {
                printf("i value in loop : %d\n",i);
                int final = 0;
                for(int j = 0 ; j < numberOfFinalStates; j++){
                        if(i == finalStates[j]){
                                final = 1;
                                break;
                        }
                }
                printf("OUTOFFOR\n");
                if(final == 1){
                        statePartition[i] = 1;
                }
                else{
                        statePartition[i] = 0;
                }


                printf("Inside state partition loop\n");
        }
        printf("Outside the state partition loop");
        int changed = 0;
        do {
                changed = 0;
                int newPartition[MAX][MAX];
                int partitionCount = 0;
                int partitionSize[MAX] = {0};

                for (int i = 0; i < numberOfStates; i++) {
                        int found = 0;
                        for (int p = 0; p < partitionCount; p++) {
                                if (statePartition[i] == statePartition[newPartition[p][0]]) {
                                        newPartition[p][partitionSize[p]++] = i;
                                        found = 1;
                                        break;
                                }
                        }
                        if (!found) {
                                newPartition[partitionCount][0] = i;
                                partitionSize[partitionCount] = 1;
                                partitionCount++;
                        }
                }

                for (int p = 0; p < partitionCount; p++) {
                        for (int j = 0; j < partitionSize[p]; j++) {
                                int state = newPartition[p][j];
                                for (int k = 0; k < numberOfInputs; k++) {
                                        int nextState = adj[state][k];
                                        if(nextState != -1 && statePartition[nextState] != statePartition[newPartition[p][0]]){
                                                changed = 1;
                                                break;
                                        }
                                }
                        }
                }
                if (changed) {
                        memcpy(statePartition, newPartition, sizeof(newPartition));
                }
        } while (changed);
        printf("Outside dowhile\n");


        printf("\nMinimized DFA:\n");
        for (int i = 0; i < numberOfStates; i++) {
                printf("State %d is in partition %d\n", i, statePartition[i]);
        }

        return 0;
}
