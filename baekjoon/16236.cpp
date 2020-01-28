#include <iostream>
#include <deque>
#include <cstring>
#include <utility>
#include <algorithm>
#define MAXN 21

using namespace std;
const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

typedef pair<int, int> Pair;
int N;
int MAP[MAXN][MAXN];
int visit[MAXN][MAXN];
Pair shark; // 현재 상어의 위치 row, col
int shark_size = 2;
int eat_count = 0;
int total_shark;

#define INBOUND(r, c) ((r >= 1) && (r <= N) && (c >= 1) && (c <= N))

bool compare(Pair pos1, Pair pos2) {
	if (pos1.first != pos2.first) return pos1.first < pos2.first;
	return pos1.second < pos2.second;
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 9) {
				shark.first = i; shark.second = j;
				MAP[i][j] = 0;
			}
			else if (MAP[i][j] != 0) total_shark++;
		}
	}
	Pair pos, nextpos;
	deque<Pair> target, shark_pos, cur, next;

	/*
	1. 4방향 탐색, 잡아먹을 상어들 vector에 넣음, 없으면 진행 가능한 곳을 queue에 넣고 다시 bfs (visit 처리 해줘야 함)
	2. vector 우선순위로 정렬, 잡아먹을 상어 선택
	3. 해당 상어로 좌표 변경, 잡아먹은 횟수 및 상어 크기 반영 - 1로 반복 ()
	4. 
	*/

	int distance = 0; // 총 이동 거리
	int cur_distance = 0; // 한 bfs 안에서 이동 거리
	shark_pos.push_back(shark);
	while(!shark_pos.empty() && total_shark != 0) {
		// 현재 위치에서 잡아먹을 수 있는 가장 가까운 상어를 찾음
		cur = shark_pos; shark_pos.pop_front();
		memset(visit, 0, MAXN * MAXN * sizeof(int));
		//memcpy(visit, eaten, MAXN * MAXN);
		while (!cur.empty() && target.empty()) { //현재 위치에서 갈 수 있는 상하좌우 탐색, target을 아직 못찾았으면 계속 bfs
			while (!cur.empty()) {
				pos = cur[0]; cur.pop_front();
				for (int i = 0; i < 4; i++) {

					nextpos = make_pair(pos.first + dir[i][0], pos.second + dir[i][1]);

					if (INBOUND(nextpos.first, nextpos.second) && visit[nextpos.first][nextpos.second] == 0) {
						// 해당 위치는 상어일 수도, 빈 공간일 수도 있음
						visit[nextpos.first][nextpos.second] = 1;
						if(MAP[nextpos.first][nextpos.second] == 0 || MAP[nextpos.first][nextpos.second] == shark_size)
							next.push_back(nextpos);
						else if (MAP[nextpos.first][nextpos.second] < shark_size) {
							target.push_back(nextpos);
					}
				}
			}
			cur_distance += 1;
			cur = next; next.clear();			
		}
		
		if (target.empty()) break; // 먹을 수 있는 상어가 더이상 없을 경우 

		distance += cur_distance;  // 현 위치에서 target을 찾기 위해 움직인 거리를 총 거리에 더해줌
		cur_distance = 0;
		
		sort(target.begin(), target.end(), compare); // 가장 우선순위가 높은 target 상어 고르기 위해 정렬
		shark = target[0]; // 첫 번째 우선순위를 가지는 상어
		target.clear();	   // 이번 bfs에서 찾은 target을 비워줌 (다음에 다시 찾아줘야 함)

		eat_count += 1;	  // 먹은 상어 증가

		if (eat_count == shark_size) 
			shark_size += 1; eat_count = 0;
		
		MAP[shark.first][shark.second] = 0;

		shark_pos.push_back(shark);
		total_shark -= 1;
	}
	cout << distance << endl;
}
