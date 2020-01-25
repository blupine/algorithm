/*
1. Heap을 Maxheap, MinHeap 두개 유지
2. 들어온 두 숫자 중 작은 값을 먼저 Maxheap에 삽입, 이후 Maxheap에서 pop한 값을 Minheap에 삽입
3. 들어온 두 숫자 중 큰 값은 Minheap에 삽입, 이후 Minheap에서 pop한 값을 Maxheap에 삽입
4. Maxheap의 크기가 항상 1 크며, Maxheap에서 가장 큰 값이 중간 값임.

*/


#include <iostream>
#define MAXNODE 20000
#define MAXHEAP 1
#define MINHEAP 0
using namespace std;

int N, first, P, Q;
int maxheap[MAXNODE * 4 + 1]; int maxheap_size;
int minheap[MAXNODE * 4 + 1]; int minheap_size;

void insert(int item, int mode) { // if mode == 1 -> maxheap, 0 -> minheap
	int index = (mode == 1 ? ++maxheap_size : ++minheap_size);
	while (index != 1) {
		if (mode) { // maxheap
			if (maxheap[index / 2] > item) break;
			maxheap[index] = maxheap[index / 2];
		}
		else { // minheap
			if (minheap[index / 2] < item) break;
			minheap[index] = minheap[index / 2];
		}
		index /= 2;
	}
	if (mode) maxheap[index] = item;
	else minheap[index] = item;
}

int pop(int mode) {
	int ret, last, parent = 1, child = 2, heap_size;
	if (mode) {
		ret = maxheap[1];
		last = maxheap[maxheap_size--];
		heap_size = maxheap_size;
	}
	else {
		ret = minheap[1];
		last = minheap[minheap_size--];
		heap_size = minheap_size;
	}
	while (child <= heap_size) {
		if (mode) {
			// maxheap
			if (maxheap[child] < maxheap[child + 1]) child += 1;
			if (last > maxheap[child]) break;
			maxheap[parent] = maxheap[child];
			
		}
		else {
			if (minheap[child] > minheap[child + 1]) child += 1;
			if (last < minheap[child]) break;
			minheap[parent] = minheap[child];
		}
		parent = child;
		child *= 2;
	}
	if (mode) maxheap[parent] = last;
	else minheap[parent] = last;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N >> first;
	cout << first << "\n";
	insert(first, MAXHEAP);
	for (int i = 0; i < (N - 1) / 2; i++) {
		cin >> P >> Q;
		if (P > Q) { // swap
			P = P ^ Q;
			Q = P ^ Q;
			P = P ^ Q;
		}
		insert(P, MAXHEAP);
		insert(pop(MAXHEAP), MINHEAP);
		insert(Q, MINHEAP);
		insert(pop(MINHEAP), MAXHEAP);
		cout << maxheap[1] << "\n";
	}

}
