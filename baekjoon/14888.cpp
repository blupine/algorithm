#include <iostream>
#include <deque>
using namespace std;

deque<int> nums;
deque<int> op;
int N, A;

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int _div(int a, int b) { return a / b; }

int (*operation[4])(int, int) = { add, sub, mul, _div };

int _max = -0x7fffffff, _min = 0x7fffffff;

int total_op;

void dfs(int depth, deque<int> ops, int num) {
	if (depth > total_op) {
		if(num < _min) _min = num;
		if (num > _max) _max = num;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (ops[i] != 0) {
			deque<int> next = ops;
			next[i]--;
			dfs(depth + 1, next, operation[i](num, nums[depth]));
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> A;
		nums.push_back(A);
	}
	for (int i = 0; i < 4; i++) {
		cin >> A;
		total_op += A;
		op.push_back(A);
	}

	dfs(1, op, nums[0]);
	cout << _max << "\n" << _min << "\n";
}
