#include <iostream>
#define PLUS 1
#define MINUS 5
using namespace std;
int T, N, direction;

const char Side[6] = { 'U', 'L', 'F', 'R', 'B', 'D' };
const char color[6] = { 'w','g', 'r', 'b', 'o', 'y' };

const int dependency[6][4] = {
	{1, 4, 3, 2},//  1={0,0}, {0, 1}, {0, 2}, 2={0,0}, {0, 1}, {0, 2}
	{0, 2, 5, 4},// 
	{0, 3, 5, 1},
	{0, 4, 5, 2},
	{0, 1, 5, 3},
	{1, 2, 3, 4}
};
const int _rotate[6][4][3][2] = {
	{{{0, 0}, {0, 1}, {0, 2}}, {{0, 0}, {0, 1}, {0, 2}}, {{0, 0}, {0, 1}, {0, 2}}, {{0, 0}, {0, 1}, {0, 2}}},
	{{{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{2, 2}, {1, 2}, {0, 2}}},
	{{{2, 0}, {2, 1}, {2, 2}}, {{0, 0}, {1, 0}, {2, 0}}, {{0, 2}, {0, 1}, {0, 0}}, {{2, 2}, {1, 2}, {0, 2}}},
	{{{0, 2}, {1, 2}, {2, 2}}, {{2, 0}, {1, 0}, {0, 0}}, {{0, 2}, {1, 2}, {2, 2}}, {{0, 2}, {1, 2}, {2, 2}}},
	{{{0, 0}, {0, 1}, {0, 2}}, {{2, 0}, {1, 0}, {0, 0}}, {{2, 2}, {2, 1}, {2, 0}}, {{0, 2}, {1, 2}, {2, 2}}},
	{{{2, 0}, {2, 1}, {2, 2}}, {{2, 0}, {2, 1}, {2, 2}}, {{2, 0}, {2, 1}, {2, 2}}, {{2, 0}, {2, 1}, {2, 2}}}
};

char _cube[6][3][3];

void rot(char s) {
	int side;
	for (int i = 0; i < 6; i++) {
		if (s - Side[i] == 0) {
			side = i;
			break;
		}
	}
	char temp[3][3];
	for (int i = 0; i < 3; i++) { // 왼쪽회전
		for (int j = 0; j < 3; j++) {
			temp[i][j] = _cube[side][direction == PLUS ? (2 - j) : j][direction == PLUS ? i : (2 - i)];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			_cube[side][i][j] = temp[i][j];
		}
	}

	char temparr[4][3];
	for (int i = 0; i < 4; i++) {
		int other_side = dependency[side][i];
		for (int j = 0; j < 3; j++) {
			int row = _rotate[side][i][j][0];
			int col = _rotate[side][i][j][1];
			temparr[i][j] = _cube[other_side][row][col];
		}
	}
	if (direction == PLUS){
		for (int i = 0; i < 4; i++) {
			int other_side = dependency[side][i];
			for (int j = 0; j < 3; j++) {
				int row = _rotate[side][i][j][0];
				int col = _rotate[side][i][j][1];
				
				_cube[other_side][row][col] = temparr[(i + 3) % 4][j]; // side가 0, 1, 2
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			int other_side = dependency[side][i];
			for (int j = 0; j < 3; j++) {
				int row = _rotate[side][i][j][0];
				int col = _rotate[side][i][j][1];
				_cube[other_side][row][col] = temparr[(i + 1) % 4][j];

			}
		}
	}
}

void init() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				_cube[i][j][k] = color[i];
			}
		}
	}
}

int main() {
	char dir, side;
	cin >> T;
	for (int i = 0; i < T; i++) {
		init();
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> side >> dir;
			dir == '+' ? direction = 1 : direction = 5;
			rot(side);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << _cube[0][i][j];
			}
			cout << endl;
		}
	}
}
