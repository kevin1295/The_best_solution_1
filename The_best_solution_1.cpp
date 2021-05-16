// The_best_solution_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
#include <algorithm>
#include <Windows.h>

using namespace std;

const long long N = 25000;									// 10*x^2
double t[3] = { 0, 1, 3 };									// time of car and man going past a point

struct Examples {
	bool Statements[51];
} Ex[N + 1];
int Parkpoint[N + 1][4], Possibility[51];					// 50 parking spots
double Time[N + 1][4], Sum_time[4][21][21];
struct Datas {
	double Allsum, Average, Variance;
}datas[4][3][21];
void resets() {
	memset(datas, 0, sizeof(datas));
}

int main()
{
	srand(time(0));											// initialization
	printf("--------------------monitoring--------------------\n");

	for (int i = 1; i <= 50; i++) {							// arrange possibility
		Possibility[i] = N - 10 * i * i;
		if (Possibility[i] < 0) {
			Possibility[i] = 0;
		}
	}

	for (int i = 1; i <= 50; i++) {							// build point No.1
		long long j = Possibility[i], points = 0;
		printf("%lld\n", j);								// monitor how many cars have parked on the point
		while (j >= 0) {									// have j points rest
			long long rest = rand() % (N - points + 1) + 1;
			for (int k = 1; k <= N; k++) {
				if (Ex[k].Statements[i] == false) {
					--rest;
					if (rest == 1) {
						Ex[k].Statements[i] = true;
						points++;
						break;
					}
				}
			}
			j--;
		}
	}

	FILE* stream1;											// prepare to write into documents

	freopen_s(&stream1, "out.txt", "w", stdout);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 51; j++) {
			printf("%c", Ex[i].Statements[j] ? 'x' : 'o');
		}
		printf("\n");
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 50; j > 0; j--) {
			if ((Ex[i].Statements[j - 1] == true) && (Ex[i].Statements[j] == false) && (Ex[i].Statements[j + 1] == true)) {					// "xox"
				Parkpoint[i][1] = j;
				break;
			}
			if (j == 1) {
				for (int j = 1; j <= 50; j++) {
					if (Ex[i].Statements[j] == false) {
						Parkpoint[i][1] = (t[2] - t[1]) / (t[1] + t[2]) * j;
						break;
					}
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 50; j > 0; j--) {
			if ((Ex[i].Statements[j - 1] == true) && (Ex[i].Statements[j] == false) && (Ex[i].Statements[j + 1] == false) && (Ex[i].Statements[j + 2] == true)) {					// "xoox"
				Parkpoint[i][2] = j;
				break;
			}
			if (j == 1) {
				for (int j = 1; j <= 50; j++) {
					if (Ex[i].Statements[j] == false) {
						Parkpoint[i][2] = (t[2] - t[1]) / (t[1] + t[2]) * j;
						break;
					}
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 47; j > 1; j--) {
			if ((Ex[i].Statements[j - 1] == true) && (Ex[i].Statements[j] == false) && (Ex[i].Statements[j + 1] == false) && (Ex[i].Statements[j + 2] == false) && (Ex[i].Statements[j+3] == true)) {					// "xooox"
				Parkpoint[i][3] = j;
				break;
			}
			if (j == 1) {
				for (int j = 1; j <= 50; j++) {
					if (Ex[i].Statements[j] == false) {
						Parkpoint[i][3] = (t[2] - t[1]) / (t[1] + t[2]) * j;
						break;
					}
				}
			}
		}
	}

	freopen_s(&stream1, "result.csv", "w", stdout);
	printf("--------------------results---------------------\n");
	printf("man_speed,car_speed,average_time_use_of_method_1,average_time_use_of_method_2,average_time_use_of_method_3\n");

	int labels[3] = { 0,0,0 };
	for (t[1] = 1.0; t[1] <= 3.0; t[1] += 0.1) {
		labels[1]++;
		labels[2] = 0;
		for (t[2] = 3.0; t[2] <= 4.9; t[2] += 0.1) {
			labels[2]++;
			printf("%llf,%llf,", t[1], t[2]);
			Sum_time[1][labels[1]][labels[2]] = 0;
			Sum_time[2][labels[1]][labels[2]] = 0;
			Sum_time[3][labels[1]][labels[2]] = 0;
			for (int i = 1; i <= N; i++) {
				Time[i][1] = (50 - Parkpoint[i][1]) * t[1] + Parkpoint[i][1] * t[2];
				Time[i][2] = (50 - Parkpoint[i][2]) * t[1] + Parkpoint[i][2] * t[2];
				Time[i][3] = (50 - Parkpoint[i][3]) * t[1] + Parkpoint[i][3] * t[2];
				Sum_time[1][labels[1]][labels[2]] += Time[i][1];
				Sum_time[2][labels[1]][labels[2]] += Time[i][2];
				Sum_time[3][labels[1]][labels[2]] += Time[i][3];
			}

			printf("%llf,", Sum_time[1][labels[1]][labels[2]] / N);
			printf("%llf,", Sum_time[2][labels[1]][labels[2]] / N);
			printf("%llf\n", Sum_time[3][labels[1]][labels[2]] / N);

		}
	}
	
	freopen_s(&stream1, "CON", "w", stdout);
	resets();
	for (labels[1] = 1; labels[1] <= 20; labels[1]++) {
		for (labels[2] = 1; labels[2] <= 20; labels[2]++) {
			datas[1][1][labels[1]].Allsum += (Sum_time[1][labels[1]][labels[2]] / N);
			datas[1][2][labels[1]].Allsum += (Sum_time[1][labels[2]][labels[1]] / N);
			datas[2][1][labels[1]].Allsum += (Sum_time[2][labels[1]][labels[2]] / N);
			datas[2][2][labels[1]].Allsum += (Sum_time[2][labels[2]][labels[1]] / N);
			datas[3][1][labels[1]].Allsum += (Sum_time[3][labels[1]][labels[2]] / N);
			datas[3][2][labels[1]].Allsum += (Sum_time[3][labels[2]][labels[1]] / N);
		}

		datas[1][1][labels[1]].Average = datas[1][1][labels[1]].Allsum / 20;
		datas[1][2][labels[1]].Average = datas[1][2][labels[1]].Allsum / 20;
		datas[2][1][labels[1]].Average = datas[2][1][labels[1]].Allsum / 20;
		datas[2][2][labels[1]].Average = datas[2][2][labels[1]].Allsum / 20;
		datas[3][1][labels[1]].Average = datas[3][1][labels[1]].Allsum / 20;
		datas[3][2][labels[1]].Average = datas[3][2][labels[1]].Allsum / 20;

		printf("%llf\n", datas[1][1][labels[1]].Average);
		printf("%llf\n", datas[1][2][labels[1]].Average);
		printf("%llf\n", datas[2][1][labels[1]].Average);
		printf("%llf\n", datas[2][2][labels[1]].Average);
		printf("%llf\n", datas[3][1][labels[1]].Average);
		printf("%llf\n\n", datas[3][2][labels[1]].Average);

		for (labels[2] = 1; labels[2] <= 20; labels[2]++) {
			datas[1][1][labels[1]].Variance += pow((Sum_time[1][labels[1]][labels[2]] / N - datas[1][1][labels[1]].Average), 2);
			datas[1][2][labels[1]].Variance += pow((Sum_time[1][labels[2]][labels[1]] / N - datas[1][2][labels[1]].Average), 2);
			datas[2][1][labels[1]].Variance += pow((Sum_time[2][labels[1]][labels[2]] / N - datas[2][1][labels[1]].Average), 2);
			datas[2][2][labels[1]].Variance += pow((Sum_time[2][labels[2]][labels[1]] / N - datas[2][2][labels[1]].Average), 2);
			datas[3][1][labels[1]].Variance += pow((Sum_time[3][labels[1]][labels[2]] / N - datas[3][1][labels[1]].Average), 2);
			datas[3][2][labels[1]].Variance += pow((Sum_time[3][labels[2]][labels[1]] / N - datas[3][2][labels[1]].Average), 2);
		}

		datas[1][1][labels[1]].Variance /= 20;
		datas[1][2][labels[1]].Variance /= 20;
		datas[2][1][labels[1]].Variance /= 20;
		datas[2][2][labels[1]].Variance /= 20;
		datas[3][1][labels[1]].Variance /= 20;
		datas[3][2][labels[1]].Variance /= 20;
	}
	printf("--------------------results--------------------\n");
	printf("The variance of method_1 in car's speed is %llf\n", datas[1][1][1].Variance);
	printf("The variance of method_1 in man's speed is %llf\n", datas[1][2][1].Variance);
	printf("The variance of method_2 in car's speed is %llf\n", datas[2][1][1].Variance);
	printf("The variance of method_2 in man's speed is %llf\n", datas[2][2][1].Variance);
	printf("The variance of method_3 in car's speed is %llf\n", datas[3][1][1].Variance);
	printf("The variance of method_3 in man's speed is %llf\n", datas[3][2][1].Variance);
	
	freopen_s(&stream1, "result.txt", "w", stdout);
	printf("--------------------results--------------------\n");
	printf("The variance of method_1 in car's speed is %llf\n", datas[1][1][1].Variance);
	printf("The variance of method_1 in man's speed is %llf\n", datas[1][2][1].Variance);
	printf("The variance of method_2 in car's speed is %llf\n", datas[2][1][1].Variance);
	printf("The variance of method_2 in man's speed is %llf\n", datas[2][2][1].Variance);
	printf("The variance of method_3 in car's speed is %llf\n", datas[3][1][1].Variance);
	printf("The variance of method_3 in man's speed is %llf\n", datas[3][2][1].Variance);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
