#include <stdio.h>
#include <stdlib.h>

int  isValid(int x, int inputArr[], int number){
        int flag = 0;
        for(int i = 0; i < number; i++){
                if(inputArr[i] == x){
                        flag = 1;
                        break;
                }
        }
        return flag;
}

int main(void){
        int numberOfStates;
        printf("Enter the number of states: ");
        scanf("%d",&numberOfStates);
        int numberOfInputs;
        printf("Enter the number of inputs {if (0,1) enter 2}: ");
        scanf("%d",&numberOfInputs);
        int inputArr[100];
        for(int i = 0; i < numberOfInputs; i++){
                printf("Enter the %d input element: ",i+1);
                scanf("%d", &inputArr[i]);
        }
        int input[100];
        int size;
        do{
                printf("Enter the size of the input: ");
                scanf("%d",&size);
                        for(int i = 0 ; i < size; i++){
                                printf("enter the %d character of string: ",i+1);
                                scanf("%d",&input[i]);
                                if(isValid(input[i],inputArr,numberOfInputs) == 0){
                                        printf("Invalid character encountered!\n");
                                        exit(0);
                                }
                        }
        //setting up the adjacency list
                int adj[100][100];
                for(int i = 0 ; i < 100; i++){
                        for(int j = 0; j < 100; j++){
                                adj[i][j] = -1;
                        }
                }
                printf("\nSpecify -1 for transitions that are not allowed\n");
                for(int i = 0 ; i < numberOfStates; i++){
                        for(int j = 0 ; j < numberOfInputs; j++){
                                printf("enter the state to go from %d when %d character: ",i,inputArr[j]);
                                int temp;
                                scanf("%d",&temp);
                                adj[i][inputArr[j]] = temp;
                        }
                }

                int finalState = numberOfStates - 1;
                int state = 0;
                for(int i = 0 ; i < size; i++){
                        state = adj[state][input[i]];
                        if(state == -1){
                                printf("invalid transition, no such transition specified in rules\n");
                                exit(0);
                        }

                }
                if(state == finalState){
                        printf("The string is verified\n");
                }
                else{
                        printf("the string is not valid\n");
                }
        }while(1);
        return 0;

}
