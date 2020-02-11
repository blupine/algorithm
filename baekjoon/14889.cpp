#include <iostream>
#include <vector>
#include <algorithm>
#define GAP(a, b) ((a) - (b) > 0 ? (a) - (b) : (b) - (a))
#define MAXN 21
using namespace std;
int map[MAXN][MAXN];
int N;
int main() {
	cin >> N;
	vector<int> comb, ind;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> map[i][j];
		}
		comb.push_back(i);
		ind.push_back(i <= N / 2 ? 0 : 1);
	}
	// N개 중 N/2개 선택, 나머지랑 점수 계산해서 
	vector<int> teamA, teamB;
	int scoreA, scoreB;
	int gap = 0x7fffffff, temp;
	do {
		scoreA = 0, scoreB = 0;
		teamA.clear(); teamB.clear();
		for (int i = 0; i < ind.size(); i++) {
			if (ind[i] == 1)
				teamA.push_back(comb[i]);
			else
				teamB.push_back(comb[i]);
		}
		for (int i = 0; i < teamA.size() - 1; ++i) {
			for (int j = i + 1; j < teamA.size(); ++j) {
				scoreA += map[teamA[i]][teamA[j]] + map[teamA[j]][teamA[i]];
			}
		}
		for (int i = 0; i < teamB.size() - 1; ++i) {
			for (int j = i + 1; j < teamB.size(); ++j) {
				scoreB += map[teamB[i]][teamB[j]] + map[teamB[j]][teamB[i]];
			}
		}
		temp = GAP(scoreA, scoreB);
		gap = temp < gap ? temp : gap;
		if (gap == 0) break;
	} while (next_permutation(ind.begin(), ind.end()));
	cout << gap << "\n";
}
