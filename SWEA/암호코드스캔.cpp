#include <iostream>
#include <cstring>
using namespace std;
int T, N, M;
char arr[50][101];
char str[10][8] = { "0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};

typedef struct Trie {
	bool isleaf;
	int val;
	Trie *child[2];
};
Trie nodes[100]; int mcount;
Trie root;
Trie * new_node() { return &nodes[mcount++]; }
void insert(Trie * ptr, char* str, int v) {
	if (*str == '\0') {
		ptr->isleaf = true;
		ptr->val = v;
	}
	else{
		if (ptr->child[*str - '0'] == '\0')
			ptr->child[*str - '0'] = new_node();
		insert(ptr->child[*str - '0'], str + 1, v);
	}
}
int _find(Trie * ptr, char * str) {
	if (ptr->isleaf == true) return ptr->val;
	if (ptr->child[*str - '0'] == '\0') return -1;
	return _find(ptr->child[*str - '0'], str + 1);
}
void init_trie() {
	for (int i = 0; i < 10; i++) {
		insert(&root, str[i], i);
	}
}

int main() {
	init_trie();
	cin >> T;
	for (int i = 1; i <= T; i++) {
		int sol = 0;
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}
		for (int i = 0; i < N; i++) {
			// 각 행에 대해서 암호코드 찾기 시작
			int cipher[8], ctop = 0;
			for (int padding = 0; padding < 7; padding++) {
				for (int index = padding; index <= strlen(arr[i]) - 7; index += 7) {
					if (ctop == 8) {
						padding = 8;
						break;
					}
					int temp = _find(&root, arr[i] + index);
					if (temp == -1) {
						ctop = 0;
					}
					else {
						cipher[ctop++] = temp;
					}
				}
			}
			if (ctop == 8) {
				int checksum = (cipher[0] + cipher[2] + cipher[4] + cipher[6]) * 3 + (cipher[1] + cipher[3] + cipher[5]) + cipher[7];
				if (checksum % 10 == 0) {
					for (int i = 0; i < 8; i++)
						sol += cipher[i];
					break;
				}
			}
		}
		cout << "#" << i << " " << sol << endl;
	}

}
