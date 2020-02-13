#include <iostream>
#include <deque>
#include <utility>
#define ABS(a) ((a) < 0 ? (a) * -1 : (a))
#define MAXN 51

using namespace std;
int N, L, R, cnt;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int visit[MAXN][MAXN];
int map[MAXN][MAXN];
#define INBOUND(r, c) (r >= 1 && r <= N && c >= 1 && c <= N)

int main() {
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	int nextrow, nextcol, row, col;
	deque<deque<pair<int, int> > > l;
	do {
		l.clear();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (visit[i][j] == 0) {
					visit[i][j] = 1;
					deque<pair<int, int> > q, uni;
					q.push_back(make_pair(i, j));
					uni.push_back(make_pair(i, j));
					while (!q.empty()) {
						row = q[0].first, col = q[0].second;
						q.pop_front();
						for (int i = 0; i < 4; i++) {
							nextrow = row + dx[i], nextcol = col + dy[i];
							if (INBOUND(nextrow, nextcol) && visit[nextrow][nextcol] == 0 &&
								ABS(map[row][col] - map[nextrow][nextcol]) >= L && ABS(map[row][col] - map[nextrow][nextcol]) <= R) {
								visit[nextrow][nextcol] = 1;
								q.push_back(make_pair(nextrow, nextcol));
								uni.push_back(make_pair(nextrow, nextcol));
							}
						}
					}
					if(uni.size() != 1) // 연합에 포함된 땅이 2개 이상일 때만
						l.push_back(uni);
				}
			}
		}
		if (!l.empty()) cnt++;

		for (int i = 0; i < l.size(); i++) {
			//l[i] = 같은 연합의 위치 저장
			int sum = 0, avg;
			for (int j = 0; j < l[i].size(); j++) {
				sum += map[l[i][j].first][l[i][j].second];
			}
			avg = sum / l[i].size();
			for (int j = 0; j < l[i].size(); j++) {
				map[l[i][j].first][l[i][j].second] = avg;
			}
		}

		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				visit[i][j] = 0;
	} while (!l.empty());
	cout << cnt << endl;
}
