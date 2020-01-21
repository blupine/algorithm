#include <iostream>
#define MAXCOW 80001
using namespace std;
 
int N;
int cows[MAXCOW][2]; // 두 번째 요소는 해당 소가 볼 수 있는 소들의 개수 (점프뛸 수 있는 소들 개수)
 
int get_cows(int index) {
    // index 번째 소가 볼 수 있는 소들의 개수를 반환
    int nextcow = index + 1;
    int ret = 0;
    while (nextcow < N && cows[index][0] > cows[nextcow][0]) {
        ret += cows[nextcow][1] + 1; // nextcow 포함시켜야되니 + 1
        nextcow += cows[nextcow][1] + 1;
    }
    cows[index][1] = ret;
    return ret;
}
 
int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> cows[i][0];
    }
    long long res = 0;
    for (int i = N - 1; i >= 0; --i) {
        res += get_cows(i);
    }
    cout << res << endl;
     
}
