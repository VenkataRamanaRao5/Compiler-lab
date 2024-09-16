#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if a character is an arithmetic operator
int isArithmetic(char inp) {
    if (inp == '+' || inp == '-' || inp == '/' || inp == '%' || inp == '*') {
        return 1;
    }
    return 0;
}

// Compute the length of a string
int len(char inp[]) {
    int count = 0;
    if (inp[0] == '\0') return 0;
    for (int i = 0; inp[i] != '\0'; i++) {
        count++;
    }
    return count;
}

// Check if a character is a prime relational operator
int isPrimeRelation(char inp) {
    if (inp == '<' || inp == '>') {
        return 1;
    }
    return 0;
}

// Check if a character is an alphabetic or underscore
int isAlpha(char inp) {
    if ((inp >= 'a' && inp <= 'z') || (inp >= 'A' && inp <= 'Z') || (inp == '_')) {
        return 1;
    }
    return 0;
}

// Check if a character is an equal sign
int isEqual(char inp) {
    if (inp == '=') {
        return 1;
    }
    return 0;
}

// Check if a character is a digit
int isDigit(char inp) {
    if (inp >= '0' && inp <= '9') {
        return 1;
    }
    return 0;
}

// Check if a character is a constant
int isConst(char inp) {
    if (inp >= '1' && inp <= '9') {
        return 1;
    }
    return 0;
}

// Wipe the content of the buffer and reset the index
void memoryWipe(char buffer[], int *u) {
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = '\0';
    }
    *u = 0;
}

// Add a character to the buffer and update the index
void bufferAdd(char buffer[], int *u, char ch) {
    // printf("into buffer: %c\n", ch); // Optional debug line
    buffer[(*u)++] = ch;
}

int main(void) {
    char str[1001];
    printf("Enter a string: ");
    fgets(str, 1001, stdin);
    printf("%s\n", str);

    int u = 0;
    char buffer[1001];
    int isQuote = 0;
    int isParan = 0;

    for (int i = 0; i < strlen(str) + 1; i++) {
        if (str[i] == ' ' || str[i] == ';') {
            printf("Buffer before termination %s\n", buffer);
            // printf("Enter termination\n"); // Optional debug line

            if (isParan == 1) {
                printf("%s is an array type\n", buffer);
                isParan = 0;
            } else if (isQuote == 1) {
                printf("%s is a string literal\n", buffer);
                isQuote = 0;
            } else if (isArithmetic(buffer[0]) == 1) {
                printf("%s is an arithmetic operator\n", buffer);
            } else if (isPrimeRelation(buffer[0]) == 1) {
                printf("%s is a relational operator\n", buffer);
            } else if (isDigit(buffer[0]) == 1) {
                printf("%s is a number\n", buffer);
            } else if (isAlpha(buffer[0]) == 1) {
                printf("%s is an identifier\n", buffer);
            } else if (len(buffer) == 1 && isEqual(buffer[0]) == 1) {
                printf("%s is an assignment\n", buffer);
            } else if (len(buffer) == 2 && isEqual(buffer[0]) == 1) {
                printf("%s is a comparator\n", buffer);
            }

            printf("Memory wipe is called\n");
            memoryWipe(buffer, &u);
        } else if (isAlpha(str[i]) == 1) {
            bufferAdd(buffer, &u, str[i]);
        } else if (str[i] == '"') {
            isQuote = 1;
            continue;
        } else if (isPrimeRelation(str[i]) == 1) {
            bufferAdd(buffer, &u, str[i]);
        } else if (str[i] == '[') {
            isParan = 1;
            // bufferAdd(buffer, &u, str[i]); // Optional line
            continue;
        } else if (isArithmetic(str[i]) == 1) {
            bufferAdd(buffer, &u, str[i]);
        } else if (isEqual(str[i]) == 1) {
            bufferAdd(buffer, &u, str[i]);
        } else if (isDigit(str[i]) == 1) {
            bufferAdd(buffer, &u, str[i]);
        }
    }

    return 0;
}
