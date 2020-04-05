//односвзяный список, написать функцию, переставляющую элементы списка в обратном порядке
#include <stdio.h>
#include <malloc.h>
#define LIST struct list


LIST{
    int value;
    LIST*next;
};


void push(LIST* L, int value){
    LIST* tmp = (LIST*)malloc(sizeof(LIST));
    tmp -> value = value;
    tmp -> next = L -> next;
    L -> next = tmp;
}


void printStack(LIST* L){
    LIST*cur = L->next;
    for(; cur; cur = cur -> next)
        printf("%d ", cur -> value);
    printf("\n");
}

int isEmpty(LIST*L){
    return (!L->next);
}

LIST* reverse(LIST*L){
    if (isEmpty(L))
        return L;
    if (!(L->next->next))
        return L;
    LIST *cur, *prev, *tmp;
    cur = prev = L -> next;
    cur = cur -> next;
    prev -> next = NULL;
    while(cur){
        tmp = cur -> next;
        cur -> next = prev;
        prev = cur;
        cur = tmp;
    }
    L -> next = prev;
    return L;
}

int main(){
    int sizeOfStack;
    scanf("%d", &sizeOfStack);
    LIST* L = (LIST*)malloc(sizeof(LIST));
    L -> next = NULL;
    for(int i = 0; i < sizeOfStack; ++i){
        int value;
        scanf("%d", &value);
        push(L, value);
    }
    printStack(L);
    L = reverse(L);
    printStack(L);
    return 0;
}