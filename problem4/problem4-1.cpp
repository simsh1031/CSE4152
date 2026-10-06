#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long double> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    const long double PI = acosl(-1);
    const long double TWO_PI = 2 * PI;

    vector<pair<long double, long double>> possible = {{0, TWO_PI}};

    for (int i = 0; i < N && !possible.empty(); ++i) {
        const long double angle = atan2l(Y[i], X[i]);
        vector<pair<long double, long double>> next;

        for (const auto& interval : possible) {
            for (int shift = -1; shift <= 1; ++shift) {
                const long double center = angle + shift * TWO_PI;
                const long double left = max(interval.first, center - PI / 2);
                const long double right = min(interval.second, center + PI / 2);

                if (left <= right) {
                    next.emplace_back(left, right);
                }
            }
        }

        possible.swap(next);
    }

    cout << (possible.empty() ? "No" : "Yes") << '\n';

    return 0;
}
