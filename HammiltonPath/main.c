#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define PATH struct list

PATH{
    int vertex;
    PATH* next;
};



void pushInPath(PATH*top, int vertex){
    PATH* tmp = (PATH*)malloc(sizeof(PATH));
    tmp -> vertex = vertex;
    tmp -> next = top -> next;
    top -> next = tmp;
}


bool pathIsNotEmpty(PATH* top) {
    return top->next;
}


int popPath(PATH*top){
    PATH* delElem = top -> next;
    int value = top -> next -> vertex;
    top -> next = top -> next -> next;
    free(delElem);
    return value;
}


void printPath(PATH* top){
    while(pathIsNotEmpty(top))
        printf("%d ", popPath(top));
    free(top);
}


void restorePath(int** matrix, bool** data, const int numOfVertices, const int finish) {
    PATH *top = (PATH *) malloc(sizeof(PATH));
    top->next = NULL;
    int mask = (int) pow(2, numOfVertices) - 1;
    int curVertex = finish;
    while (mask) {
        for (int i = 0; i < numOfVertices; ++i) {
            if (data[i][mask - (int)pow(2,i)] && matrix[curVertex][i] && (mask & (1 << i))) {
                pushInPath(top, i);
                mask -= (int) pow(2, i);
                curVertex = i;
            }
        }
    }
    popPath(top);
    printPath(top);

   
    free(matrix);
    free(data);
}


bool findHammiltonPath(int**matrix, bool** data, const int numOfVertices, const int vertex, const int mask){
    if (data[vertex][mask])
        return true;
    for (int i = 0; i < numOfVertices; ++i) {
        if (matrix[vertex][i] && (mask & (1 << i))) // смотрим есть ли ребро и посещали ли мы эту вершину
            data[vertex][mask] = findHammiltonPath(matrix, data, numOfVertices, i, mask - (int) pow(2, i));
        if (data[vertex][mask])
            break;
    }
    return data[vertex][mask];
}


void start(int**matrix, const int numOfVertices) {
    int addingVertex = numOfVertices - 1;
    bool** data = (bool**) malloc(numOfVertices);
    for (int i = 0; i < numOfVertices; ++i){
        data[i] = (bool*) malloc((int)pow(2, numOfVertices));
        memset(data[i], false, (int)pow(2, numOfVertices));
    }
    data[addingVertex][0] = true; // старт - начало цикла
    findHammiltonPath(matrix, data, numOfVertices, addingVertex, (int)pow(2, numOfVertices) - 1); // идём с конца
    /*for (int i = 0; i < numOfVertices; ++i){
        for (int j = 0; j < pow(2, numOfVertices); ++j)
            printf("%d ", data[i][j]);
    printf("\n");
    }*/
    restorePath(matrix, data, numOfVertices, addingVertex);
}


int** initMatrixAdjacency(FILE*fp, const int maxNumOfVertices, int* maxVertex){
    int** matrix =(int**)malloc(sizeof(int) * (maxNumOfVertices + 1));
    for (int i = 0; i <= maxNumOfVertices; ++i){
        matrix[i] = (int*)malloc(sizeof(int) * (maxNumOfVertices+1));
        memset(matrix[i], 0, sizeof(int) * (maxNumOfVertices + 1));
    }
    for (int i = 0; i < maxNumOfVertices; ++i) {
        int begin, end, biggerVertex;
        fscanf(fp, "%d %d", &begin, &end);
        biggerVertex = (begin > end ? begin : end);
        if (biggerVertex > *maxVertex)
            *maxVertex = biggerVertex;
        ++matrix[begin][end];
        ++matrix[end][begin];
    }
    *maxVertex+=1; // добавляем новую вершину
    for(int i = 0; i < *maxVertex; ++i) {
        ++matrix[*maxVertex][i];
        ++matrix[i][*maxVertex];
    }
    /*for(int i = 0; i <= *maxVertex; ++i) {
        for (int j = 0; j <= *maxVertex; ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }*/
    return matrix;
}


int* degreesOfVertices(int** matrix, int numOfVertices){
    int* deg = (int*)malloc(sizeof(int) * numOfVertices);
    memset(deg, 0, sizeof(int)*numOfVertices);
    for (int i = 0; i < numOfVertices; ++i){
        for (int j = 0; j < numOfVertices; ++j)
            deg[i]+=matrix[i][j];
    }
    for (int i = 0; i < numOfVertices; ++i){
        if (deg[i] < (numOfVertices - 1)/2) // теорема Дирака (от обратного)
            return NULL;
    }
    return deg;
}


int main() {
    FILE* fp = fopen("in.txt", "r");
    int numOfEdges, numOfVertices;
    int maxVertex = -1;
    fscanf(fp, "%d", &numOfEdges);
    int maxNumOfVertices = numOfEdges;
    int*deg = NULL;
    int** graph = initMatrixAdjacency(fp, maxNumOfVertices, &maxVertex);
    if (maxVertex > -1) {
        numOfVertices = maxVertex + 1;
        deg = degreesOfVertices(graph, numOfVertices);
    }
    else{
        printf("There is no vertices!");
        return 0;
    }
    if(deg != NULL) {
        start(graph, numOfVertices);
        free(deg);
    }
    else
        printf("NO");
    return 0;
}
