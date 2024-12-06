#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 10
#define COLS 10

// ���ڲ��Եĵ�ͼ����
int grid[ROWS][COLS] = { 0 };
int grid1[ROWS][COLS] = { 0 }, grid2[ROWS][COLS] = { 0 };
int a1 = 3, a2 = 3;//��ʼ�ɻ���
int kx[2][3], ky[2][3];
char kz[2][3];
int lastround = 0, lastx = -10, lasty = -10;

char map[5][11][11];

int rn(int x) {
	// ʹ�õ�ǰʱ����Ϊ��������ӣ���ȷ��ÿ�����г���ʱ���õ���ͬ�������
	srand(time(NULL));

	// ����α�������ȡģ�õ�0~x-1֮�������
	int randomNumber = rand() % x;

	return randomNumber;
}
char rd() {
	// ʹ�õ�ǰʱ����Ϊ���������
	srand(time(NULL));

	// ����α�������ȡģ�õ�0-3֮�������
	int randomNumber = rand() % 4;

	// ����ȡģ���ӳ�䵽�ĸ���ĸ
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
	printf("���ӵ�ͼ��\n");
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
		// �Ϸ�����������
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
		// �·�����������
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
		// ������������
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
		// �ҷ�����������
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
		// ����δ֪��������
		return true;
	}

	// ����Ƿ񳬳��߽�
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			printf("���𳬳��߽磬");
			return true; // �����߽�
		}
	}

	// ����Ƿ��Ѿ���ռ��
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			printf("�����ص����÷ɻ���");
			return true; // �Ѿ���ռ��
		}
	}

	// ����Щ��ȫ����1����ʾռ��
	for (int i = 0; i < 10; i++) {
		grid[planeCoords[i][0]][planeCoords[i][1]] = 1;
	}
	grid[x][y] = 2;
	return false; // û�г����߽���û�б�ռ��
}

bool checkboundryBOT(int x, int y, char z) {
	int planeCoords[10][2];

	switch (z) {
	case 'd':
		// �Ϸ�����������
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
		// �·�����������
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
		// ������������
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
		// �ҷ�����������
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
		// ����δ֪��������
		return true;
	}

	// ����Ƿ񳬳��߽�
	for (int i = 0; i < 10; i++) {
		if (planeCoords[i][0] < 0 || planeCoords[i][0] >= ROWS ||
			planeCoords[i][1] < 0 || planeCoords[i][1] >= COLS) {
			//printf("���𳬳��߽磬");
			return true; // �����߽�
		}
	}

	// ����Ƿ��Ѿ���ռ��
	for (int i = 0; i < 10; i++) {
		if (grid[planeCoords[i][0]][planeCoords[i][1]] != 0) {
			//printf("�����ص����÷ɻ���");
			return true; // �Ѿ���ռ��
		}
	}

	// ����Щ��ȫ����1����ʾռ��
	for (int i = 0; i < 10; i++) {
		grid[planeCoords[i][0]][planeCoords[i][1]] = 1;
	}
	grid[x][y] = 2;
	return false; // û�г����߽���û�б�ռ��
}

int check1(int x, int y) {
	int hit = 0;//0Ϊδ���У�1Ϊ�������ӣ�2Ϊ����ͷ��
	for (int i = 0; i < 3; i++) {
		if (x == kx[1][i] && y == ky[1][i]) {
			//�����ɻ�
			int planeCoords[10][2];
			switch (kz[1][i]) {
			case 'd':
				// �Ϸ�����������
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
				// �·�����������
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
				// ������������
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
				// �ҷ�����������
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
				// ����δ֪��������
				return true;
			}
			// ����Щ��ȫ����-1����ʾ����
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
	int hit = 0;//0Ϊδ���У�1Ϊ�������ӣ�2Ϊ����ͷ��
	for (int i = 0; i < 3; i++) {
		if (x == kx[0][i] && y == ky[0][i]) {
			//�����ɻ�
			int planeCoords[10][2];
			switch (kz[0][i]) {
			case 'd':
				// �Ϸ�����������
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
				// �·�����������
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
				// ������������
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
				// �ҷ�����������
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
				// ����δ֪��������
				return true;
			}
			// ����Щ��ȫ����-1����ʾ����
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
	if (lastround == 0) {//δ���У����ѡ��
		*px = rn(10);
		*py = rn(10);
		while (map[1][*px + 1][*py + 1] != ' ' || grid1[*px][*py] == -1) {
			//printf("����Խ�磡�����2�������빥�����ꡰx y��\n");
			//scanf("%d%d", &x, &y);
			*px = rn(10);
			*py = rn(10);
		}
	}
	else if (lastround == 1) {//��һ�ֻ��ˣ�С��Χѡ��
		*px = rn(5) + lastx - 2;
		*py = rn(5) + lasty - 2;
		while (map[1][*px + 1][*py + 1] != ' ' || grid1[*px][*py] == -1) {
			//printf("����Խ�磡�����2�������빥�����ꡰx y��\n");
			//scanf("%d%d", &x, &y);
			*px = rn(5) + lastx - 2;
			*py = rn(5) + lasty - 2;
		}
	}

	//֪��grid1��map[2]��Ҫһ�׸�Ч������ը������
	for (int i = 0; i < 3; i++) {
		int x = kx[0][i];
		int y = ky[0][i];
		if (x >= 0 && y >= 0) {
			int planeCoords[10][2];
			switch (kz[0][i]) {
			case 'd':
				// �Ϸ�����������
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
				// �·�����������
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
				// ������������
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
				// �ҷ�����������
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
				// ����δ֪��������
				return true;
			}
			// ��ÿ�ܷɻ������м���
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
	printf("�����1���빥�����ꡰx y��\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("����Ƿ��������1�������빥�����ꡰx y��\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("δ����Ŀ��\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("���˵л�\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("����ͷ��������һ�ܵл�\n");
	}
	showmap(1);
	printf("�����2���빥�����ꡰx y��\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[1][x + 1][y + 1] != ' ') {
		printf("����Ƿ��������2�������빥�����ꡰx y��\n");
		scanf("%d%d", &x, &y);
	}
	hit = check2(x, y);
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("δ����Ŀ��\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("���˵л�\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		printf("����ͷ��������һ�ܵл�\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("���2ʤ����\n��Ϸ����");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("���1ʤ����\n��Ϸ����");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("ƽ�֣�\n��Ϸ����");
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
	printf("��������빥�����ꡰx y��\n");
	scanf("%d%d", &x, &y);
	while ((!(x >= 0 && x < ROWS && y >= 0 && y < COLS)) || map[0][x + 1][y + 1] != ' ') {
		printf("����Ƿ���������������빥�����ꡰx y��\n");
		scanf("%d%d", &x, &y);
	}
	hit = check1(x, y);
	if (hit == 0) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("δ����Ŀ��\n");
	}
	else if (hit == 1) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("���˵л�\n");
	}
	else if (hit == 2) {
		map[0][x + 1][y + 1] = '0' + hit;
		printf("����ͷ��������һ�ܵл�\n");
	}
	showmap(1);

	printf("\nBOT�����У���ȴ�...\n");

	int* px, * py;
	px = &x;
	py = &y;
	figure(px, py);//��Ϊѡ���㷨x y

	hit = check2(x, y);
	printf("BOT���빥�����ꡰ%d %d��\n", x, y);
	lastx = x;
	lasty = y;
	if (hit == 0) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("δ����Ŀ��\n");
	}
	else if (hit == 1) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 1;
		printf("���˵л�\n");
	}
	else if (hit == 2) {
		map[1][x + 1][y + 1] = '0' + hit;
		lastround = 0;
		printf("����ͷ��������һ�ܵл�\n");
	}
	showmap(2);
	if (a1 == 0 && a2 > 0) {
		printf("BOTʤ����\n��Ϸ����");
		return 0;
	}
	else if (a2 == 0 && a1 > 0) {
		printf("���ʤ����\n��Ϸ����");
		return 0;
	}
	else if (a1 == 0 && a2 == 0) {
		printf("ƽ�֣�\n��Ϸ����");
		return 0;
	}
	else {
		return 1;
	}
}

int main() {
	char c = '0';
	while (c != '1' && c != '2') {
		//printf("ը�ɻ���Ϸ�淨��������\nhttps://baike.baidu.com/item/%E7%82%B8%E9%A3%9E%E6%9C%BA/3937542\n\n");

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
		printf("��Ϸ˵����\n");
		printf("��ͼ��ʵ���ֱ����ļܷɻ������Ǵ��������ַɻ�����,�ɻ���ͷ������2��ʾ������������1��ʾ��\n���ǵ�ͷ��������ϵ��´����������ǣ�2 0 u ��7 3 d �� 0 7 l �� 9 7 r ��\n");
		printf("�ڷ��÷ɻ�ʱ��ע�⣬�����Խ��ɻ�����Խ�磬Ҳ�����Խ��ɻ��ص����á�\n���������õķɻ�ͷ��������0 - 9��Χ�ڣ������п��ܻ������˽��⣬���磺1 1 r\n\n");



		printf("��ѡ��\n1.˫�˶�ս(���롰1��) \n2.�˻���ս(���롰2��)\n");
		scanf("%c", &c);
		getchar();
	}

	if (c == '1') {//˫�˶�ս
		int x, y;
		char z;
		bool v = 1;//Ϊ0ʱ������ȷ����ѭ��

		printf("�����1����\n�����������ܷɻ�ͷ�������꣬�����ʽΪ:x(�ո�)y(�ո�)z �����磺9 2 r\n����x��y�ֱ��Ǻ������꣨���귶Χ��0-9����z������u���ϣ�d���£�l����r����\n");
		while (v) {
			printf("��������÷ɻ�1��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�2��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�3��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;
				printf("����Ϸ��������\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid1[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}
		initmap3();

		while (getchar() != '1') { printf("������1ȷ��\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");


		printf("�����2����\n�����������ܷɻ�ͷ�������꣬�����ʽΪ:x(�ո�)y(�ո�)z �����磺9 2 r\n����x��y�ֱ��Ǻ������꣨���귶Χ��0-9����z������u���ϣ�d���£�l����r����\n");
		v = 1;
		while (v) {
			printf("��������÷ɻ�1��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[1][0] = x;
				ky[1][0] = y;
				kz[1][0] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�2��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[1][1] = x;
				ky[1][1] = y;
				kz[1][1] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�3��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[1][2] = x;
				ky[1][2] = y;
				kz[1][2] = z;
				printf("����Ϸ��������\n");
			}
		}


		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid2[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}

		initmap4();
		while (getchar() != '2') { printf("������2ȷ��\n"); }
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n��Ϸ��ʼ\n");

		initmap();

		int n = 1;

		while (roundPvP(n)) {
			n++;
		}

	}

	else if (c == '2') {//�˻���ս
		int x, y;
		char z;
		bool v = 1;//Ϊ0ʱ������ȷ����ѭ��

		printf("����Ҿ���\n�����������ܷɻ�ͷ�������꣬�����ʽΪ:x(�ո�)y(�ո�)z �����磺9 2 r\n����x��y�ֱ��Ǻ������꣨���귶Χ��0-9����z������u���ϣ�d���£�l����r����\n");
		while (v) {
			printf("��������÷ɻ�1��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][0] = x;
				ky[0][0] = y;
				kz[0][0] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�2��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][1] = x;
				ky[0][1] = y;
				kz[0][1] = z;
				printf("����Ϸ��������\n");
			}
		}
		v = 1;
		while (v) {
			printf("��������÷ɻ�3��ͷ��λ�ã��Լ��ɻ��ķ���\n");
			scanf("%d%d", &x, &y);
			getchar();
			scanf("%c", &z);
			v = checkboundry(x, y, z);
			if (v) {
				printf("����Ƿ���\n");
			}
			else {
				kx[0][2] = x;
				ky[0][2] = y;
				kz[0][2] = z;
				printf("����Ϸ��������\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid1[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}
		initmap3();

		while (getchar() != '1') { printf("������1ȷ��\n"); }
		printf("\n���Եȣ�������������...");
		//BOT��grid2[][]��������÷ɻ����㷨
		v = 1;
		int count = 0;
		int error = 0;
		while (v) {
			//printf("��������÷ɻ�1��ͷ��λ�ã��Լ��ɻ��ķ���\n");
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
				printf("\n\n������1,���Ե�...");
			}
		}
		v = 1;
		while (v) {
			//printf("��������÷ɻ�2��ͷ��λ�ã��Լ��ɻ��ķ���\n");
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
						printf("\n���ż�����û�����⣬��BOT����һ���");
					}
					else if (error == 20) {
						printf("\nBOT�������е��");
					}
					else if (error == 40) {
						printf("\nBOT�����ĺ����е�̫���ˣ�Ҫ���˳����ԣ�");
					}
					else if (error == 60) {
						printf("\n���ڵ���");
					}
					else if (error == 80) {
						printf("\nBOTȷ���ǿ�ס�ˣ�����ǿ���˳���Ϸ");
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
				printf("\n\n������2,���Ե�...");
			}
		}
		v = 1;
		while (v) {
			//printf("��������÷ɻ�3��ͷ��λ�ã��Լ��ɻ��ķ���\n");
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
						printf("\n���ż�����û�����⣬��BOT����һ���");
					}
					else if (error == 40) {
						printf("\nBOT�������е��");
					}
					else if (error == 80) {
						printf("\nBOT�����ĺ����е�̫���ˣ�Ҫ���˳����ԣ�");
					}
					else if (error == 120) {
						printf("\n���ڵ���");
					}
					else if (error == 160) {
						printf("\nBOTȷ���ǿ�ס�ˣ�����ǿ���˳���Ϸ");
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
				printf("\n\n������3,��Ϸ������ʼ\n\n");
			}
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid2[i][j] = grid[i][j];
				grid[i][j] = 0;
			}
		}

		initmap4();
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n������������ϣ���Ϸ��ʼ\n");
		initmap();

		int n = 1;

		while (roundPvE(n)) {
			n++;
		}

	}

	printf("\n����������0�˳���Ҳ�������ϻ����鿴�Ծֹ���\n");
	int s = 1;
	while (s != 0) {
		scanf("%d", &s);
	}
	return 0;

}
