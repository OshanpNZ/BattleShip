/* Go to main to play game */



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 7
#define HIT 1000


void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);




int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	int map[MAP_SIZE][MAP_SIZE] = { 0 };
	int shots[MAP_SIZE][MAP_SIZE] = { 0 };

	InitialiseMap(map);
	printf("Shots:\n");

	//replace ? with a map coordinate to fire a shot and copy and past the next two lines to fire more shots.
	FireShot(shots, map, ?, ?);
	PrintArray(shots);

	CheckGameOver(shots, map);

	return 0;
}



void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (j == MAP_SIZE - 1) {
				printf("%d", values[i][j]);
			}
			else {
				printf("%d ", values[i][j]);
			}
		}
		printf("\n");
	}
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			map[i][j] = 0;
		}
	}
	
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (i == 0 && j < 5) {
				map[i][j] = 5;
			}
			if (i == MAP_SIZE - 1 && j<4) {
				map[i][j] = 4;
			}
			if (i == (int)(MAP_SIZE / 2) && j == (int)(MAP_SIZE / 2)) {
				map[i][j] = 3;
				map[i][j-1] = 3;
				map[i][j+1] = 3;
			}
			if (i == MAP_SIZE - 1 && j == MAP_SIZE - 1) {
				map[i][j] = 2;
				map[i - 1][j] = 2;
			}
		}
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int direction = (rand() % 2) + 0;

	if (direction == 0) {
		int startRow = (rand() % (MAP_SIZE)) + 0;
		int startCol = (rand() % (MAP_SIZE - size - 0 + 1)) + 0;
		for (int i = startCol; i < startCol + size; i++) {
			map[startRow][i] = size;
		}
	}

	if (direction == 1) {
		int startCol = (rand() % (MAP_SIZE)) + 0;
		int startRow = (rand() % (MAP_SIZE - size - 0 + 1)) + 0;
		for (int i = startRow; i < startRow + size; i++) {
			map[i][startCol] = size;
		}
	}
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int count;
	count = 0;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == value) {
				count++;
			}
		}
	}

	return count;
}


int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE])
{
	*row = MAP_SIZE - 1;
	*col = MAP_SIZE - 1;

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				if (i < *row || j < *col) {
					*row = i;
					*col = j;
				}
			}
		}
	}
	
	if (map[*row][*col+1] == size) {
		return 1;
	}
	else {
		return 2;
	}
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	if (CountValues(size,map) != size) {
		return 0;
	}
	int row, col;
	int direction = TopLeftPosition(size, &row, &col, map);

	if (direction == 2) {
		for (int i = row; i < row + size; i++) {
			if (col != 0) {
				if (map[i][col - 1] != 0) {
					return 0;
				}
			}

			if (col != MAP_SIZE - 1) {
				if (map[i][col + 1] != 0) {
					return 0;
				}
			}

			if (i == row && row != 0) {
				if (map[i - 1][col] != 0) {
					return 0;
				}
			}

			if (i == row + size - 1 && i != MAP_SIZE - 1) {
				if (map[i + 1][col] != 0) {
					return 0;
				}
			}
		}
	}

	if (direction == 1) {
		for (int i = col; i < col + size; i++) {
			if (row != 0) {
				if (map[row-1][i] != 0) {
					return 0;
				}
			}

			if (row != MAP_SIZE - 1) {
				if (map[row+1][i] != 0) {
					return 0;
				}
			}

			if (i == col && col != 0) {
				if (map[row][i-1] != 0) {
					return 0;
				}
			}

			if (i == col + size - 1 && i != MAP_SIZE - 1) {
				if (map[row][i+1] != 0) {
					return 0;
				}
			}
		}
	}

	return 1;
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	int valid = 0;

	while (valid == 0) {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				map[i][j] = 0;
			}
		}

		AddRandomShip(2, map);
		AddRandomShip(3, map);
		AddRandomShip(4, map);
		AddRandomShip(5, map);

		for (int i = 2; i < 6; i++) {
			if (IsShipValid(i, map) == 0) {
				valid = 0;
				break;
			}
			else {
				valid = 1;
			}
		}
	}
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int shotnum = 1;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (shots[i][j] != 0) {
				shotnum++;
			}
		}
	}

	if (map[row][col] == 0 && shots[row][col] == 0) {
		shots[row][col] = shotnum;
	}

	if (map[row][col] != 0 && shots[row][col] == 0) {
		shots[row][col] = shotnum + 1000;

		int ship = map[row][col];
		int hit = 0;

		if (ship != 0) {
			for (int i = 0; i < MAP_SIZE; i++) {
				for (int j = 0; j < MAP_SIZE; j++) {
					if (map[i][j] == ship && shots[i][j] > 1000) {
						hit++;
					}
				}
			}
			if (hit == ship) {
				for (int i = 0; i < MAP_SIZE; i++) {
					for (int j = 0; j < MAP_SIZE; j++) {
						if (map[i][j] == ship) {
							shots[i][j] = shots[i][j] + ((ship - 1) * 1000);
						}
					}
				}
			}
		}
	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] != 0 && shots[i][j] < 1000) {
				return 0;

			}
		}
	}
	return 1;
}














