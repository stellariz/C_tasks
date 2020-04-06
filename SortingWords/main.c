#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define NWORD 4
#define NLETTERS 7


int comp(const void *i, const int *j){
    char* a = *(char**)i;
    char* b = *(char**)j;
    return strcmp(a,b);
}


int main(void) {
    char** allWords = (char**)malloc(sizeof(char*) * NWORD); // массив указателей на слова
    int cWord = 0; // счётчик слов
    while(1){
        char* word = (char*)malloc(sizeof(char) * NLETTERS); // буфер
        scanf("%s", word);
        *(allWords+cWord) = word; // заполняем массив слов
        cWord++;
        if (word[strlen(word)-1]  == 46){
            word[strlen(word)-1] = 0;
            break;
        }
    }
    qsort(allWords, cWord, sizeof(char*), (int (*)(const void *, const void *)) comp); // чудо - сортировка
    for (int i = 0; i < cWord; ++i) {
        printf("%s ", *(allWords + i));
        free(*(allWords + i));
    }
    return 0;
}