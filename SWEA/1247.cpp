#include <iostream>
using namespace std;
#define ABS(a) ((a) < 0 ? (a)*-1 : (a))

int T, N, _min;
int pos[14][2];
bool visit[13];
void init() {
	_min = 0x7fffffff;
	for (int i = 0; i < 13; i++) visit[i] = false;
}

void solve(int depth, int curdis, int curpos) {
	if (curdis > _min) return;
	
	if (depth == N) {
		curdis += ABS(pos[curpos][0] - pos[N + 1][0]) + ABS(pos[curpos][1] - pos[N + 1][1]);
		_min = curdis < _min ? curdis : _min;
	}
	else {
		for (int i = 1; i <= N; i++) {
			if (!visit[i]) {
				visit[i] = true;
				solve(depth + 1, curdis + ABS(pos[curpos][0] - pos[i][0]) + ABS(pos[curpos][1] - pos[i][1]), i);
				visit[i] = false;
			}
		}
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		cin >> N;
		cin >> pos[0][0] >> pos[0][1] >> pos[N + 1][0] >> pos[N + 1][1];
		for (int i = 1; i <= N; i++) {
			cin >> pos[i][0] >> pos[i][1];
		}

		solve(0, 0, 0);

		cout << "#" << tc << " " << _min << "\n";
	}
}
