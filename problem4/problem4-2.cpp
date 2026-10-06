#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<vector<pair<int, long long>>> graph(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int U, V;
        long long W;
        cin >> U >> V >> W;
        graph[U].emplace_back(V, W);
        graph[V].emplace_back(U, W);
    }

    if (N == 1) {
        cout << 0 << '\n';
        return 0;
    }

    if (K == 1) {
        auto farthest = [&](int start) {
            vector<long long> distance(N + 1, -1);
            vector<int> order = {start};
            distance[start] = 0;
            int endpoint = start;

            for (int i = 0; i < N; ++i) {
                int v = order[i];
                for (auto [next, weight] : graph[v]) {
                    if (distance[next] != -1) continue;
                    distance[next] = distance[v] + weight;
                    order.push_back(next);
                    if (distance[next] > distance[endpoint]) {
                        endpoint = next;
                    }
                }
            }

            return make_pair(endpoint, distance[endpoint]);
        };

        int A = farthest(1).first;
        cout << farthest(A).second << '\n';
        return 0;
    }

    vector<int> parent(N + 1), order = {1};
    for (int i = 0; i < N; ++i) {
        int v = order[i];
        for (auto [next, weight] : graph[v]) {
            if (next == parent[v]) continue;
            parent[next] = v;
            order.push_back(next);
        }
    }

    vector<long long> down(N + 1), subDiam(N + 1);
    vector<long long> up(N + 1), outDiam(N + 1);

    for (int i = N - 1; i >= 0; --i) {
        int v = order[i];
        long long first = 0, second = 0;

        for (auto [child, weight] : graph[v]) {
            if (child == parent[v]) continue;
            long long distance = weight + down[child];
            if (distance > first) {
                second = first;
                first = distance;
            } else if (distance > second) {
                second = distance;
            }
            subDiam[v] = max(subDiam[v], subDiam[child]);
        }

        down[v] = first;
        subDiam[v] = max(subDiam[v], first + second);
    }

    auto insert = [](auto& best, long long value, int child) {
        pair<long long, int> candidate = {value, child};
        for (auto& entry : best) {
            if (candidate.first > entry.first) {
                swap(candidate, entry);
            }
        }
    };

    long long answer = subDiam[1];

    for (int v : order) {
        array<pair<long long, int>, 3> distances = {};
        array<pair<long long, int>, 2> diameters = {};
        insert(distances, up[v], 0);
        insert(diameters, outDiam[v], 0);

        for (auto [child, weight] : graph[v]) {
            if (child == parent[v]) continue;
            insert(distances, weight + down[child], child);
            insert(diameters, subDiam[child], child);
        }

        for (auto [child, weight] : graph[v]) {
            if (child == parent[v]) continue;
            long long first = 0, second = 0;
            int count = 0;
            for (auto [distance, source] : distances) {
                if (source == child) continue;
                if (count == 0) first = distance;
                else if (count == 1) second = distance;
                ++count;
            }

            up[child] = weight + first;
            outDiam[child] = first + second;
            for (auto [diameter, source] : diameters) {
                if (source != child) {
                    outDiam[child] = max(outDiam[child], diameter);
                }
            }

            answer = min(answer, max(subDiam[child], outDiam[child]));
        }
    }

    cout << answer << '\n';

    return 0;
}
