#include<iostream>
#include<vector>
using namespace std;

vector<int> min_multiplications(int n) {
    vector<int> powers;

    //TODO : complete min multiplication

    powers.push_back(1);
    if (n == 1) {
        return powers;
    }

    // 한 번의 곱셈으로 지수는 최대 두 배가 되므로 탐색 깊이의 하한을 구한다.
    int maxDepth = 0;
    for (long long reachable = 1; reachable < n; reachable *= 2) {
        ++maxDepth;
    }

    auto dfs = [&](auto&& self, int depth, int limit) -> bool {
        int current = powers.back();
        if (current == n) {
            return true;
        }
        if (depth == limit) {
            return false;
        }

        // 목표에 도달하면 배가를 멈춰 정수 오버플로를 방지한다.
        long long reachable = current;
        for (int remaining = limit - depth;
             remaining > 0 && reachable < n; --remaining) {
            reachable *= 2;
        }
        if (reachable < n) {
            return false;
        }

        // 마지막 지수뿐 아니라 이전에 만든 모든 지수 쌍을 사용한다.
        int last = static_cast<int>(powers.size()) - 1;
        for (int i = last; i >= 0; --i) {
            for (int j = i; j >= 0; --j) {
                long long next = static_cast<long long>(powers[i]) + powers[j];
                if (next <= current || next > n) {
                    continue;
                }

                powers.push_back(static_cast<int>(next));
                if (self(self, depth + 1, limit)) {
                    return true;
                }
                powers.pop_back();
            }
        }
        return false;
    };

    // 작은 깊이부터 완전 탐색하므로 처음 찾은 수열의 곱셈 횟수가 최소이다.
    while (!dfs(dfs, 0, maxDepth)) {
        ++maxDepth;
    }


    return powers;
}

int main(){

    int n;
    cin >> n;

    
    vector<int> steps = min_multiplications(n);
    cout << steps.size() - 1 << " ";
    for (int step : steps) {
        cout << step << " ";
    }

    return 0;
}