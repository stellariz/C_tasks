#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

#define PATH struct list1


PATH{
    int vertex;
    PATH* next;
};



bool isNotEmpty(PATH* top){
    return (top -> next);
}


void pushInPath(PATH* top, int vertex){
    PATH* tmp = (PATH*)malloc(sizeof(PATH));
    tmp -> vertex = vertex;
    tmp -> next = top -> next;
    top -> next = tmp;
}


void popInPath(PATH*top){
    PATH* del = top -> next;
    printf("%d ", del -> vertex);
    top -> next = top -> next -> next;
    free(del);
}


void searchEulerPath(int** matrix, int* deg, const int numOfVertices) {
    PATH *way = (PATH *) malloc(sizeof(PATH));
    way->next = NULL;
    for (int i = 0; i < numOfVertices; ++i) {
        if (deg[i] % 2) {
            pushInPath(way, i);
            break;
        }
    }
    while (isNotEmpty(way)){
         int currentVertex = way -> next -> vertex;
         for (int column = 0; column < numOfVertices; ++column) { // finding way from current vertex
             if (matrix[currentVertex][column]) {
                 --matrix[currentVertex][column]; // decrease degrees of vertices
                 --matrix[column][currentVertex];
                 pushInPath(way, column); // pushing in stack of vertices
                 break;
             }
         }
         if(currentVertex == way -> next -> vertex) // if we didn't find vertex - pop from stack for another vertex
             popInPath(way);
     }
    free(matrix);
    free(deg);
    free(way);
}


int** initMatrixAdjacency(FILE*fp, const int numOfMaxVertices, int* maxVertex){
    int** matrix =(int**)malloc(sizeof(int) * (numOfMaxVertices + 1));
    for (int i = 0; i <= numOfMaxVertices; ++i){
        matrix[i] = (int*)malloc(sizeof(int) * (numOfMaxVertices+1));
        memset(matrix[i], 0, sizeof(int) * (numOfMaxVertices+1));
    }
    for (int i = 0; i < numOfMaxVertices; ++i) {
        int begin, end, biggerVertex;
        fscanf(fp, "%d %d", &begin, &end);
        biggerVertex = (begin > end ? begin : end);
        if (biggerVertex > *maxVertex)
            *maxVertex = biggerVertex;
        ++matrix[begin][end];
        ++matrix[end][begin];
    }
    return matrix;
}


int* counterOddVertices(int** matrix, int numOfVertices, int* numOfOddVertices){
    int* deg = (int*)malloc(sizeof(int) * numOfVertices);
    memset(deg, 0, sizeof(int)*numOfVertices);
    for (int i = 0; i <= numOfVertices; ++i){
        for (int j = 0; j <= numOfVertices; ++j)
        deg[i]+=matrix[i][j];
    }
    for (int i = 0; i < numOfVertices; ++i){
        if (deg[i] % 2)
            *numOfOddVertices+=1;
    }
    return deg;
}


int main(){
    FILE* fp = fopen("in.txt", "r");
    int numOfEdges, numOfVertices;
    int numOfOddVertices = 0;
    int maxVertex = -1;
    fscanf(fp, "%d", &numOfEdges);
    int maxNumOfVertices = numOfEdges;
    int*deg;
    int** graph = initMatrixAdjacency(fp, maxNumOfVertices, &maxVertex); // adjacency list
    if (maxVertex > -1) {
        numOfVertices = maxVertex + 1;
        deg = counterOddVertices(graph, numOfVertices, &numOfOddVertices);
    }
    else{
        printf("There is no vertices!");
        return 0;
    }
    if (numOfOddVertices == 2 || numOfOddVertices == 0) // number of odd vertices need to be < 2 (zero or two)
        searchEulerPath(graph, deg, numOfVertices);
    else
        printf("NO");
    fclose(fp);
    return 0;
}