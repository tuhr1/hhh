#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 0-1 ��������Ķ�̬�滮ʵ��
void knapsack(int n, int c, int values[], int weights[]) {
    // ��̬�����ά���� dp[n + 1][c + 1]
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
        dp[i] = (int*)malloc((c + 1) * sizeof(int));
    // ��ʼ�� dp ����
    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= c; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w) {
                if (dp[i - 1][w] > dp[i - 1][w - weights[i - 1]] + values[i - 1])
                    dp[i][w] = dp[i - 1][w];
                else
                    dp[i][w] = dp[i - 1][w - weights[i - 1]] + values[i - 1];
            }
            else
                dp[i][w] = dp[i - 1][w];
        }
    // ��ӡ dp ����
    printf("DP ����:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= c; w++)
            printf("%4d ", dp[i][w]);
        printf("\n");
    }
    // ���յ�����ֵ
    printf("\n����ֵ: %d\n", dp[n][c]);
    // �ͷŶ�̬������ڴ�
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
}

int main() {
    int n;            // ��Ʒ����
    int vmin, vmax;   // ÿ����Ʒ��ͺ���ߵļ�ֵ
    int wmin, wmax;   // ÿ����Ʒ��С����������
    int c;            // �������������
    // ������Ʒ��������ֵ��Χ��������Χ�ͱ�������
    printf("��������Ʒ������������Χ��wmin wmax����ÿ����Ʒ�ļ�ֵ��Χ��vmin vmax�����������������:\n");
    scanf("%d %d %d %d %d %d", &n, &wmin, &wmax, &vmin, &vmax, &c);
    // ���������Ч��
    if (vmin > vmax || wmin > wmax || n <= 0 || c <= 0) {
        printf("����ķ�Χ��Ч�����������г���������ȷ�ķ�Χ��\n");
        return 1;
    }
    // ��ʼ�����������
    srand((unsigned int)time(NULL));
    // ��̬������Ʒ�ļ�ֵ����������
    int* values = (int*)malloc(n * sizeof(int));
    int* weights = (int*)malloc(n * sizeof(int));
    // �����������Ʒ��ֵ������
    printf("\n���ɵ���Ʒ���ݣ���ֵ����������\n");
    for (int i = 0; i < n; i++) {
        values[i] = vmin + rand() % (vmax - vmin + 1);     // ��������� [vmin, vmax] ��Χ�ڵļ�ֵ
        weights[i] = wmin + rand() % (wmax - wmin + 1);    // ��������� [wmin, wmax] ��Χ�ڵ�����
        printf("��Ʒ %d: ��ֵ = %d, ���� = %d\n", i + 1, values[i], weights[i]);
    }
    printf("\n");
    // ���� knapsack �������㲢��� dp ���������ֵ
    knapsack(n, c, values, weights);
    // �ͷŶ�̬������ڴ�
    free(values);
    free(weights);
    return 0;
}