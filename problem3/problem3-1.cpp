#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> A(N + 2, vector<int>(N + 2, 0));
    vector<vector<int>> diff(N + 2, vector<int>(N + 2, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> A[i][j];
        }
    }

    int Q;
    cin >> Q;
    for (int k = 0; k < Q; ++k) {
        int R1, C1, R2, C2, V;
        cin >> R1 >> C1 >> R2 >> C2 >> V;

        // Record the rectangle's start and end boundaries.
        diff[R1][C1] += V;
        diff[R1][C2 + 1] -= V;
        diff[R2 + 1][C1] -= V;
        diff[R2 + 1][C2 + 1] += V;
    }

    // Accumulate horizontally, then vertically, to recover each change.
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            diff[i][j] += diff[i][j - 1];
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            diff[i][j] += diff[i - 1][j];
            A[i][j] += diff[i][j];
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (j > 1) cout << ' ';
            cout << A[i][j];
        }
        cout << '\n';
    }

    return 0;
}
