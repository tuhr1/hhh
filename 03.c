#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 0-1 背包问题的动态规划实现
void knapsack(int n, int c, int values[], int weights[]) {
    // 动态分配二维数组 dp[n + 1][c + 1]
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
        dp[i] = (int*)malloc((c + 1) * sizeof(int));
    // 初始化 dp 数组
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
    // 打印 dp 矩阵
    printf("DP 矩阵:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= c; w++)
            printf("%4d ", dp[i][w]);
        printf("\n");
    }
    // 最终的最大价值
    printf("\n最大价值: %d\n", dp[n][c]);
    // 释放动态分配的内存
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);
}

int main() {
    int n;            // 物品数量
    int vmin, vmax;   // 每个物品最低和最高的价值
    int wmin, wmax;   // 每个物品最小和最大的重量
    int c;            // 背包的最大容量
    // 输入物品数量、价值范围、重量范围和背包容量
    printf("请输入物品数量、重量范围（wmin wmax）、每个物品的价值范围（vmin vmax）、背包的最大容量:\n");
    scanf("%d %d %d %d %d %d", &n, &wmin, &wmax, &vmin, &vmax, &c);
    // 检查输入有效性
    if (vmin > vmax || wmin > wmax || n <= 0 || c <= 0) {
        printf("输入的范围无效，请重新运行程序并输入正确的范围。\n");
        return 1;
    }
    // 初始化随机数种子
    srand((unsigned int)time(NULL));
    // 动态分配物品的价值和重量数组
    int* values = (int*)malloc(n * sizeof(int));
    int* weights = (int*)malloc(n * sizeof(int));
    // 生成随机的物品价值和重量
    printf("\n生成的物品数据（价值和重量）：\n");
    for (int i = 0; i < n; i++) {
        values[i] = vmin + rand() % (vmax - vmin + 1);     // 随机生成在 [vmin, vmax] 范围内的价值
        weights[i] = wmin + rand() % (wmax - wmin + 1);    // 随机生成在 [wmin, wmax] 范围内的重量
        printf("物品 %d: 价值 = %d, 重量 = %d\n", i + 1, values[i], weights[i]);
    }
    printf("\n");
    // 调用 knapsack 函数计算并输出 dp 矩阵和最大价值
    knapsack(n, c, values, weights);
    // 释放动态分配的内存
    free(values);
    free(weights);
    return 0;
}