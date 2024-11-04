#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct
{
    char symbols[256];
} production_body;
typedef struct
{
    char head;
    production_body productions[32];
    int noOfProductions;
} production;
typedef struct
{
    production productions[26];
} grammar;
grammar getGrammar()
{
    grammar g;
    while (1)
    {
        printf("Enter head:");
        char h;
        fflush(stdin);
        scanf("\n%c", &h);
        if (h == 'x')
            break;
        printf("Enter production:");
        production_body p;
        int i = g.productions[h - 'A'].noOfProductions;
        fflush(stdin);
        scanf("\n%[^\n]s", g.productions[h - 'A'].productions[i].symbols);
        g.productions[h - 'A'].noOfProductions++;
        g.productions[h - 'A'].head = h;
    }
    return g;
}
void display(grammar g)
{
    int i;
    printf("\n\n");
    for (i = 0; i < 26; i++)
    {
        if (g.productions[i].noOfProductions == 0)
            continue;
        printf("%c -> ", g.productions[i].head);
        int j = 0;
        printf("%s", g.productions[i].productions[j].symbols);
        for (j = 1; j < g.productions[i].noOfProductions; j++)
            printf(" | %s", g.productions[i].productions[j].symbols);
        printf("\n");
    }
}
void setFirsts(grammar g, int firsts[26][256])
{
    int isChanged = 0, i, j, k, l;
    int pointers[26] = {0};
    do
    {
        isChanged = 0;
        for (i = 0; i < 26; i++)
        {
            if (g.productions[i].noOfProductions == 0)
                continue;
            for (j = 0; j < g.productions[i].noOfProductions; j++)
            {
                for (k = 0; g.productions[i].productions[j].symbols[k]; k++)
                {
                    firsts[i][238] = 0;
                    if (!isupper(g.productions[i].productions[j].symbols[k]))
                    {
                        if (!firsts[i][g.productions[i].productions[j].symbols[k]])
                        {
                            isChanged = 1;
                            firsts[i][g.productions[i].productions[j].symbols[k]] = 1;
                        }
                        break;
                    }
                    else
                    {
                        for (l = 0; l < 256; l++)
                        {
                            if (firsts[g.productions[i].productions[j].symbols[k] - 'A'][l] && !firsts[i][l])
                            {
                                isChanged = 1;
                                firsts[i][l] = 1;
                            }
                        }
                        if (firsts[i][238] != 1)
                            break;
                    }
                }
            }
        }
    } while (isChanged);
}
void setFollow(grammar g, int firsts[26][256], int follow[26][256])
{
    int isChanged, i, j, k, l;
    follow['S' - 'A']['$'] = 1;
    do
    {
        isChanged = 0;
        for (i = 0; i < 26; i++)
        {
            if (g.productions[i].noOfProductions == 0)
                continue;
            for (j = 0; j < g.productions[i].noOfProductions; j++)
            {
                char *symbols = g.productions[i].productions[j].symbols;
                for (k = 0; symbols[k]; k++)
                {
                    if (isupper(symbols[k]))
                    {
                        if (symbols[k + 1] != '\0')
                        {
                            if (isupper(symbols[k + 1]))
                            {
                                int nextIndex = symbols[k + 1] - 'A';
                                for (l = 0; l < 256; l++)
                                {
                                    if (firsts[nextIndex][l] && l != 238 && !follow[symbols[k] - 'A'][l])
                                    {
                                        follow[symbols[k] - 'A'][l] = 1;
                                        isChanged = 1;
                                    }
                                }
                                if (firsts[nextIndex][238])
                                {
                                    for (l = 0; l < 256; l++)
                                    {
                                        if (follow[i][l] && !follow[symbols[k] - 'A'][l])
                                        {
                                            follow[symbols[k] - 'A'][l] = 1;
                                            isChanged = 1;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (!follow[symbols[k] - 'A'][symbols[k + 1]])
                                {
                                    follow[symbols[k] - 'A'][symbols[k + 1]] = 1;
                                    isChanged = 1;
                                }
                            }
                        }
                        else
                        {
                            for (l = 0; l < 256; l++)
                            {
                                if (follow[i][l] && !follow[symbols[k] - 'A'][l])
                                {
                                    follow[symbols[k] - 'A'][l] = 1;
                                    isChanged = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    } while (isChanged);
}
int main()
{
    grammar g = getGrammar();
    display(g);
    int firsts[26][256], follows[26][256];
    setFirsts(g, firsts);
    setFollow(g, firsts, follows);
    int i, j, k;
    printf("Symbols\t\tFirsts:\n");
    printf("----------------------------\n");
    for (i = 0; i < 26; i++)
    {
        if (g.productions[i].noOfProductions == 0)
            continue;
        printf("%c\t{", 'A' + i);
        for (j = 0; j < 256; j++)
            if (firsts[i][j])
                printf("%c, ", j);
        printf("}\n");
    }
    printf("\n\nSymbols\tFollows:\n");
    printf("----------------------------\n");
    for (i = 0; i < 26; i++)
    {
        if (g.productions[i].noOfProductions == 0)
            continue;
        printf("%c\t{", 'A' + i);
        for (j = 0; j < 256; j++)
            if (follows[i][j])
                printf("%c, ", j);
        printf("}\n");
    }
    int terminals[256] = {0};
    for (i = 0; i < 26; i++)
    {
        if (g.productions[i].noOfProductions == 0)
            continue;
        for (j = 0; j < g.productions[i].noOfProductions; j++)
            for (k = 0; g.productions[i].productions[j].symbols[k]; k++)
                if (!isupper(g.productions[i].productions[j].symbols[k]))
                    terminals[g.productions[i].productions[j].symbols[k]] = 1;
    }
    printf("\n\nPredictive Parsing Table:\n");
    printf("\t");
    for (i = 0; i < 256; i++)
        if (terminals[i])
            printf("%c\t\t", i);
    printf("\n");
    for (i = 0; i < 26; i++)
    {
        if (g.productions[i].noOfProductions == 0)
            continue;
        printf("\n%c\t", 'A' + i);
        for (j = 0; j < 256; j++)
        {
            if (terminals[j])
            {
                if (g.productions[i].noOfProductions == 1)
                {
                    if (firsts[i][j])
                        printf("%c->%s", 'A' + i, g.productions[i].productions[0].symbols);
                }
                else
                {
                    for (k = 0; k < g.productions[i].noOfProductions; k++)
                    {
                        if (!isupper(g.productions[i].productions[k].symbols[0]) && g.productions[i].productions[k].symbols[0] == j || firsts[g.productions[i].productions[k].symbols[0] - 'A'][j])
                            printf("%c->%s", 'A' + i, g.productions[i].productions[k].symbols);
                        else
                            ; // printf("boo%d %c %c -> %s\n",k, j, i + 'A', g.productions[i].productions[k].symbols);
                    }
                }
                printf("\t\t");
            }
        }
    }
    printf("\n");
    return 0;
}
