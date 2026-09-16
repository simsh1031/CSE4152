#include <iostream>
#include <vector>
using namespace std;

vector<int> findNLargestElements(const vector<vector<int>>& matrix, int n) {
    vector<int> largestElements;
    // TODO:
    int m = n * n;
    vector<int> values(m);
    vector<bool> active(m, true); // 리프의 사용 여부 체크
    int idx = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            values[idx++] = matrix[i][j];
        }
    }

    // 두 승자를 비교할 때, active 상태를 고려하는 람다 함수
    auto whoisWinner = [&](int leftIdx, int rightIdx) {
        if (!active[leftIdx]) return rightIdx;
        if (!active[rightIdx]) return leftIdx;
        return (values[leftIdx] >= values[rightIdx]) ? leftIdx : rightIdx;
    };

    vector<int> tree(2 * m);
    for (int i = 0; i < m; ++i) {
        tree[m + i] = i;
    }

    for (int i = m - 1; i >= 1; --i) {
        tree[i] = whoisWinner(tree[2 * i], tree[2 * i + 1]);
    }

    for (int k = 0; k < n; ++k) {
        int winnerIdx = tree[1];
        largestElements.push_back(values[winnerIdx]);

        // 사용한 원소 비활성화 (LLONG_MIN 대체)
        active[winnerIdx] = false;

        // 경로 재갱신
        int pos = (m + winnerIdx) / 2;
        while (pos >= 1) {
            tree[pos] = whoisWinner(tree[2 * pos], tree[2 * pos + 1]);
            pos /= 2;
        }
    }

    return largestElements;
}

int main() {
    // Do NOT delete these lines unless you know what you are doing:
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> M(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> M[i][j];
        }
    }

    vector<int> largestElements = findNLargestElements(M, n);

    for (int element : largestElements) {
        cout << element << "\n";
    }

    return 0;
}
