#include <iostream>
#define MAXN 101
#define ABS(a) ((a) < 0 ? (a) * -1 : (a))
using namespace std;
int map[MAXN][MAXN];
bool hbuilt[MAXN][MAXN];
bool vbuilt[MAXN][MAXN];
int N, L, sol;
int main() {
	cin >> N >> L;
	for (int i = 1; i <= N; ++i) 
	{
		for (int j = 1; j <= N; ++j) 
		{
			cin >> map[i][j];
			hbuilt[i][j] = vbuilt[i][j] = false;
		}
	}
	for (int i = 1; i <= N; ++i)
	{
		// 가로로
		int prev = map[i][1];
		for (int j = 2; j <= N; j++) {
			if (prev != map[i][j]) {
				if (ABS(map[i][j] - prev) > 1) break;

				if (map[i][j] > prev) {
					for (int k = 1; k <= L; k++) {
						if (j - k < 1 || map[i][j - k] != prev || hbuilt[i][j - k]) {
							j = N + 1;
							break;	// 범위 초과 또는 경사가 일치하지 않거나 이미 건설했을 경우
						}
						hbuilt[i][j - k] = true;
					}
				}
				else if (map[i][j] < prev) {
					for (int k = 0; k < L; k++) {
						// 현재 위치부터 L만큼 건설 가능한지 확인
						if (j + k > N || map[i][j + k] != map[i][j] || hbuilt[i][j + k]) {
							j = N + 1;
							break;// 범위 초과 또는 경사가 일치하지 않거나 이미 건설했을 경우
						}
						hbuilt[i][j + k] = true;
					}
				}
			}
			prev = map[i][j];
			if (j == N) sol++;
		}
		prev = map[1][i];
		for (int j = 2; j <= N; j++) {
			if (prev != map[j][i]) {
				if (ABS(map[j][i] - prev) > 1) break;
		
				if (map[j][i] > prev) {
					for (int k = 1; k <= L; k++) {
						if (j - k < 1 || map[j - k][i] != prev || vbuilt[j - k][i]) {
							j = N + 1;
							break;
						}
						vbuilt[j - k][i] = true;
					}
				}
				else if (map[j][i] < prev) {
					for (int k = 0; k < L; k++) {
						if (j + k > N || map[j + k][i] != map[j][i] || vbuilt[j + k][i]) {
							j = N + 1;
							break;
						}
						vbuilt[j + k][i] = true;
					}
				}
			}
			prev = map[j][i];
			if (j == N) sol++;
		}
	}
	cout << sol << "\n";
}
