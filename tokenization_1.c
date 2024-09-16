#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isArithmetic(char inp[]) {
    if (inp[0] == '+' || inp[0] == '-' || inp[0] == '/' || inp[0] == '%' || inp[0] == '*') {
        return 1;
    }
    return 0;
}

int len(char inp[]) {
    int count = 0;
    for (int i = 0; inp[i] != '\0'; i++) {
        count++;
    }
    return count;
}

int isPrimeRelation(char inp[]) {
    if (strcmp(inp, "<") == 0 || strcmp(inp, ">") == 0) {
        return 1;
    }
    return 0;
}

int isKeyword(char inp[]) {
    if (strcmp(inp, "if") == 0 || strcmp(inp, "else if") == 0 || strcmp(inp, "else") == 0 ||
        strcmp(inp, "while") == 0 || strcmp(inp, "for") == 0 || strcmp(inp, "do") == 0 ||
        strcmp(inp, "goto") == 0) {
        return 1;
    }
    return 0;
}

int isDataType(char inp[]) {
    if (strcmp(inp, "int") == 0 || strcmp(inp, "char") == 0 || strcmp(inp, "float") == 0 ||
        strcmp(inp, "double") == 0 || strcmp(inp, "long") == 0) {
        return 1;
    }
    return 0;
}

int isRelational(char inp[]) {
    if (strcmp(inp, "<=") == 0 || strcmp(inp, ">=") == 0) {
        return 1;
    }
    return 0;
}

int isLogical(char inp[]) {
    if (strcmp(inp, "!=") == 0 || strcmp(inp, "==") == 0) {
        return 1;
    }
    return 0;
}

int isDigit(char inp[]) {
    if (inp[0] >= '0' && inp[0] <= '9') {
        return 1;
    }
    return 0;
}

int isEquality(char inp[]) {
    if (strcmp(inp, "==") == 0) {
        return 1;
    }
    return 0;
}

int incrementor(char inp[]) {
    if (strcmp(inp, "++") == 0) {
        return 1;
    }
    return 0;
}

int decrementor(char inp[]) {
    if (strcmp(inp, "--") == 0) {
        return 1;
    }
    return 0;
}

int isConst(char inp[]) {
    if (inp[0] >= '1' && inp[0] <= '9') {
        return 1;
    }
    return 0;
}

int main(void) {
    char option;
    do {
        printf("Enter a string: ");
        char inp[100];
        scanf("%s", inp);
        getchar(); // Clear newline character from input buffer

        int size = len(inp);
        printf("The size of the word is %d\n", size);

        if (size < 2 && size > 0) {
            if (isArithmetic(inp)) {
                printf("%s is an arithmetic symbol\n", inp);
            } else if (isPrimeRelation(inp)) {
                printf("%s is a relational type\n", inp);
            } else if (isDigit(inp)) {
                printf("%s is a digit\n", inp);
            } else {
                printf("%s is just a symbol\n", inp);
            }
        } else if (size >= 2) {
            if (isKeyword(inp)) {
                printf("%s is a keyword\n", inp);
            } else if (isDataType(inp)) {
                printf("%s is a datatype\n", inp);
            } else if (isLogical(inp)) {
                printf("%s is a logical symbol\n", inp);
            } else if (isRelational(inp)) {
                printf("%s is a relational type\n", inp);
            } else if (incrementor(inp)) {
                printf("%s is an incrementor\n", inp);
            } else if (decrementor(inp)) {
                printf("%s is a decrementor\n", inp);
            } else if (isConst(inp)) {
                printf("%s is a constant value\n", inp);
            } else {
                printf("%s is an identifier\n", inp);
            }
        }

        printf("Enter y to continue: ");
        scanf(" %c", &option); // Note the space before %c to consume any leftover whitespace

    } while (option == 'y');

    return 0;
}
