#include <stdio.h>
#include <malloc.h>
#define GRAPH struct list
#define checked 2
#define checking 1
#define notChecked 0


GRAPH{
    int end;
    int state;
    GRAPH *next;
};


void check(GRAPH* top, int vertex){
    int counter = 0;
    for (int i = 0; i<vertex; ++i){
        if (!(top[i].state))
            counter++;
    }
    if (counter)
        printf("Disconnected graph");
    else
        printf("Connected graph");
}


int findAnyPoint(GRAPH *top){
    int i = 0;
    while (!top[i].next)
        i++;
    return i;
}


int popElement(GRAPH *top){
    int point;
    point = top -> next -> end;
    GRAPH *del;
    del = top -> next;
    top -> next = top ->next->next;
    free(del);
    return point - 1;
}


void interruption(GRAPH *top, GRAPH *point){
    GRAPH *peak = point->next;
    point -> state = checking;
    while (peak){
        int next = popElement(point);
        if (!(top[next].state)){
            interruption(top, &top[next]);
        }
        peak = point -> next;
    }
    point -> state = checked;
}


void pushElement(GRAPH *top, int vertex){
    GRAPH* tmp = (GRAPH*)malloc(sizeof(GRAPH));
    tmp -> end = vertex;
    GRAPH *first = top -> next;
    top -> next = tmp;
    tmp -> next = first;
}




int main() {
    int vertex, edges, index;
    scanf("%d %d", &vertex, &edges);
    GRAPH*top = (GRAPH*)malloc(sizeof(GRAPH) * vertex);
    for (int i = 0; i < vertex; ++i){
        top[i].next = NULL;
        top[i].state = notChecked;
    }
    for (int i = 0; i < edges; i++){
        int firstPoint, secondPoint;
        scanf("%d %d", &firstPoint, &secondPoint);
        pushElement(&top[firstPoint-1], secondPoint);
        pushElement(&top[secondPoint-1], firstPoint);
    }
    index = findAnyPoint(top);
    interruption(top, &top[index]);
    check(top, vertex);
    free(top);
    return 0;
}


