//
// Created by asus on 2020/2/16.
//

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
    int size;
    int *array;
} intArray;

intArray *a;

void setArray() {
    a = malloc(sizeof(intArray));
    a->size = 9;
    a->array = malloc(sizeof(int) * a->size);
    a->array[0] = 1;
    a->array[1] = 9;
    a->array[2] = 5;
    a->array[3] = 6;
    a->array[4] = 3;
    a->array[5] = 8;
    a->array[6] = 4;
    a->array[7] = 7;
    a->array[8] = 2;
}

void merge(int begin, int end) {
    int mid = (begin + end) / 2;
    int i = begin, p = begin, j = mid + 1;

    int *tmp = malloc(sizeof(int) * (end - begin + 1));
    for (int k = begin; k <= end; ++k) {
        tmp[k - begin] = a->array[k];
    }

    while (i <= mid && j <= end) {
        if (tmp[i - begin] > tmp[j - begin]) {
            a->array[p] = tmp[j - begin];
            j++;
        } else {
            a->array[p] = tmp[i - begin];
            i++;
        }
        p++;
    }
    for (; i <= mid; ++i) {
        a->array[p] = tmp[i - begin];
        p++;
    }
    for (; j <= end; ++j) {
        a->array[p] = tmp[j - begin];
        p++;
    }

    free(tmp);
}

void *executor(void *param) {
    int begin = ((int *) param)[0];
    int end = ((int *) param)[1];
    int mid = (begin + end) / 2;

    if (begin == end) {
        return NULL;
    }

    pthread_t tid1;
    pthread_attr_t attr1;
    int param1[2];
    param1[0] = begin;
    param1[1] = mid;
    pthread_attr_init(&attr1);
    pthread_create(&tid1, &attr1, executor, param1);
    /*executor(param1);*/

    pthread_t tid2;
    pthread_attr_t attr2;
    int param2[2];
    param2[0] = mid + 1;
    param2[1] = end;
    pthread_attr_init(&attr2);
    pthread_create(&tid2, &attr2, executor, param2);
    /*executor(param2);*/

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    merge(begin, end);
    return NULL;
}

void sort() {
    pthread_t tid;
    pthread_attr_t attr;
    int param[2];
    param[0] = 0;
    param[1] = a->size - 1;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, executor, param);
    pthread_join(tid, NULL);
}