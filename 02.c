#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 全局变量，用于统计每种排序的比较次数
long long selectionComparisons = 0;
long long bubbleComparisons = 0;
long long quickComparisons = 0;
long long insertionComparisons = 0;
long long mergeComparisons = 0;

// 生成随机数的函数
int test(int range) {
    return rand() % range + 1;
}

// 选择排序函数
void selectionSort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            selectionComparisons++; // 记录比较次数
            if (arr[j] < arr[min])
                min = j;
        }
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

// 冒泡排序函数
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++) {
            bubbleComparisons++; // 记录比较次数
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
}

// 快速排序函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        quickComparisons++; // 记录比较次数
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 插入排序函数
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0) {
            insertionComparisons++; // 记录比较次数
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// 归并排序函数
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) {
        printf("内存分配失败\n");
        return;
    }
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        mergeComparisons++; // 记录比较次数
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    srand((unsigned int)time(NULL)); // 初始化随机数种子
    int n1 = 10000, n2 = 10000;
    int arr1[10000], arr2[10000], backup1[10000], backup2[10000];
    struct SortTimeArray {
        char name[20];
        double timeArray1, timeArray2;
        long long comparisons1, comparisons2;
    } timeArrays[5];

    // 数据集1
    for (int i = 0; i < n1; i++)
        arr1[i] = test(100000);
    memcpy(backup1, arr1, n1 * sizeof(int));

    // 数据集2
    for (int i = 0; i < n2; i++)
        arr2[i] = test(20);
    memcpy(backup2, arr2, n2 * sizeof(int));

    // 排序并记录数据集1和数据集2的时间和比较次数

    // 选择排序（数据集1）
    clock_t start = clock();
    selectionSort(arr1, n1);
    clock_t end = clock();
    timeArrays[0] = (struct SortTimeArray){ "选择排序", (double)(end - start) / CLOCKS_PER_SEC, 0, selectionComparisons, 0 };
    memcpy(arr1, backup1, n1 * sizeof(int));
    selectionComparisons = 0;

    // 冒泡排序（数据集1）
    start = clock();
    bubbleSort(arr1, n1);
    end = clock();
    timeArrays[1] = (struct SortTimeArray){ "冒泡排序", (double)(end - start) / CLOCKS_PER_SEC, 0, bubbleComparisons, 0 };
    memcpy(arr1, backup1, n1 * sizeof(int));
    bubbleComparisons = 0;

    // 快速排序（数据集1）
    start = clock();
    quickSort(arr1, 0, n1 - 1);
    end = clock();
    timeArrays[2] = (struct SortTimeArray){ "快速排序", (double)(end - start) / CLOCKS_PER_SEC, 0, quickComparisons, 0 };
    memcpy(arr1, backup1, n1 * sizeof(int));
    quickComparisons = 0;

    // 插入排序（数据集1）
    start = clock();
    insertionSort(arr1, n1);
    end = clock();
    timeArrays[3] = (struct SortTimeArray){ "插入排序", (double)(end - start) / CLOCKS_PER_SEC, 0, insertionComparisons, 0 };
    memcpy(arr1, backup1, n1 * sizeof(int));
    insertionComparisons = 0;

    // 归并排序（数据集1）
    start = clock();
    mergeSort(arr1, 0, n1 - 1);
    end = clock();
    timeArrays[4] = (struct SortTimeArray){ "归并排序", (double)(end - start) / CLOCKS_PER_SEC, 0, mergeComparisons, 0 };
    memcpy(arr1, backup1, n1 * sizeof(int));
    mergeComparisons = 0;

    // 数据集2的所有排序
    // 选择排序（数据集2）
    start = clock();
    selectionSort(arr2, n2);
    end = clock();
    timeArrays[0].timeArray2 = (double)(end - start) / CLOCKS_PER_SEC;
    timeArrays[0].comparisons2 = selectionComparisons;
    memcpy(arr2, backup2, n2 * sizeof(int));
    selectionComparisons = 0;

    // 冒泡排序（数据集2）
    start = clock();
    bubbleSort(arr2, n2);
    end = clock();
    timeArrays[1].timeArray2 = (double)(end - start) / CLOCKS_PER_SEC;
    timeArrays[1].comparisons2 = bubbleComparisons;
    memcpy(arr2, backup2, n2 * sizeof(int));
    bubbleComparisons = 0;

    // 快速排序（数据集2）
    start = clock();
    quickSort(arr2, 0, n2 - 1);
    end = clock();
    timeArrays[2].timeArray2 = (double)(end - start) / CLOCKS_PER_SEC;
    timeArrays[2].comparisons2 = quickComparisons;
    memcpy(arr2, backup2, n2 * sizeof(int));
    quickComparisons = 0;

    // 插入排序（数据集2）
    start = clock();
    insertionSort(arr2, n2);
    end = clock();
    timeArrays[3].timeArray2 = (double)(end - start) / CLOCKS_PER_SEC;
    timeArrays[3].comparisons2 = insertionComparisons;
    memcpy(arr2, backup2, n2 * sizeof(int));
    insertionComparisons = 0;

    // 归并排序（数据集2）
    start = clock();
    mergeSort(arr2, 0, n2 - 1);
    end = clock();
    timeArrays[4].timeArray2 = (double)(end - start) / CLOCKS_PER_SEC;
    timeArrays[4].comparisons2 = mergeComparisons;
    memcpy(arr2, backup2, n2 * sizeof(int));
    mergeComparisons = 0;

    // 输出结果

    printf("\n数据集1 (10000个范围1-20的随机数)结果:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s：时间 = %.6f 秒，比较次数 = %lld\n", timeArrays[i].name, timeArrays[i].timeArray2, timeArrays[i].comparisons2);
    }

    printf("\n数据集2 (10000个范围1-100000的随机数)结果:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s：时间 = %.6f 秒，比较次数 = %lld\n", timeArrays[i].name, timeArrays[i].timeArray1, timeArrays[i].comparisons1);
    }

    return 0;
}