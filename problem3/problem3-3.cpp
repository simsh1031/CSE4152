#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long M;
    cin >> N >> M;

    long long S = 0;
    int count = 0;

    while (S < N * M) {
        // Generalize the report's 1-, 2-, and 3-value coin rule.
        // A larger coin would leave some demands totaling S + 1 unpaid.
        long long coin = S / N + 1;
        S += coin;
        ++count;
    }

    cout << count << '\n';

    return 0;
}
