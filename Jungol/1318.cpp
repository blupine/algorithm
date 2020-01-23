#include <iostream>
#define MAXN 1500
using namespace std;

int N;
long long heap[MAXN * 20 + 1];
int heap_size;
long long sol[MAXN + 1];
int sol_top;

void insert(long long item) {
	int index = ++heap_size;
	while (index != 1 && heap[index / 2] > item) {
		heap[index] = heap[index / 2];
		index /= 2;
	}
	heap[index] = item;
}

long long pop() {
	long long ret = heap[1];
	long long last = heap[heap_size--];
	int parent = 1, child = 2;
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
	insert(1);
	long long cur = 0;
	long long prev = -1;
	while (cin >> N) {
		if (N == 0) break;
		else {
			if (N < sol_top) {
				cout << sol[N - 1] << "\n";
			}
			else {
				while (N >= sol_top) {
					cur = pop();
					if (cur == prev) continue;
					
					sol[sol_top++] = cur;

					insert(cur * 2);
					insert(cur * 3);
					insert(cur * 5);

					prev = cur;
				}
				cout << sol[N - 1] << "\n";
			}
		}
	}
}
