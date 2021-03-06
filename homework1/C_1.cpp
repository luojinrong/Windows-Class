#include<stdio.h>

const int maxn = 105;
int n, max_index;
double arr[maxn], max, sum;

void GetSumAndMaxIndex() {//全局变量处理
	max = sum = arr[0];
	max_index = 0;
	for (int i = 1; i < n; i++) {
		sum += arr[i];
		if (max < arr[i]) {
			max = arr[i];
			max_index = i;
		}
	}
}

double GetSumAndMaxIndex(double a[], int length, int* index) {//指针传参处理
	double sum = a[0], max = a[0];
	*index = 0;
	for (int i = 1; i < length; i++) {
		sum += a[i];
		if (max < a[i]) {
			max = arr[i];
			*index = i;
		}
	}
	return sum;
}

int main() {
	while (printf("输入一个整数n，表示接下来将输入n个数（n=0时输入结束）：\n"), scanf("%d", &n), n) {
		for (int i = 0; i < n; i++) {
			scanf("%lf", &arr[i]);
		}
		GetSumAndMaxIndex();
		printf("方法一：\n数组元素和为：%lf, 最大值为第 %d 项\n", sum, max_index);
		printf("方法二：\n数组元素和为：%lf, 最大值为第 %d 项\n", GetSumAndMaxIndex(arr, n, &max_index), max_index);
	}
}