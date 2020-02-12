#include <iostream>
#define ABS(a) ((a) < 0 ? (a) * -1 : (a))
using namespace std;
#define MAXN 51
int map[MAXN][MAXN];
int home[MAXN * 2][2]; 
int chicken[14][2];
int N, M, htop, ctop, sol = 0x7fffffff;

int check_distance(int chick[]) {
	int min, dis, total = 0;
	for (int i = 0; i < htop; i++) {
		min = 0x7fffffff;
		for (int j = 0; j < M; j++) {
			dis = ABS(home[i][0] - chicken[chick[j]][0]) + ABS(home[i][1] - chicken[chick[j]][1]);
			min = dis < min ? dis : min;
		}
		total += min;
	}
	return total;
}

void dfs(int arr[], int top, int target) {
	// 0~ctop에서 M개 골라서 check_distance 호출
	if (top == M) {
		int res = check_distance(arr);
		sol = res < sol ? res : sol;
	}
	else if (target < ctop) {
		arr[top] = target;
		dfs(arr, top + 1, target + 1);
		arr[top] = 0;
		dfs(arr, top, target + 1);
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				home[htop][0] = i;
				home[htop][1] = j;
				++htop;
			}
			else if (map[i][j] == 2) {
				chicken[ctop][0] = i;
				chicken[ctop][1] = j;
				++ctop;
			}
		}
	}
	int arr[15];
	dfs(arr, 0, 0);
	cout << sol << endl;
}
