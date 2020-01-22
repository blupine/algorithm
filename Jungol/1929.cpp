/*
 1. 작운 순서를 높은 우선순위로 힙 유지
 2. 힙에서 두 숫자를 pop, 더한 뒤에 다시 push, 그리고 총 결과에 더해줌
*/


#include <iostream>
#define MAXNODE 50000
using namespace std;

int N, input;
int heap[MAXNODE * 4 + 1];
int heap_size;

void insert(int item) { 
	int index = ++heap_size;
	while (index != 1 && heap[index / 2] > item) {
		heap[index] = heap[index / 2];
		index /= 2;
	}
	heap[index] = item;
 }

int pop() {
	int ret = heap[1];
	int last = heap[heap_size--];
	int parent = 1;
	int child = 2;
	while (child <= heap_size) {
		if (heap[child] > heap[child + 1]) child += 1;
		if (last < heap[child]) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = last;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> input;
		insert(input);
	}

	long long res = 0, cur =0;
	while (heap_size != 1) {
		cur = pop() + pop();
		res += cur;
		insert(cur);
	}
	cout << res << endl;
}
