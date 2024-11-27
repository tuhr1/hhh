#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 生成随机数的函数
int test()
{
    return rand();
}

// 选择排序函数
void selectionSort(int arr[], int n)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

// 冒泡排序函数
void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

// 计数排序函数
void countingSort(int arr[], int n)
{
    int i, max = arr[0], min = arr[0];
    for (i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    int range = max - min + 1;
    int* count = (int*)malloc(range * sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));
    if (count == NULL || output == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    for (i = 0; i < range; i++)
        count[i] = 0;
    for (i = 0; i < n; i++)
        count[arr[i] - min]++;
    for (i = 1; i < range; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    free(count);
    free(output);
}

// 快速排序函数
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 插入排序函数
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 合并两个子数组 arr[l..m] 和 arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; // 左子数组的大小
    int n2 = r - m;     // 右子数组的大小
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    // 检查内存分配是否成功
    if (L == NULL || R == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    // 将数据复制到临时数组 L[] 和 R[] 中
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // 合并临时数组到 arr[l..r]
    i = 0;   // 左子数组的起始索引
    j = 0;   // 右子数组的起始索引
    k = l;   // 合并后的数组的起始索引
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 复制 L[] 剩余的元素
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // 复制 R[] 剩余的元素
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// 递归实现归并排序
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2; // 正确计算中间点
        mergeSort(arr, l, m);     // 排序左半部分
        mergeSort(arr, m + 1, r); // 排序右半部分
        merge(arr, l, m, r);      // 合并两个有序子数组
    }
}

// 定义结构体，用于存储排序名称和时间
struct SortTimeArray
{
    char name[20];
    double timeArray;
};

// 排序结构体数组（按时间排序）
void sortTimeArrays(struct SortTimeArray timeArrays[], int n)
{
    int i, j;
    struct SortTimeArray temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (timeArrays[i].timeArray > timeArrays[j].timeArray)
            {
                temp = timeArrays[i];
                timeArrays[i] = timeArrays[j];
                timeArrays[j] = temp;
            }
}

int main()
{
    srand((unsigned int)time(NULL)); // 初始化随机数种子
    int i = 0, n = 0, arr[100000], a[100000]; // 定义数组存储随机数
    struct SortTimeArray timeArrays[6]; // 声明结构体数组用于存储排序时间和名称

    printf("请输入要生成的随机数个数: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) // 生成 n 个随机数并存入数组
        arr[i] = test();
    for (i = 0; i < n; i++)
        a[i] = arr[i];

    // 选择排序
    clock_t start1 = clock();
    selectionSort(arr, n);
    clock_t end1 = clock();
    double duration1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("选择排序花费的时间: %.6f 秒\n", duration1);
    strcpy(timeArrays[0].name, "选择排序");
    timeArrays[0].timeArray = duration1;

    // 恢复原数组
    memcpy(arr, a, n * sizeof(int));

    // 冒泡排序
    clock_t start2 = clock();
    bubbleSort(arr, n);
    clock_t end2 = clock();
    double duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("冒泡排序花费的时间: %.6f 秒\n", duration2);
    strcpy(timeArrays[1].name, "冒泡排序");
    timeArrays[1].timeArray = duration2;

    memcpy(arr, a, n * sizeof(int));

    // 计数排序
    clock_t start3 = clock();
    countingSort(arr, n);
    clock_t end3 = clock();
    double duration3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf("计数排序花费的时间: %.6f 秒\n", duration3);
    strcpy(timeArrays[2].name, "计数排序");
    timeArrays[2].timeArray = duration3;

    memcpy(arr, a, n * sizeof(int));

    // 快速排序
    clock_t start4 = clock();
    quickSort(arr, 0, n - 1);
    clock_t end4 = clock();
    double duration4 = (double)(end4 - start4) / CLOCKS_PER_SEC;
    printf("快速排序花费的时间: %.6f 秒\n", duration4);
    strcpy(timeArrays[3].name, "快速排序");
    timeArrays[3].timeArray = duration4;

    memcpy(arr, a, n * sizeof(int));

    // 插入排序
    clock_t start5 = clock();
    insertionSort(arr, n);
    clock_t end5 = clock();
    double duration5 = (double)(end5 - start5) / CLOCKS_PER_SEC;
    printf("插入排序花费的时间: %.6f 秒\n", duration5);
    strcpy(timeArrays[4].name, "插入排序");
    timeArrays[4].timeArray = duration5;

    memcpy(arr, a, n * sizeof(int));

    // 归并排序
    clock_t start6 = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end6 = clock();
    double duration6 = (double)(end6 - start6) / CLOCKS_PER_SEC;
    printf("归并排序花费的时间: %.6f 秒\n", duration6);
    strcpy(timeArrays[5].name, "归并排序");
    timeArrays[5].timeArray = duration6;

    // 对排序算法按时间进行排序
    sortTimeArrays(timeArrays, 6);
    printf("\n各排序算法按时间排序:\n");
    for (i = 0; i < 6; i++)
        printf("%s: %.6f 秒\n", timeArrays[i].name, timeArrays[i].timeArray);

    return 0;
}