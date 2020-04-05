#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define HEAP struct list1


HEAP{
    int* harr; // pointer to array of elements in heap;
    int capacity; // maximum possible elements of min heap
    int heap_size; // current number of elements in heap
};


void siftDown(); // элемент сверху нарушает свойство кучи





void printHeap(HEAP*ptr){
    for (int i = 0; i < ptr->heap_size; ++i)
        printf("%d ", ptr->harr[i]);
    printf("\n");
}


int parent(int i){
    return (i-1)/2;
}


int left(int i){
    return (2*i+1);
}


int right(int i){
    return (2*i+2);
}


void swap (int*x , int*y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void siftUp(HEAP* ptr, int idx){ // элемент снизу  нарушает свойство кучи
    while (idx != 0 && ptr->harr[parent(idx)] > ptr -> harr[idx]) {
        swap(&ptr->harr[parent(idx)], &ptr->harr[idx]);
        idx = parent(idx);
    }
}


void MinHeapify(HEAP*ptr, int i){ // при извлечении рута рекурсивно спускаемся по дереву, испрпавляя его
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < ptr->heap_size && ptr->harr[l] < ptr -> harr [i])
        smallest = l;
    if (r < ptr->heap_size && ptr->harr[r] < ptr -> harr [smallest])
        smallest = r;
    if (smallest != i){
        swap(&ptr -> harr[i], &ptr -> harr[smallest]);
        MinHeapify(ptr, smallest);
    }
}


int extractMin(HEAP*ptr){ // замена ключа в корне (берём последний элемент в массиве) + sift down
    if (ptr -> heap_size <= 0)
        return INT_MAX;
    if (ptr -> heap_size == 1){
        ptr -> heap_size--;
        return ptr -> harr[0];
    }

    int root = ptr -> harr[0];
    ptr -> harr[0] = ptr -> harr[ptr -> heap_size - 1];
    ptr -> heap_size--;
    MinHeapify(ptr, 0);
    return root;
}


void insertKey(HEAP*ptr, int k){ // добавление + sift up
    if (ptr->heap_size == ptr->capacity) {
        printf("Overflow, my brother");
        return;
    }
    ptr->heap_size++;
    int i = ptr->heap_size - 1;
    ptr -> harr[i] = k;
    siftUp(ptr, i);
}


void decreaseKey(HEAP*ptr, int i, int new_val){ // уменьшение ключа + sift up
    ptr -> harr[i] = new_val;
    siftUp(ptr, i);
}


void deleteKey(HEAP*ptr, int i){ // decrease key до корня + extractMin
    decreaseKey(ptr, i, INT_MIN);
    extractMin(ptr);
}


int getMin(HEAP*ptr){
    return ptr->harr[0];
}


void HeapSort(HEAP*ptr){
   while(ptr -> heap_size > 0)
        printf("%d ", extractMin(ptr));
    printf("\n");
}




HEAP* MinHeap(int cap){
    HEAP* tmp = (HEAP*)malloc(sizeof(HEAP));
    int* harray = (int*)malloc(sizeof(int) * cap);
    tmp->heap_size = 0;
    tmp->capacity = cap;
    tmp -> harr = harray;
    return tmp;
}



int main() {
    int n;
    scanf("%d", &n);
    HEAP*ptr = MinHeap(n);
    for (int i = 0; i < n; ++i){
        int num;
        scanf("%d", &num);
        insertKey(ptr, num);
    }
    /*printHeap(ptr);
    printf("%d\n", getMin(ptr));
    extractMin(ptr);
    printHeap(ptr);
    deleteKey(ptr, 1);
    printHeap(ptr);*/
    HeapSort(ptr);
    free(ptr);
    return 0;
}
