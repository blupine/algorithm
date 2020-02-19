#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

using namespace std;
int dr[4] = { 0, 0, -1, 1 };
int dc[4] = { 1, -1, 0, 0 };
int map[100][100];
int dist[100][100];

int T, N, sol;
#define INBOUND(r, c) (r < N && r >= 0 && c < N && c >= 0)

typedef struct Move {
	int row, col, depth;
}Move;

Move heap[1000]; int heap_size;
void push(Move a) {
	int index = ++heap_size;
	while (index != 1 && heap[index / 2].depth > a.depth) {
		heap[index] = heap[index / 2];
		index /= 2;
	}
	heap[index] = a;
}
Move pop() {
	Move ret = heap[1];
	int last = heap_size--;
	int parent = 1, child = 2;
	while (child < last ) {
		if (heap[child].depth > heap[child + 1].depth) child += 1;
		if (heap[last].depth < heap[child].depth) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = heap[last];
	return ret;
}

void solve() {
	push({ 0, 0, 0 });
	while (heap_size) {
		Move cur = pop();
		if (dist[cur.row][cur.col] >= cur.depth) {
			dist[cur.row][cur.col] = cur.depth;

			for (int i = 0; i < 4; i++) {
				int nextrow = cur.row + dr[i];
				int nextcol = cur.col + dc[i];
				if (!INBOUND(nextrow, nextcol)) continue;
				int nextdis = cur.depth + map[nextrow][nextcol];
				if (nextdis < dist[nextrow][nextcol]) {
					dist[nextrow][nextcol] = nextdis;
					push({ nextrow, nextcol, nextdis });
				}
			}
		}
	}
}
void init() {
	heap_size = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = 0x7fffffff;
		}
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;

		init();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf(" %1d", &map[i][j]);
				//cin >> map[i][j];
			}
		}
		
		solve();
		cout << "#" << tc << " " << dist[N-1][N-1] << "\n";
	}
}
