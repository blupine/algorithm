#include <iostream>
#include <vector>
using namespace std;
int map[101][101];
int gen[21]; int top = 0;
int dir[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

typedef struct Dragon_pos{
	int x, y;
	int dir;
	Dragon_pos() {};
	Dragon_pos(int a, int b, int c) {
		x = a; y = b; dir = c;
	}
}Dragon_pos;

vector<Dragon_pos> dragons[21];

int N, x, y, d, g;
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		gen[top] = g;
		dragons[top].push_back(Dragon_pos(x, y, d));
		dragons[top].push_back(Dragon_pos(x + dir[d][0], y + dir[d][1], -1));
		top++;
		map[x][y] = 1;
		map[x + dir[d][0]][y + dir[d][1]] = 1;
	}
	for (int i = 0; i < N; i++) {
		while (gen[i]) {
			//dragons[i] 의 맨 뒤에서 두번째 점부터 시작해서 새로운 점을 만들어나감
			int last = dragons[i].size() - 1;
			int size = dragons[i].size();
			int startX = dragons[i].back().x;
			int startY = dragons[i].back().y;

			for (int j = size - 2; j >= 0; j--) {
				int new_dir = (dragons[i][j].dir + 1) % 4;

				startX = startX + dir[new_dir][0];
				startY = startY + dir[new_dir][1];
				
				map[startX][startY] = 1;
				dragons[i][last].dir = new_dir;
				dragons[i].push_back(Dragon_pos(startX, startY, -1));
				
				last = dragons[i].size() - 1;
			}

			gen[i]--;
		}
	}
	int sol = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1)
				sol++;
		}
	}
	cout << sol << endl;

}
