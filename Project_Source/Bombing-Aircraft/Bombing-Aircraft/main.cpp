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
	static int seed_initialized = 0;
	if (!seed_initialized) {
		srand((unsigned int)clock());  // 只在第一次调用时初始化种子
		seed_initialized = 1;
	}

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
	printf("Visual map:\n");
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


	// Check if it exceeds the boundary
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			printf("Do not exceed the boundary,");
			return true; // Exceeds the boundary
		}
	}

	// Check if it is already occupied
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			printf("Do not overlap when placing the plane,");
			return true; // Already occupied
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

	// Check if it exceeds the boundary
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			return true; // Exceeds the boundary
		}
	}

	// Check if it is already occupied
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			return true; // Already occupied
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
		while (map[1][*px + 1][*py + 1] != ' ' || grid1[*px][*py] == -1 || *py > 9 || *py < 0 || *px > 9 || *px < 0) {
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
	printf("Player 1, please enter attack coordinates \"x y\"\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("Invalid input! Player 1, please re-enter attack coordinates \"x y\"\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Missed the target\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Damaged the enemy plane\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Hit the head and shot down an enemy plane\n");
	}
	showmap(1);
	printf("Player 2, please enter attack coordinates \"x y\"\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[1][x + 1][y + 1] != ' ') {
		printf("Invalid input! Player 2, please re-enter attack coordinates \"x y\"\n");
		scanf("%d%d", &x, &y);
	}
	hit = check2(x, y);
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("Missed the target\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("Damaged the enemy plane\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("Hit the head and shot down an enemy plane\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("Player 2 wins!\nGame over");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("Player 1 wins!\nGame over");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("It's a draw!\nGame over");
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
	printf("Player, please enter attack coordinates \"x y\"\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("Invalid input! Player, please re-enter attack coordinates \"x y\"\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Missed the target\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Damaged the enemy plane\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("Hit the head and shot down an enemy plane\n");
	}
	showmap(1);

	printf("\nBOT is deciding, please wait...\n");

	int* px, * py;
	px = &x;
	py = &y;
	figure(px, py); // Change to point selection algorithm x y

	hit = check2(x, y);
	printf("BOT input attack coordinates \"%d %d\"\n", x, y);
	lastx = x;
	lasty = y;
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("Missed the target\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 1;
		printf("Damaged the enemy plane\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("Hit the head and shot down an enemy plane\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("BOT wins!\nGame over");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("Player wins!\nGame over");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("It's a draw!\nGame over");
		return 0;
	}
	else {
		return 1;
	}
}


int main() {
	char c = '0';
	while (c != '1' && c != '2') {
		//printf("For a brief introduction to the game, please refer to: \nhttps://baike.baidu.com/item/%E7%82%B8%E9%A3%9E%E6%9C%BA/3937542\n\n");

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

		printf("Game Instructions:\n");
		printf("The plane's nose is represented by the number 2, and the body is represented by the number 1. A plane consists of one nose and nine body parts (i.e., one 2 and nine 1s).\n");
		printf("The coordinates for the plane's position are in the format: x (space) y (space) z, where x and y are the horizontal and vertical coordinates (coordinate range is 0-9), and z represents the direction: u for up, d for down, l for left, r for right.\n\n");

		initmap3();

		printf("In the example above, there are four planes, representing four directions.\n");
		printf("Their nose coordinates, from top to bottom and left to right, are: 2 0 u, 7 3 d, 0 7 l, 9 7 r.\n");
		printf("For example: 2 0 u means the plane's nose is at coordinate (2, 0) and its direction is upward.\n");
		printf("When placing planes, please note: planes cannot go out of bounds, and planes cannot overlap.\n");
		printf("Even if the plane's nose coordinates are within the range of 0 - 9, the body might exceed the boundary. For example: 1 1 r.\n\n");

		printf("Please choose:\n1. Two-player battle (input '1') \n2. Human vs AI battle (input '2')\n");
		scanf("%c", &c);
		getchar();
	}

	if (c == '1') {//Two-player battle
		int x, y;
		char z;
		bool v = 1;//Set to 0 to exit loop when input is correct

		printf("Please Player 1, get ready.\nEnter the coordinates of the heads of your three planes in the format: x (space) y (space) z, for example: 9 2 r\nWhere x and y are the horizontal and vertical coordinates (range 0-9), and z represents the direction: u is up, d is down, l is left, r is right.\n");
		while (v) {
			printf("Please enter the head position of plane 1 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
					}
				}
				initmap3();
				printf("Valid input, please continue.\n");
			}
		}
		v = 1;
		while (v) {
			printf("Please enter the head position of plane 2 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
					}
				}
				initmap3();
				printf("Valid input, please continue.\n");
			}
		}
		v = 1;
		while (v) {
			printf("Please enter the head position of plane 3 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
				initmap3();
				printf("Valid input, please continue.\n");
			}
		}



		while (getchar() != '1') { printf("Please enter 1 to confirm.\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");


		printf("Please Player 2, get ready.\nEnter the coordinates of the heads of your three planes in the format: x (space) y (space) z, for example: 9 2 r\nWhere x and y are the horizontal and vertical coordinates (range 0-9), and z represents the direction: u is up, d is down, l is left, r is right.\n");
		v = 1;
		while (v) {
			printf("Please enter the head position of plane 1 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[1][0] = x;
				ky[1][0] = y;
				kz[1][0] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid2[i][j] = grid[i][j];
					}
				}
				initmap4();
				printf("Valid input, please continue.\n");
			}
		}
		v = 1;
		while (v) {
			printf("Please enter the head position of plane 2 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[1][1] = x;
				ky[1][1] = y;
				kz[1][1] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid2[i][j] = grid[i][j];
					}
				}
				initmap4();
				printf("Valid input, please continue.\n");
			}
		}
		v = 1;
		while (v) {
			printf("Please enter the head position of plane 3 and its direction.\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[1][2] = x;
				ky[1][2] = y;
				kz[1][2] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid2[i][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
				initmap4();
				printf("Valid input, please continue.\n");
			}
		}


		while (getchar() != '2') { printf("Please enter 2 to confirm.\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThe game starts\n");

		initmap();

		int n = 1;

		while (roundPvP(n)) {
			n++;
		}

	}


	else if (c == '2') { // Player vs. BOT
		int x, y;
		char z;
		bool v = 1; // Set to 0 to exit the loop when input is valid

		printf("Please get ready, player.\nEnter the coordinates of the head of your three planes, format: x(space)y(space)z. For example: 9 2 r\nWhere x and y are the horizontal and vertical coordinates (range: 0-9), z represents the direction: u for up, d for down, l for left, r for right.\n");
		while (v) {
			printf("Enter the head position and direction for Plane 1\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
					}
				}
				initmap3();
				printf("Valid input, please continue\n");
			}
		}

		v = 1;
		while (v) {
			printf("Enter the head position and direction for Plane 2\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
					}
				}
				initmap3();
				printf("Valid input, please continue\n");
			}
		}

		v = 1;
		while (v) {
			printf("Enter the head position and direction for Plane 3\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("Invalid input!\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;

				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						grid1[i][j] = grid[i][j];
						grid[i][j] = 0;
					}
				}
				initmap3();
				printf("Valid input, please continue\n");
			}
		}



		while (getchar() != '1') {
			printf("Please press 1 to confirm\n");
		}
		printf("\nPlease wait, the robot is generating...");

		// BOT randomly places planes in grid2[][]
		v = 1;
		int count = 0;
		int error = 0;
		while (v) {
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
			else {
				z = rd();
			}

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
				printf("\n\nGenerated Plane 1, please wait...");
			}
		}

		v = 1;
		while (v) {
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
			else {
				z = rd();
			}

			v = checkboundryBOT(x, y, z);
			if (v) {
				count++;
				if (count > 5000000) {
					printf(".");
					count = 0;
					error++;
					if (error == 10) {
						printf("\nDon't worry, there's no issue. Let the BOT think for a while");
					}
					else if (error == 20) {
						printf("\nThe BOT is taking quite a long time to think");
					}
					else if (error == 40) {
						printf("\nThe BOT seems to be taking too long, maybe try exiting?");
					}
					else if (error == 60) {
						printf("\nAre you still waiting?");
					}
					else if (error == 80) {
						printf("\nThe BOT is definitely stuck, the game will forcibly exit soon");
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
				printf("\n\nGenerated Plane 2, please wait...");
			}
		}

		v = 1;
		while (v) {
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
			else {
				z = rd();
			}

			v = checkboundryBOT(x, y, z);
			if (v) {
				count++;
				if (count > 5000000) {
					printf(".");
					count = 0;
					error++;
					if (error == 20) {
						printf("\nDon't worry, there's no issue. Let the BOT think for a while");
					}
					else if (error == 40) {
						printf("\nThe BOT is taking quite a long time to think");
					}
					else if (error == 80) {
						printf("\nThe BOT seems to be taking too long, maybe try exiting?");
					}
					else if (error == 120) {
						printf("\nAre you still waiting?");
					}
					else if (error == 160) {
						printf("\nThe BOT is definitely stuck, the game will forcibly exit soon");
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
				printf("\n\nGenerated Plane 3, the game is about to start\n\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid2[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}

		initmap4();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nThe robot has finished generating, the game begins\n");
		initmap();

		int n = 1;

		while (roundPvE(n)) {
			n++;
		}

	}

	printf("\nYou can enter 0 to exit, or swipe up to view the game process\n");
	int s = 1;
	while (s != 0) {
		scanf("%d", &s);
	}
	return 0;


}
