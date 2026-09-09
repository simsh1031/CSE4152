#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 백트래킹(DFS) 함수: 현재 제한된 깊이(target_depth) 내에서 n에 도달할 수 있는지 검사
bool dfs(vector<int>& chain, int target_depth, int n) {
    int current_val = chain.back();
    int current_depth = chain.size() - 1;

    // 목표 깊이에 도달했을 때 마지막 값이 n이면 성공
    if (current_depth == target_depth) {
        return current_val == n;
    }

    // [Pruning 1] Under-growth: 남은 단계 동안 매번 2배(제곱)를 해도 n에 도달 못 하면 가지치기
    long long max_possible = (long long)current_val << (target_depth - current_depth);
    if (max_possible < n) {
        return false;
    }

    // [Pruning 2] Star Chain & Large-to-Small Order
    // 가장 최근에 만들어진 지수(chain.back())를 반드시 활용하면서,
    // 큰 값부터 조합하여 빠르게 지수를 불려나감 (i: current_depth down to 0)
    int last_idx = current_depth;
    for (int i = last_idx; i >= 0; --i) {
        int next_val = current_val + chain[i];

        // [Pruning 3] Over-growth: 현재 지수보다 작거나 같거나, n을 초과하면 배제
        if (next_val > current_val && next_val <= n) {
            chain.push_back(next_val);
            if (dfs(chain, target_depth, n)) {
                return true; // 성공 시 즉시 리턴
            }
            chain.pop_back(); // Backtracking
        }
    }

    return false;
}

// IDDFS 메인 함수: 최단 깊이부터 1씩 늘려가며 탐색
vector<int> findShortestAdditionChain(int n) {
    if (n == 1) return {1};

    // 하한선 L = ceil(log2(n)) 부터 탐색 시작
    int lower_bound = ceil(log2(n));

    for (int target_depth = lower_bound; ; ++target_depth) {
        vector<int> chain = {1};
        if (dfs(chain, target_depth, n)) {
            return chain; // 가장 먼저 발견된 체인이 '최소 곱셈 횟수'임이 보장됨
        }
    }
}

// 도출된 체인을 계산기용 코드로 출력하는 함수
void printGeneratedCode(const vector<int>& chain) {
    cout << "========================================" << endl;
    cout << " [Generated Calculator Code]" << endl;
    cout << "========================================" << endl;
    cout << "x1 := a;" << endl;

    for (size_t k = 1; k < chain.size(); ++k) {
        int target = chain[k];
        int src1 = -1, src2 = -1;

        // target = chain[i] + chain[j] 가 되는 이전 지수 인덱스 탐색
        for (int i = k - 1; i >= 0; --i) {
            for (int j = i; j >= 0; --j) {
                if (chain[i] + chain[j] == target) {
                    src1 = i + 1; // 1-based index (x1, x2, ...)
                    src2 = j + 1;
                    break;
                }
            }
            if (src1 != -1) break;
        }

        cout << "x" << (k + 1) << " := x" << src1 << " * x" << src2 
             << "; // a^" << target << endl;
    }
    cout << "b := x" << chain.size() << ";" << endl;
    cout << "========================================" << endl;
    cout << "Minimum Multiplications: " << chain.size() - 1 << endl;
}

int main() {
    int n;
    cout << "Enter exponent (n): ";
    if (!(cin >> n) || n < 1) return 0;

    vector<int> chain = findShortestAdditionChain(n);
    printGeneratedCode(chain);

    return 0;
}