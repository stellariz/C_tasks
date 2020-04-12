#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define GRAPH struct list


GRAPH{
    int vertex;
    GRAPH* next;
};


int min(int x, int y){
    return (x < y ? x : y);
}


void pushElement(GRAPH *top, int vertex){
    GRAPH*newVert = (GRAPH*)malloc(sizeof(GRAPH));
    newVert -> vertex = vertex;
    GRAPH *first = top -> next;
    top -> next = newVert;
    newVert -> next = first;
}


void printPoints(GRAPH* listCutpoints, int numOfVertices){
    int* copies = (int*)malloc(sizeof(int) * numOfVertices);
    memset(copies, 0, sizeof(int) * numOfVertices);
    GRAPH* node = listCutpoints -> next;
    for(;node;node=node->next) {
        if (copies[node->vertex] == 0) {
            printf("%d ", node->vertex);
            ++copies[node->vertex];
        }
    }
    free(copies);
}


void cutPoints(int currV, int parentV, int* timer, int* children, GRAPH* list, GRAPH* listCutpoints, bool* visited, int* timeInDfs, int* leastTime){
    visited[currV] = true;
    int posInDfs = *timer;
    timeInDfs[currV] = leastTime[currV] = posInDfs;
    *timer+=1;
    if (parentV == 0)
        *children+=1;
    for (GRAPH* node = list[currV].next; node; node = node -> next){
        int whither = node -> vertex;
        if (whither == parentV) // don't check the same edge
            continue;
        if (visited[whither])
            leastTime[currV] = min (leastTime[whither], timeInDfs[currV]); //shortest way to current vertex
        else {
            cutPoints(whither, currV, timer, children, list, listCutpoints, visited, timeInDfs, leastTime);
            leastTime[whither] = min(leastTime[whither], leastTime[currV]);
            if (leastTime[whither] >= timeInDfs[currV] && parentV != -1) // if shortest time to the point >= timeInDfs its parent,
                                                                         // we have way to this only through this point
                pushElement(listCutpoints, currV);
        }
    }
}


GRAPH* initialiseInputData(FILE*fp, int numOfVertices){
    GRAPH* listVertex = (GRAPH*)malloc(sizeof(GRAPH) * numOfVertices); // list of adjacency
    for (int i = 0; i < numOfVertices; ++i)
        (listVertex + i) -> next = NULL;
    while (1){
        int fPoint, sPoint;
        int check = fscanf(fp, "%d ", &fPoint);
        if (check == -1)
            break;
        fseek(fp, -1, SEEK_CUR);
        if (fgetc(fp)!='\n'){
            fscanf (fp, "%d", &sPoint);
            pushElement(listVertex+fPoint, sPoint);
            pushElement(listVertex+sPoint, fPoint);
        }
        else{
            pushElement(listVertex+fPoint, sPoint);
            pushElement(listVertex+sPoint, fPoint);
        }
    }
    return listVertex;
}


int main() {
    FILE*fp = fopen("in.txt", "r");
    int numOfVertices, timer, childrenRoot;
    timer = childrenRoot = 0;
    fscanf(fp, "%d", &numOfVertices);
    GRAPH* listCutpoints = (GRAPH*)malloc(sizeof(GRAPH)); // list of cutpoints
    listCutpoints -> next = NULL;
    bool* visited = (bool*)malloc(sizeof(bool) * numOfVertices);
    int* timeInDfs = (int*)malloc(sizeof(int) * numOfVertices);
    int* leastTime = (int*)malloc(sizeof(int) * numOfVertices);
    memset(visited, false, numOfVertices);
    GRAPH* adjacencyList = initialiseInputData(fp, numOfVertices);
    cutPoints(0, -1, &timer, &childrenRoot, adjacencyList, listCutpoints, visited, timeInDfs, leastTime);
    if (childrenRoot > 1)    // if root has more than one descendant - it's cutpoint
        pushElement(listCutpoints, 1);
    printPoints(listCutpoints, numOfVertices);
    return 0;
}
