#include <bits/stdc++.h>
#include "test.h"
using namespace std;

#ifdef LOCAL // -DLOCAL
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif
#define printvec(v) for (auto& x: v) cout << (x) << ", "; cout << endl;
#define printheap(h) while (!h.empty()) {cout << (h.top()) << ", "; h.pop();} cout << endl;

template<typename T>
using maxheap = std::priority_queue<T>;
template<typename T>
using minheap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

const int MOD = 1e9 + 7;

int main(int argc, char * argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    tester::test();
    return 0;
}