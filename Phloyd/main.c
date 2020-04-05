#include <stdio.h>
#include <malloc.h>
#include <limits.h>

int main() {
    long long int* matrix;
    int n;
    FILE* fp;
    fp = fopen("in.txt", "r");
    fscanf(fp,"%d",&n);
    matrix = (long long int*)malloc(n*n* sizeof(long long int));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j){
            fscanf(fp, "%lld", matrix+ i*n +j);
            if (*(matrix+ i*n +j) == 0)
            *(matrix+ i*n +j) = INT_MAX-1;
        }
    }
    for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (*(matrix + i*n +j) > *(matrix + i*n + k) + *(matrix + k*n +j))
                        *(matrix + i*n +j) = *(matrix + i*n + k) + *(matrix + k*n +j);
                    printf("%lld ", *(matrix + i*n +j));
                }
                printf("\n");
            }
    }
    return 0;
}
