#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define THINGS struct list


THINGS{
    int numOfThing;
    THINGS* next;
};



void popStack(THINGS*top){
    THINGS* delElem;
    delElem = top -> next;
    top -> next = top -> next -> next;
    printf("%d ", delElem -> numOfThing);
    free(delElem);
}


void pushStack(THINGS* top, int num){
    THINGS* tmp = (THINGS*)malloc(sizeof(THINGS));
    tmp -> numOfThing = num;
    tmp -> next = top -> next;
    top -> next = tmp;
}


int isNotEmpty(THINGS*top){
    return (int)(top ->next);
}


int max(const int x, const int y){
    return (x > y ? x : y);
}


void printStack(THINGS*top){
    while(isNotEmpty(top))
        popStack(top);
    free(top);
}


int findMaxCostIndex(const int* array, const int maxWeight){
    int maxCost = 0;
    int index;
    for(int i = 1; i <= maxWeight; ++i)
        if (array[i] > maxCost){
            maxCost = array[i];
            index = i;
        }
    if (!maxCost)
        return 0;
    else
        return index;
}


THINGS* pushAns(int** bestTotalCost, int** listOfThings, const int numOfThings, const int maxWeight){
    THINGS* top = (THINGS*)malloc(sizeof(THINGS));
    top -> next = NULL;
    int index = findMaxCostIndex(bestTotalCost[numOfThings], maxWeight); // go from the end - choose max cost
    for (int step = numOfThings; step > 0; --step){
        if (bestTotalCost[step][index] != bestTotalCost[step-1][index]){ // if cost isn't the same - drop this thing and change index
            pushStack(top, step);
            index -= listOfThings[step - 1][1];
        }
    }
    for(int i = 0; i < numOfThings; ++i) {
        free(listOfThings[i]);
        free(bestTotalCost[i]);
    }
    free(bestTotalCost[numOfThings+1]);
    free(bestTotalCost);
    free(listOfThings);
    return top;
}


int** puttingThings(const int maxWeight, const int numOfThings, int** listOfThings){
    int** bestTotalCost = (int**)malloc(sizeof(int*) * (numOfThings+1)); // first column = numOfTHings + 1 = steps + 1
    for (int i = 0; i <= numOfThings; ++i){
        bestTotalCost[i] = (int*) malloc(sizeof(int) * (maxWeight + 1)); // strings = current loading of backpack
        memset(bestTotalCost[i], 0, sizeof(int) * (maxWeight + 1));
    }
    for (int step = 1; step <= numOfThings; ++step) { // we decide: put this thing in backpack or not
        int costOfThing = listOfThings[step - 1][0];
        int weightOfThing = listOfThings[step - 1][1];
        for (int capacity = 0; capacity <= maxWeight; ++capacity){
            if (weightOfThing <= capacity) // if weight < current capacity - choose costs
                bestTotalCost[step][capacity] = max(bestTotalCost[step-1][capacity],
                                                    bestTotalCost[step - 1][capacity - weightOfThing] + costOfThing);
            else // just don't put this thing
                bestTotalCost[step][capacity] = bestTotalCost[step-1][capacity];
       }
    }
    return bestTotalCost;
}


int** initialInputData(int* numOfThings){
    scanf("%d", numOfThings);
    int** listOfThings = (int**)malloc(sizeof(int*) * *numOfThings);
    for (int i = 0; i < *numOfThings; ++i){
        listOfThings[i]=(int*)malloc(sizeof(int) * 2);
        scanf("%d ", &listOfThings[i][0]); // first index - cost
        scanf("%d", &listOfThings[i][1]); // second index - weight
    }
    return listOfThings;
}


int main(){
    int numOfThings;
    int maxWeight;
    scanf("%d", &maxWeight);
    int** listOfThings = initialInputData(&numOfThings); // array of things: num, cost, weight
    int** pushingThingsInBackpack = puttingThings(maxWeight, numOfThings, listOfThings); // table of pushing
    THINGS* chosenThings = pushAns(pushingThingsInBackpack, listOfThings, numOfThings, maxWeight);
    printStack(chosenThings);
    return 0;
}