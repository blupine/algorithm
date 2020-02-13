#include <iostream>
#include <algorithm>
#define INF 0x7fffffff
#define MAXN 101
using namespace std;
int N, M, K, x, y, z;
const int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };;
#define INBOUND(r, c) (r >= 1 && r <= N && c >= 1 && c <= N)
typedef struct Ground {
	int nutrition;
	int trees[MAXN * 10]; // {age}
	int top;
	int next_nutrition;
	Ground() { nutrition = 5; next_nutrition = 0; }

};

Ground map[MAXN][MAXN];
int A[MAXN][MAXN];
int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		map[x][y].trees[map[x][y].top++] = z;
	}

	for (int year = 0; year < K; year++) {
		//spring
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				sort(map[i][j].trees, map[i][j].trees + map[i][j].top);
				int next_top = map[i][j].top;
				for (int k = 0; k < map[i][j].top; k++) {
					if (map[i][j].nutrition >= map[i][j].trees[k]) {
						map[i][j].nutrition -= map[i][j].trees[k];
						map[i][j].trees[k]++;
					}
					else {
						map[i][j].next_nutrition += map[i][j].trees[k] / 2;
						map[i][j].trees[k] = INF;
						next_top--;
						//break;
					}
				}
				map[i][j].top = next_top;
			}
		}


		//summer
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				map[i][j].nutrition += map[i][j].next_nutrition;
				map[i][j].next_nutrition = 0;
			}
		}
		//fall
		int nextrow, nextcol;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				for (int c = 0; c < map[i][j].top; c++) {
					if (map[i][j].trees[c] % 5 == 0) {
						for (int d = 0; d < 8; d++) {
							nextrow = i + dir[d][0], nextcol = j + dir[d][1];
							if (INBOUND(nextrow, nextcol)) {
								map[nextrow][nextcol].trees[map[nextrow][nextcol].top++] = 1;
							}
						}
					}
				}
			}
		}
		//winter
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				map[i][j].nutrition += A[i][j];
			}
		}
	}
	int sol = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sol += map[i][j].top;
		}
	}
	cout << sol << endl;
}
