#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 10
#define COLS 10

// 用于测试的地图数组
int grid[ROWS][COLS] = { 0 };
int grid1[ROWS][COLS] = { 0 }, grid2[ROWS][COLS] = { 0 };
int a1 = 3, a2 = 3;//初始飞机数
int kx[2][3], ky[2][3];
char kz[2][3];
int lastround = 0, lastx = -10, lasty = -10;

char map[5][11][11];

int rn(int x) {
	// 使用当前时间作为随机数种子，以确保每次运行程序时都得到不同的随机数
	srand(time(NULL));

	// 生成伪随机数并取模得到0~x-1之间的数字
	int randomNumber = rand() % x;

	return randomNumber;
}
char rd() {
	// 使用当前时间作为随机数种子
	srand(time(NULL));

	// 生成伪随机数并取模得到0-3之间的数字
	int randomNumber = rand() % 4;

	// 根据取模结果映射到四个字母
	char direction;
	switch (randomNumber) {
	case 0:
		direction = 'r';
		break;
	case 1:
		direction = 'l';
		break;
	case 2:
		direction = 'd';
		break;
	case 3:
		direction = 'u';
		break;
	}

	return direction;
}

int showmap(int user) {
	printf("可视地图：\n");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			printf("%c ", map[user - 1][j][i]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int initmap() {

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				map[k][i][j] = ' ';
			}
		}
	}
	for (int k = 0; k < 2; k++) {
		int i = 0;
		for (int j = 1; j < 11; j++) {
			map[k][i][j] = '0' + j - 1;
		}
		for (int j = 1; j < 11; j++) {
			map[k][j][i] = '0' + j - 1;
		}
	}
	//showmap(1);
	//showmap(2);
	return 0;
}

int initmap3() {
	int k = 2;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			map[k][i][j] = ' ';
		}
	}

	int i = 0;
	for (int j = 1; j < 11; j++) {
		map[k][i][j] = '0' + j - 1;
	}
	for (int j = 1; j < 11; j++) {
		map[k][j][i] = '0' + j - 1;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid1[i][j] == 0) {
				map[2][i + 1][j + 1] = ' ';
			}
			else if (grid1[i][j] == 1) {
				map[2][i + 1][j + 1] = '1';
			}
			else if (grid1[i][j] == 2) {
				map[2][i + 1][j + 1] = '2';
			}
		}
	}
	showmap(3);
	return 0;
}

int initmap4() {
	int k = 3;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			map[k][i][j] = ' ';
		}
	}

	int i = 0;
	for (int j = 1; j < 11; j++) {
		map[k][i][j] = '0' + j - 1;
	}
	for (int j = 1; j < 11; j++) {
		map[k][j][i] = '0' + j - 1;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid2[i][j] == 0) {
				map[3][i + 1][j + 1] = ' ';
			}
			else if (grid2[i][j] == 1) {
				map[3][i + 1][j + 1] = '1';
			}
			else if (grid2[i][j] == 2) {
				map[3][i + 1][j + 1] = '2';
			}
		}
	}
	showmap(4);
	return 0;
}

bool checkboundry(int x, int y, char z) {
	int planeCoords[10][2];

	switch (z) {
	case 'd':
		// 上方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 2;
		planeCoords[1][1] = y - 1;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x;
		planeCoords[3][1] = y - 1;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y - 1;
		planeCoords[5][0] = x + 2;
		planeCoords[5][1] = y - 1;
		planeCoords[6][0] = x;
		planeCoords[6][1] = y - 2;
		planeCoords[7][0] = x - 1;
		planeCoords[7][1] = y - 3;
		planeCoords[8][0] = x;
		planeCoords[8][1] = y - 3;
		planeCoords[9][0] = x + 1;
		planeCoords[9][1] = y - 3;
		break;
	case 'u':
		// 下方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 2;
		planeCoords[1][1] = y + 1;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y + 1;
		planeCoords[3][0] = x;
		planeCoords[3][1] = y + 1;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x + 2;
		planeCoords[5][1] = y + 1;
		planeCoords[6][0] = x;
		planeCoords[6][1] = y + 2;
		planeCoords[7][0] = x - 1;
		planeCoords[7][1] = y + 3;
		planeCoords[8][0] = x;
		planeCoords[8][1] = y + 3;
		planeCoords[9][0] = x + 1;
		planeCoords[9][1] = y + 3;
		break;
	case 'r':
		// 左方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 1;
		planeCoords[1][1] = y - 2;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x - 1;
		planeCoords[3][1] = y;
		planeCoords[4][0] = x - 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x - 1;
		planeCoords[5][1] = y + 2;
		planeCoords[6][0] = x - 2;
		planeCoords[6][1] = y;
		planeCoords[7][0] = x - 3;
		planeCoords[7][1] = y - 1;
		planeCoords[8][0] = x - 3;
		planeCoords[8][1] = y;
		planeCoords[9][0] = x - 3;
		planeCoords[9][1] = y + 1;
		break;
	case 'l':
		// 右方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x + 1;
		planeCoords[1][1] = y - 2;
		planeCoords[2][0] = x + 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x + 1;
		planeCoords[3][1] = y;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x + 1;
		planeCoords[5][1] = y + 2;
		planeCoords[6][0] = x + 2;
		planeCoords[6][1] = y;
		planeCoords[7][0] = x + 3;
		planeCoords[7][1] = y - 1;
		planeCoords[8][0] = x + 3;
		planeCoords[8][1] = y;
		planeCoords[9][0] = x + 3;
		planeCoords[9][1] = y + 1;
		break;
	default:
		// 处理未知方向的情况
		return true;
	}

	// 检查是否超出边界
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			printf("请勿超出边界，");
			return true; // 超出边界
		}
	}

	// 检查是否已经被占领
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			printf("请勿重叠放置飞机，");
			return true; // 已经被占领
		}
	}

	// 将这些点全部置1，表示占领
	for (int i = 0; i < 10; i++) {
		grid[planeCoords[i][0]][planeCoords[i][1]] = 1;
	}
	grid[x][y] = 2;
	return false; // 没有超出边界且没有被占领
}

bool checkboundryBOT(int x, int y, char z) {
	int planeCoords[10][2];

	switch (z) {
	case 'd':
		// 上方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 2;
		planeCoords[1][1] = y - 1;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x;
		planeCoords[3][1] = y - 1;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y - 1;
		planeCoords[5][0] = x + 2;
		planeCoords[5][1] = y - 1;
		planeCoords[6][0] = x;
		planeCoords[6][1] = y - 2;
		planeCoords[7][0] = x - 1;
		planeCoords[7][1] = y - 3;
		planeCoords[8][0] = x;
		planeCoords[8][1] = y - 3;
		planeCoords[9][0] = x + 1;
		planeCoords[9][1] = y - 3;
		break;
	case 'u':
		// 下方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 2;
		planeCoords[1][1] = y + 1;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y + 1;
		planeCoords[3][0] = x;
		planeCoords[3][1] = y + 1;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x + 2;
		planeCoords[5][1] = y + 1;
		planeCoords[6][0] = x;
		planeCoords[6][1] = y + 2;
		planeCoords[7][0] = x - 1;
		planeCoords[7][1] = y + 3;
		planeCoords[8][0] = x;
		planeCoords[8][1] = y + 3;
		planeCoords[9][0] = x + 1;
		planeCoords[9][1] = y + 3;
		break;
	case 'r':
		// 左方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x - 1;
		planeCoords[1][1] = y - 2;
		planeCoords[2][0] = x - 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x - 1;
		planeCoords[3][1] = y;
		planeCoords[4][0] = x - 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x - 1;
		planeCoords[5][1] = y + 2;
		planeCoords[6][0] = x - 2;
		planeCoords[6][1] = y;
		planeCoords[7][0] = x - 3;
		planeCoords[7][1] = y - 1;
		planeCoords[8][0] = x - 3;
		planeCoords[8][1] = y;
		planeCoords[9][0] = x - 3;
		planeCoords[9][1] = y + 1;
		break;
	case 'l':
		// 右方向的坐标计算
		planeCoords[0][0] = x;
		planeCoords[0][1] = y;
		planeCoords[1][0] = x + 1;
		planeCoords[1][1] = y - 2;
		planeCoords[2][0] = x + 1;
		planeCoords[2][1] = y - 1;
		planeCoords[3][0] = x + 1;
		planeCoords[3][1] = y;
		planeCoords[4][0] = x + 1;
		planeCoords[4][1] = y + 1;
		planeCoords[5][0] = x + 1;
		planeCoords[5][1] = y + 2;
		planeCoords[6][0] = x + 2;
		planeCoords[6][1] = y;
		planeCoords[7][0] = x + 3;
		planeCoords[7][1] = y - 1;
		planeCoords[8][0] = x + 3;
		planeCoords[8][1] = y;
		planeCoords[9][0] = x + 3;
		planeCoords[9][1] = y + 1;
		break;
	default:
		// 处理未知方向的情况
		return true;
	}

	// 检查是否超出边界
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			//printf("请勿超出边界，");
			return true; // 超出边界
		}
	}

	// 检查是否已经被占领
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			//printf("请勿重叠放置飞机，");
			return true; // 已经被占领
		}
	}

	// 将这些点全部置1，表示占领
	for (int i = 0; i < 10; i++) {
		grid[planeCoords[i][0]][planeCoords[i][1]] = 1;
	}
	grid[x][y] = 2;
	return false; // 没有超出边界且没有被占领
}

int check1(int x, int y) {
	int hit = 0;//0为未击中，1为击中身子，2为击中头部
	for (int i = 0; i < 3; i++) {
		if (x == kx[1][i] && y == ky[1][i]) {
			//消除飞机
			int planeCoords[10][2];
			switch (kz[1][i]) {
			case 'd':
				// 上方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y - 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y - 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y - 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y - 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y - 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y - 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y - 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y - 3;
				break;
			case 'u':
				// 下方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y + 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y + 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y + 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y + 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y + 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y + 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y + 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y + 3;
				break;
			case 'r':
				// 左方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x - 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x - 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x - 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x - 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x - 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x - 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x - 3;
				planeCoords[9][1] = y + 1;
				break;
			case 'l':
				// 右方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x + 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x + 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x + 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x + 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x + 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x + 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x + 3;
				planeCoords[9][1] = y + 1;
				break;
			default:
				// 处理未知方向的情况
				return true;
			}
			// 将这些点全部置-1，表示击落
			for (int i = 0; i < 10; i++) {
				grid2[planeCoords[i][0]][planeCoords[i][1]] = -1;
			}
			kx[1][i] = -1;
			ky[1][i] = -1;
			a2--;
			hit = 2;
			return hit;
		}
	}
	if (grid2[x][y] == 1) {
		grid2[x][y] = -1;
		hit = 1;
	}
	else hit = 0;

	return hit;
}

int check2(int x, int y) {
	int hit = 0;//0为未击中，1为击中身子，2为击中头部
	for (int i = 0; i < 3; i++) {
		if (x == kx[0][i] && y == ky[0][i]) {
			//消除飞机
			int planeCoords[10][2];
			switch (kz[0][i]) {
			case 'd':
				// 上方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y - 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y - 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y - 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y - 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y - 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y - 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y - 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y - 3;
				break;
			case 'u':
				// 下方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y + 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y + 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y + 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y + 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y + 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y + 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y + 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y + 3;
				break;
			case 'r':
				// 左方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x - 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x - 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x - 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x - 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x - 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x - 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x - 3;
				planeCoords[9][1] = y + 1;
				break;
			case 'l':
				// 右方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x + 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x + 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x + 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x + 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x + 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x + 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x + 3;
				planeCoords[9][1] = y + 1;
				break;
			default:
				// 处理未知方向的情况
				return true;
			}
			// 将这些点全部置-1，表示击落
			for (int i = 0; i < 10; i++) {
				grid1[planeCoords[i][0]][planeCoords[i][1]] = -1;
			}
			kx[0][i] = -1;
			ky[0][i] = -1;
			a1--;
			hit = 2;
			return hit;
		}
	}
	if (grid1[x][y] == 1) {
		grid1[x][y] = -1;
		hit = 1;
	}
	else hit = 0;

	return hit;
}

int figure(int* px, int* py) {
	if (lastround == 0) {//未击中，随机选点
		*px = rn(10);
		*py = rn(10);
		while (map[1][*px + 1][*py + 1] != ' ' || grid1[*px][*py] == -1) {
			//printf("输入越界！请玩家2重新输入攻击坐标“x y”\n");
			//scanf("%d%d", &x, &y);
			*px = rn(10);
			*py = rn(10);
		}
	}
	else if (lastround == 1) {//上一轮击伤，小范围选点
		*px = rn(5) + lastx - 2;
		*py = rn(5) + lasty - 2;
		while (map[1][*px + 1][*py + 1] != ' ' || grid1[*px][*py] == -1) {
			//printf("输入越界！请玩家2重新输入攻击坐标“x y”\n");
			//scanf("%d%d", &x, &y);
			*px = rn(5) + lastx - 2;
			*py = rn(5) + lasty - 2;
		}
	}

	//知道grid1和map[2]需要一套高效聪明的炸机方法
	for (int i = 0; i < 3; i++) {
		int x = kx[0][i];
		int y = ky[0][i];
		if (x >= 0 && y >= 0) {
			int planeCoords[10][2];
			switch (kz[0][i]) {
			case 'd':
				// 上方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y - 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y - 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y - 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y - 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y - 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y - 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y - 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y - 3;
				break;
			case 'u':
				// 下方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 2;
				planeCoords[1][1] = y + 1;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y + 1;
				planeCoords[3][0] = x;
				planeCoords[3][1] = y + 1;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 2;
				planeCoords[5][1] = y + 1;
				planeCoords[6][0] = x;
				planeCoords[6][1] = y + 2;
				planeCoords[7][0] = x - 1;
				planeCoords[7][1] = y + 3;
				planeCoords[8][0] = x;
				planeCoords[8][1] = y + 3;
				planeCoords[9][0] = x + 1;
				planeCoords[9][1] = y + 3;
				break;
			case 'r':
				// 左方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x - 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x - 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x - 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x - 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x - 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x - 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x - 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x - 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x - 3;
				planeCoords[9][1] = y + 1;
				break;
			case 'l':
				// 右方向的坐标计算
				planeCoords[0][0] = x;
				planeCoords[0][1] = y;
				planeCoords[1][0] = x + 1;
				planeCoords[1][1] = y - 2;
				planeCoords[2][0] = x + 1;
				planeCoords[2][1] = y - 1;
				planeCoords[3][0] = x + 1;
				planeCoords[3][1] = y;
				planeCoords[4][0] = x + 1;
				planeCoords[4][1] = y + 1;
				planeCoords[5][0] = x + 1;
				planeCoords[5][1] = y + 2;
				planeCoords[6][0] = x + 2;
				planeCoords[6][1] = y;
				planeCoords[7][0] = x + 3;
				planeCoords[7][1] = y - 1;
				planeCoords[8][0] = x + 3;
				planeCoords[8][1] = y;
				planeCoords[9][0] = x + 3;
				planeCoords[9][1] = y + 1;
				break;
			default:
				// 处理未知方向的情况
				return true;
			}
			// 数每架飞机被击中几次
			int count = 0;
			for (int i = 0; i < 10; i++) {
				if (map[1][planeCoords[i][0] + 1][planeCoords[i][1] + 1] == '1') {
					count++;
				}
			}
			if (count > 2) {
				*px = kx[0][i];
				*py = ky[0][i];
				break;
			}
		}
	}

	return 0;
}

int roundPvP(int n) {
	int hit;
	int x, y;
	printf("round %d\n", n);
	printf("请玩家1输入攻击坐标“x y”\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("输入非法！请玩家1重新输入攻击坐标“x y”\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("未击中目标\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("击伤敌机\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("击中头部并击落一架敌机\n");
	}
	showmap(1);
	printf("请玩家2输入攻击坐标“x y”\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[1][x + 1][y + 1] != ' ') {
		printf("输入非法！请玩家2重新输入攻击坐标“x y”\n");
		scanf("%d%d", &x, &y);
	}
	hit = check2(x, y);
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("未击中目标\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("击伤敌机\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("击中头部并击落一架敌机\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("玩家2胜利！\n游戏结束");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("玩家1胜利！\n游戏结束");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("平局！\n游戏结束");
		return 0;
	}
	else {
		return 1;
	}
}

int roundPvE(int n) {
	int hit;
	int x, y;
	printf("round %d\n", n);
	printf("请玩家输入攻击坐标“x y”\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("输入非法！请玩家重新输入攻击坐标“x y”\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("未击中目标\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("击伤敌机\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("击中头部并击落一架敌机\n");
	}
	showmap(1);

	printf("\nBOT决策中，请等待...\n");

	int* px, * py;
	px = &x;
	py = &y;
	figure(px, py);//改为选点算法x y

	hit = check2(x, y);
	printf("BOT输入攻击坐标“%d %d”\n", x, y);
	lastx = x;
	lasty = y;
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("未击中目标\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 1;
		printf("击伤敌机\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("击中头部并击落一架敌机\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("BOT胜利！\n游戏结束");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("玩家胜利！\n游戏结束");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("平局！\n游戏结束");
		return 0;
	}
	else {
		return 1;
	}
}

int main() {
	char c = '0';
	while (c != '1' && c != '2') {
		//printf("炸飞机游戏玩法简介请见：\nhttps://baike.baidu.com/item/%E7%82%B8%E9%A3%9E%E6%9C%BA/3937542\n\n");

		checkboundry(2, 0, 'u');
		checkboundry(7, 3, 'd');
		checkboundry(0, 7, 'l');
		checkboundry(9, 7, 'r');
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid1[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}
		initmap3();
		printf("游戏说明：\n");
		printf("上图中实例分别是四架飞机，他们代表了四种飞机方向,飞机机头用数字2表示，机身用数字1表示。\n他们的头部坐标从上到下从左到右依次是：2 0 u ，7 3 d ， 0 7 l ， 9 7 r 。\n");
		printf("在放置飞机时请注意，不可以将飞机放置越界，也不可以将飞机重叠放置。\n尽管您放置的飞机头部坐标在0 - 9范围内，但是有可能机身超出了界外，例如：1 1 r\n\n");



		printf("请选择：\n1.双人对战(输入“1”) \n2.人机对战(输入“2”)\n");
		scanf("%c", &c);
		getchar();
	}

	if (c == '1') {//双人对战
		int x, y;
		char z;
		bool v = 1;//为0时输入正确跳出循环

		printf("请玩家1就绪\n请输入您三架飞机头部的坐标，输入格式为:x(空格)y(空格)z ，例如：9 2 r\n其中x和y分别是横纵坐标（坐标范围是0-9），z代表方向：u是上，d是下，l是左，r是右\n");
		while (v) {
			printf("请输入放置飞机1的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机2的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机3的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;
				printf("输入合法，请继续\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid1[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}
		initmap3();

		while (getchar() != '1') { printf("请输入1确认\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");


		printf("请玩家2就绪\n请输入您三架飞机头部的坐标，输入格式为:x(空格)y(空格)z ，例如：9 2 r\n其中x和y分别是横纵坐标（坐标范围是0-9），z代表方向：u是上，d是下，l是左，r是右\n");
		v = 1;
		while (v) {
			printf("请输入放置飞机1的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[1][0] = x;
				ky[1][0] = y;
				kz[1][0] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机2的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[1][1] = x;
				ky[1][1] = y;
				kz[1][1] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机3的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[1][2] = x;
				ky[1][2] = y;
				kz[1][2] = z;
				printf("输入合法，请继续\n");
			}
		}


		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid2[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}

		initmap4();
		while (getchar() != '2') { printf("请输入2确认\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n游戏开始\n");

		initmap();

		int n = 1;

		while (roundPvP(n)) {
			n++;
		}

	}

	else if (c == '2') {//人机对战
		int x, y;
		char z;
		bool v = 1;//为0时输入正确跳出循环

		printf("请玩家就绪\n请输入您三架飞机头部的坐标，输入格式为:x(空格)y(空格)z ，例如：9 2 r\n其中x和y分别是横纵坐标（坐标范围是0-9），z代表方向：u是上，d是下，l是左，r是右\n");
		while (v) {
			printf("请输入放置飞机1的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机2的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;
				printf("输入合法，请继续\n");
			}
		}
		v = 1;
		while (v) {
			printf("请输入放置飞机3的头部位置，以及飞机的方向\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("输入非法！\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;
				printf("输入合法，请继续\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid1[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}
		initmap3();

		while (getchar() != '1') { printf("请输入1确认\n"); }
		printf("\n请稍等，机器人生成中...");
		//BOT在grid2[][]中随机放置飞机的算法
		v = 1;
		int count = 0;
		int error = 0;
		while (v) {
			//printf("请输入放置飞机1的头部位置，以及飞机的方向\n");
			//scanf("%d%d", &x, &y);
			//getchar();
			//scanf("%c", &z);
			x = rn(10);
			y = rn(10);


			if (x > 7) {
				y = rn(6) + 2;
				z = 'r';
			}
			else if (x < 2) {
				y = rn(6) + 2;
				z = 'l';
			}
			else if (y > 7) {
				x = rn(6) + 2;
				z = 'd';
			}
			else if (y < 2) {
				x = rn(6) + 2;
				z = 'u';
			}
			else { z = rd(); }

			v = checkboundryBOT(x, y, z);
			if (v) {
				count++;
				if (count > 5000000) {
					printf(".");
					count = 0;
				}
			}
			else {
				kx[1][0] = x;
				ky[1][0] = y;
				kz[1][0] = z;
				printf("\n\n已生成1,请稍等...");
			}
		}
		v = 1;
		while (v) {
			//printf("请输入放置飞机2的头部位置，以及飞机的方向\n");
			//scanf("%d%d", &x, &y);
			//getchar();
			//scanf("%c", &z);
			x = rn(10);
			y = rn(10);


			if (x > 7) {
				y = rn(6) + 2;
				z = 'r';
			}
			else if (x < 2) {
				y = rn(6) + 2;
				z = 'l';
			}
			else if (y > 7) {
				x = rn(6) + 2;
				z = 'd';
			}
			else if (y < 2) {
				x = rn(6) + 2;
				z = 'u';
			}
			else { z = rd(); }

			v = checkboundryBOT(x, y, z);
			if (v) {
				count++;
				if (count > 5000000) {
					printf(".");
					count = 0;
					error++;
					if (error == 10) {
						printf("\n别着急，我没出问题，让BOT再想一会儿");
					}
					else if (error == 20) {
						printf("\nBOT这次想的有点久");
					}
					else if (error == 40) {
						printf("\nBOT这次想的好像有点太久了，要不退出试试？");
					}
					else if (error == 60) {
						printf("\n还在等吗？");
					}
					else if (error == 80) {
						printf("\nBOT确乎是卡住了，即将强制退出游戏");
					}
					else if (error == 100) {
						return 0;
					}
				}
			}
			else {
				kx[1][1] = x;
				ky[1][1] = y;
				kz[1][1] = z;
				printf("\n\n已生成2,请稍等...");
			}
		}
		v = 1;
		while (v) {
			//printf("请输入放置飞机3的头部位置，以及飞机的方向\n");
			//scanf("%d%d", &x, &y);
			//getchar();
			//scanf("%c", &z);
			x = rn(10);
			y = rn(10);


			if (x > 7) {
				y = rn(6) + 2;
				z = 'r';
			}
			else if (x < 2) {
				y = rn(6) + 2;
				z = 'l';
			}
			else if (y > 7) {
				x = rn(6) + 2;
				z = 'd';
			}
			else if (y < 2) {
				x = rn(6) + 2;
				z = 'u';
			}
			else { z = rd(); }

			v = checkboundryBOT(x, y, z);
			if (v) {
				count++;
				if (count > 5000000) {
					printf(".");
					count = 0;
					error++;
					if (error == 20) {
						printf("\n别着急，我没出问题，让BOT再想一会儿");
					}
					else if (error == 40) {
						printf("\nBOT这次想的有点久");
					}
					else if (error == 80) {
						printf("\nBOT这次想的好像有点太久了，要不退出试试？");
					}
					else if (error == 120) {
						printf("\n还在等吗？");
					}
					else if (error == 160) {
						printf("\nBOT确乎是卡住了，即将强制退出游戏");
					}
					else if (error == 200) {
						return 0;
					}
				}
			}
			else {
				kx[1][2] = x;
				ky[1][2] = y;
				kz[1][2] = z;
				printf("\n\n已生成3,游戏即将开始\n\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid2[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}

		initmap4();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n机器人生成完毕，游戏开始\n");
		initmap();

		int n = 1;

		while (roundPvE(n)) {
			n++;
		}

	}

	printf("\n您可以输入0退出，也可以向上滑动查看对局过程\n");
	int s = 1;
	while (s != 0) {
		scanf("%d", &s);
	}
	return 0;

}
