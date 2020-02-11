#include <iostream>

using namespace std;
char topni[4][9];
int visit[4];
int left_index[4] = { 6, 6, 6, 6 };
int rot_dir[4];
int k, sol, x, d;

#define R_INDEX(i) ((left_index[i] + 4) % 8)
#define L_INDEX(i) (left_index[i])

void rotate(int th, int dir) {
	rot_dir[th] = dir;
	for (int i = th + 1; i < 4; i++) {
		if (topni[i - 1][R_INDEX(i - 1)] == topni[i][L_INDEX(i)])
			break;
		dir = dir == 1 ? -1 : 1;
		rot_dir[i] = dir;
	}
	dir = rot_dir[th];
	for (int i = th - 1; i >= 0; i--) {
		if (topni[i + 1][L_INDEX(i + 1)] == topni[i][R_INDEX(i)])
			break;
		dir = dir == 1 ? -1 : 1;
		rot_dir[i] = dir;
	}
}

int main() {
	for (int i = 0; i < 4; i++)
		cin >> topni[i];
	cin >> k;
	for (int i = 0; i < k; i++) {
		visit[0] = visit[1] = visit[2] = visit[3] = 0;
		rot_dir[0] = rot_dir[1] = rot_dir[2] = rot_dir[3] = 0;
		cin >> x >> d;
		rotate(x - 1, d);

		for (int i = 0; i < 4; i++) {
			left_index[i] = (left_index[i] + rot_dir[i] * -1) % 8;
			if (left_index[i] < 0) left_index[i] += 8;
		}
	}
	int mul[4] = { 1, 2, 4, 8 };

	for (int i = 0; i < 4; i++) {
		int tw_index = (left_index[i] + 2) % 8;
		sol += topni[i][tw_index] == '0' ? 0 : mul[i];
	}

	cout << sol << "\n";
}
