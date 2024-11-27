#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ����������ĺ���
int test()
{
    return rand();
}

// ѡ��������
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

// ð��������
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

// ����������
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
        printf("�ڴ����ʧ��\n");
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

// ����������
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

// ����������
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

// �ϲ����������� arr[l..m] �� arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; // ��������Ĵ�С
    int n2 = r - m;     // ��������Ĵ�С
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    // ����ڴ�����Ƿ�ɹ�
    if (L == NULL || R == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return;
    }
    // �����ݸ��Ƶ���ʱ���� L[] �� R[] ��
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // �ϲ���ʱ���鵽 arr[l..r]
    i = 0;   // �����������ʼ����
    j = 0;   // �����������ʼ����
    k = l;   // �ϲ�����������ʼ����
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

    // ���� L[] ʣ���Ԫ��
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // ���� R[] ʣ���Ԫ��
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// �ݹ�ʵ�ֹ鲢����
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2; // ��ȷ�����м��
        mergeSort(arr, l, m);     // ������벿��
        mergeSort(arr, m + 1, r); // �����Ұ벿��
        merge(arr, l, m, r);      // �ϲ���������������
    }
}

// ����ṹ�壬���ڴ洢�������ƺ�ʱ��
struct SortTimeArray
{
    char name[20];
    double timeArray;
};

// ����ṹ�����飨��ʱ������
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
    srand((unsigned int)time(NULL)); // ��ʼ�����������
    int i = 0, n = 0, arr[100000], a[100000]; // ��������洢�����
    struct SortTimeArray timeArrays[6]; // �����ṹ���������ڴ洢����ʱ�������

    printf("������Ҫ���ɵ����������: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) // ���� n �����������������
        arr[i] = test();
    for (i = 0; i < n; i++)
        a[i] = arr[i];

    // ѡ������
    clock_t start1 = clock();
    selectionSort(arr, n);
    clock_t end1 = clock();
    double duration1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("ѡ�����򻨷ѵ�ʱ��: %.6f ��\n", duration1);
    strcpy(timeArrays[0].name, "ѡ������");
    timeArrays[0].timeArray = duration1;

    // �ָ�ԭ����
    memcpy(arr, a, n * sizeof(int));

    // ð������
    clock_t start2 = clock();
    bubbleSort(arr, n);
    clock_t end2 = clock();
    double duration2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("ð�����򻨷ѵ�ʱ��: %.6f ��\n", duration2);
    strcpy(timeArrays[1].name, "ð������");
    timeArrays[1].timeArray = duration2;

    memcpy(arr, a, n * sizeof(int));

    // ��������
    clock_t start3 = clock();
    countingSort(arr, n);
    clock_t end3 = clock();
    double duration3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf("�������򻨷ѵ�ʱ��: %.6f ��\n", duration3);
    strcpy(timeArrays[2].name, "��������");
    timeArrays[2].timeArray = duration3;

    memcpy(arr, a, n * sizeof(int));

    // ��������
    clock_t start4 = clock();
    quickSort(arr, 0, n - 1);
    clock_t end4 = clock();
    double duration4 = (double)(end4 - start4) / CLOCKS_PER_SEC;
    printf("�������򻨷ѵ�ʱ��: %.6f ��\n", duration4);
    strcpy(timeArrays[3].name, "��������");
    timeArrays[3].timeArray = duration4;

    memcpy(arr, a, n * sizeof(int));

    // ��������
    clock_t start5 = clock();
    insertionSort(arr, n);
    clock_t end5 = clock();
    double duration5 = (double)(end5 - start5) / CLOCKS_PER_SEC;
    printf("�������򻨷ѵ�ʱ��: %.6f ��\n", duration5);
    strcpy(timeArrays[4].name, "��������");
    timeArrays[4].timeArray = duration5;

    memcpy(arr, a, n * sizeof(int));

    // �鲢����
    clock_t start6 = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end6 = clock();
    double duration6 = (double)(end6 - start6) / CLOCKS_PER_SEC;
    printf("�鲢���򻨷ѵ�ʱ��: %.6f ��\n", duration6);
    strcpy(timeArrays[5].name, "�鲢����");
    timeArrays[5].timeArray = duration6;

    // �������㷨��ʱ���������
    sortTimeArrays(timeArrays, 6);
    printf("\n�������㷨��ʱ������:\n");
    for (i = 0; i < 6; i++)
        printf("%s: %.6f ��\n", timeArrays[i].name, timeArrays[i].timeArray);

    return 0;
}