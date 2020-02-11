#include <iostream>
#define LADDER 1
using namespace std;
int N, M, H, sol; // N 은 col, H 는 row
int map[31][11];// i, j == LADDER -> (i, j) -> (i, j + 1)로 사다리
bool check()
{
	bool ret = true;
	for (int j = 1; j <= N; j++) {
		int curR = 0, curC = j;
		while (curR <= H) {

			if (curC != N && map[curR][curC] == LADDER) 
				curC++;
			
			else if (curC != 1 && map[curR][curC - 1] == LADDER) 
				curC--;
			
			curR++;
		}
		if (curC != j) {
			ret = false;
			break;
		}
	}
	return ret;
}


bool dfs(int arr[], int c, int index, int start, int end) {
	bool ret = false;
	if (index == c) {
		for (int i = 0; i < c; i++) {
			int row = (arr[i] / (N - 1)) + 1;
			int col = (arr[i] % (N - 1)) + 1;
			map[row][col] = LADDER;
		}
		if (check()) return true;
		for (int i = 0; i < c; i++) {
			int row = (arr[i] / (N - 1)) + 1;
			int col = (arr[i] % (N - 1)) + 1;
			map[row][col] = 0;
		}
		return false;
	}
	else if(start < end){
		// start번째를 넣었을 때 dfs, 넣지 않았을 때 dfs
		int row = (start / (N - 1)) + 1;
		int col = (start % (N - 1)) + 1;
		if (map[row][col] != LADDER && map[row][col - 1] != LADDER) {
			//printf("%d, %d\n", row, col);

			arr[index] = start;
			ret = dfs(arr, c, index + 1, start + 1, end);
			if (ret) return true;
			arr[index] = 0;
		}
		ret = dfs(arr, c, index, start + 1, end);
	}
	return ret;
}


void solve() {
	bool flag = check();
	if (flag) sol = 0;
	else {
		int last = 3;
		if ((N - 1) * H < 3) last = (N - 1) * H;
		for (int i = 1; i <= last; i++) {
			int arr[10];
			flag = dfs(arr, i, 0, 0, (N - 1) * H);
			if (flag) {
				sol = i;
				break;
			}
			if (i == last) sol = -1;
		}
	}

}



int a, b;

int main() {
	cin >> N >> M >> H;
	bool c = true;
	for (int i = 1; i <= M; i++) {
		cin >> a >> b;
		map[a][b] = LADDER;
	}

	solve();

	cout << sol << "\n";
}
