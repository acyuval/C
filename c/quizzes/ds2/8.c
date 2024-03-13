#include <stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void GeneratePermutations(char *word, int start, int end ,  int * counter) 
{
    int i =0;

    printf("and : %.*s\n", start, word); /*Print substring up to start*/
    if (start == end) 
    {
        printf("%s counter: %d\n", word, *(counter++));
        return;
    }

    for (i = start; i <= end; ++i) 
    {
        if (i != start && word[i] == word[start]) 
        {
            continue; /*Skip duplicate characters*/
        }
        
        swap(&word[start], &word[i]);
        GeneratePermutations(word, start + 1, end, counter);
        swap(&word[start], &word[i]); /*Backtrack*/
    }
}

int Permutes(char *str) 
{
    int len = strlen(str);
    int counter = 0; 
    GeneratePermutations(str, 0, len - 1, &counter);

    return 0;
}  

int main()
{
    char s1[5] = "YUVAL";

    Permutes(s1);

    return (0);
}