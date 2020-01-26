/*
# 2020.01.26
# Jungol 3337 : 쇼핑몰
# 풀이
	- heap 두개 사용
	- 계산중인 counter heap
	- 쉬고있는 counter heap 

	- 계산중인 힙에서 먼저 시간 0인 애들을 모두 꺼내서 쉬고있는 힙으로 삽입함
	- 쉬고있는 힙 중에서 가장 우선순위가 높은 카운터를 꺼내서 할당, 계산중인 힙으로 삽입

	-> 그러면 계산중인 카운터 힙에서 꺼낼 때 마다 남은 시간을 매번 갱신해줘야 하는데..?
	-> 일이 처리된 시간들을 누적시키고, 이 값을 쉬고있는 아이템에 일을 할당할때 더해서 큐에 넣으면 매번 갱신해주지 않아도 됨
*/

#include <iostream>
#define MAXN 100001
#define MAXK 100001
using namespace std;

typedef struct Task {
	int counter_id;
	int cart_id;
	int remain_time;
};

int _time;
int N, K, id, w;
Task temp, temp2;

bool compare1(Task t1, Task t2) { // t1의 우선순위가 높으면 true 
	if (t1.remain_time < t2.remain_time) return true;
	else if (t1.remain_time > t2.remain_time) return false;

	// 만약 남은 시간이 같다면?
	return t1.counter_id > t2.counter_id;

}
bool compare2(Task t1, Task t2) { // t1의 우선순위가 높으면 true
	return t1.counter_id < t2.counter_id;
}

Task heap1[MAXK * 4 + 1]; int heap1_size;
Task heap2[MAXK * 4 + 1]; int heap2_size;

void heap1_insert(Task item) {
	//item.remain_time += _time;// 현재까지 누적된 시간을 더해줌
	int index = ++heap1_size;
	while (index != 1 && compare1(item, heap1[index / 2])) { // 부모보다 우선순위가 높을 경우
		heap1[index] = heap1[index / 2];
		index /= 2;
	}
	heap1[index] = item;
}

Task heap1_pop() {
	Task ret = heap1[1];
	Task last = heap1[heap1_size--];
	int parent = 1, child = 2;
	while (child <= heap1_size) {
		if (!compare1(heap1[child], heap1[child + 1])) child += 1; // false일 경우 오른쪽 자식의 우선순위가 더 높음
		if (compare1(last, heap1[child])) break;

		heap1[parent] = heap1[child];
		parent = child;
		child *= 2;
	}
	
	heap1[parent] = last;
	return ret;
}

void heap2_insert(Task item) {
	int index = ++heap2_size;
	while (index != 1 && compare2(item, heap2[index / 2])) {
		heap2[index] = heap2[index / 2];
		index /= 2;
	}
	heap2[index] = item;
}
Task heap2_pop() {
	Task ret = heap2[1];
	Task last = heap2[heap2_size--];
	int parent = 1, child = 2;
	while (child <= heap2_size) {
		if (!compare2(heap2[child], heap2[child + 1])) child += 1;
		if (compare2(last, heap2[child])) break;

		heap2[parent] = heap2[child];
		parent = child;
		child *= 2;
	}
	heap2[parent] = last;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	register int i, j;
	cin >> N >> K;
	
	// 쉬고있는 힙 초기화해줘야 함
	heap2_size = K;
	for (i = 1; i <= K; ++i) {
		//heap2_insert(Task(i));
		heap2[i].counter_id = i;
	}
	
	int t, done = 1, input_count = 0;
	unsigned long long res = 0;

	while(done != N + 1){ // done == N + 1이 되면 멈춰야 함

		if (heap1_size != 0) { // 계산중인 힙을 완료, 쉬는 힙으로 넣음
			// 남은시간이 같은건 모두 pop해서 넣어야 함
			t = heap1[1].remain_time;
			_time = t;

			while (heap1_size != 0 && heap1[1].remain_time == t) {
				temp = heap1_pop();
				res += (long long)temp.cart_id * done++;
				heap2_insert(temp);
			}
		}
		
		while (input_count < N &&  heap2_size != 0) {
			input_count++;
			cin >> id >> w;
			temp = heap2_pop();
			temp.cart_id = id;
			temp.remain_time = w + _time;
			heap1_insert(temp);
		}
	}
	cout << res << endl;
}
