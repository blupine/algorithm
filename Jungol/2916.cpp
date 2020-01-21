#include <iostream>
#include <set>
#define MAXNODE 100001
 
using namespace std;
 
int Parents[MAXNODE][2];
int Visited[MAXNODE];
int N, K, a, b, c, r;
int lca_seq;
 
int LCA(int A, int B) {
    // A와 B의 최소 공통 부모를 찾아서 반환
    lca_seq++;
    if (A == B) return A;
 
    for (int i = 0; i < 1000; i++) {
        if (A >= 0) {
            if(Visited[A] == lca_seq)
                return A;
            Visited[A] = lca_seq;
            A = Parents[A][0];
        }
        if (B >= 0) {
            if (Visited[B] == lca_seq)
                return B;
            Visited[B] = lca_seq;
            B = Parents[B][0];
        }
    }
    return -1; // error
}
 
void paint(int A, int B, int C) {
    int lca = LCA(A, B);
    register int n1 = A, n2 = B;
    while (n1 != lca) {
        Parents[n1][1] = C;
        n1 = Parents[n1][0];
    }
    while (n2 != lca) {
        Parents[n2][1] = C;
        n2 = Parents[n2][0];
    }
    return;
}
 
int count(int A, int B) {
    int lca = LCA(A, B);
    register int n1 = A, n2 = B;
    set<int> s;
    while (n1 != lca) {
        s.insert(Parents[n1][1]);
        n1 = Parents[n1][0];
    }
    while (n2 != lca) {
        s.insert(Parents[n2][1]);
        n2 = Parents[n2][0];
    }
    return s.size();
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
     
    int lca = 0;
    Parents[0][0] = -1;
    for (register int i = 1; i <= K; i++) {
        cin >> r;
        if (r == 1) {
            cin >> a >> b >> c;
            paint(a, b, c);
        }
        else if (r == 2) {
            cin >> a >> b;
            // move
            Parents[a][0] = b;
        }
        else {
            cin >> a >> b;
            cout << count(a, b) << "\n";
        }
    }
 
}
