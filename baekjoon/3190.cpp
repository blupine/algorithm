#include <iostream>
#include <deque>
#define MAXN 101
using namespace std;
deque<pair<int, int> > directions;
deque<pair<int, char> > snakes;

int MAP[MAXN][MAXN];
int N, K, L, X, Row, Col;
char C;
int cur_dir = 0;
int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}};// 우 하 좌 상
// L일때 0->3, 1->0, 2->1, 3-> 2 // (cur_dir + 3) % 4
// D일때 0-?1, 1->2, 2->3, 3-> 0 // (cur_dir + 1) % 4

bool validcheck(pair<int, int> pos) {
	if (pos.first <= N && pos.first >= 1 && pos.second <= N && pos.second >= 1
		&& MAP[pos.first][pos.second] != 1) // 자기 몸이 아닐 때
		return true;
	return false;
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < K; i++) {
		cin >> Row >> Col;
		MAP[Row][Col] = 9; // apple
	}
	MAP[1][1] = 1;
	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		directions.push_back(make_pair(X, C));
	}
	int time = 0;
	pair<int, int> head, tail, nexthead;
	snakes.push_back(make_pair(1, 1));
	while (1) {
		head = snakes.back();

		if (!directions.empty() && time == directions[0].first) {
			// 방향 전환
			if (directions[0].second == 'L') cur_dir = (cur_dir + 3) % 4;
			else if (directions[0].second == 'D') cur_dir = (cur_dir + 1) % 4;
			directions.pop_front();
		}
		time++;
		nexthead = make_pair(head.first + dir[cur_dir][0], head.second + dir[cur_dir][1]);

		if (validcheck(nexthead)) {
			snakes.push_back(nexthead);
			if (MAP[nexthead.first][nexthead.second] != 9) {
				tail = snakes[0];
				snakes.pop_front();
				MAP[tail.first][tail.second] = 0;
			}
			MAP[nexthead.first][nexthead.second] = 1;
		}
		else {
			break;
		}
	}
	cout << time << endl;

}
