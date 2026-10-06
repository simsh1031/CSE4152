#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K, S, T;
    cin >> N >> M >> K >> S >> T;

    struct Edge {
        int u, v, w;
    };
    vector<vector<Edge>> edges(K + 1);
    for (int i = 0; i < M; ++i) {
        int U, V, W, C;
        cin >> U >> V >> W >> C;
        edges[C].push_back({U, V, W});
    }

    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(N + 1, INF);
    dist[S] = 0;

    vector<vector<pair<int, int>>> adj(N + 1);
    vector<int> vertices;
    using State = pair<long long, int>;

    for (int c = 1; c <= K; ++c) {
        // Build an undirected graph using only the current color.
        vertices.clear();
        for (const Edge& edge : edges[c]) {
            if (adj[edge.u].empty()) vertices.push_back(edge.u);
            if (adj[edge.v].empty()) vertices.push_back(edge.v);
            adj[edge.u].push_back({edge.v, edge.w});
            adj[edge.v].push_back({edge.u, edge.w});
        }

        // Earlier colors provide the starting distances for this color.
        priority_queue<State, vector<State>, greater<State>> pq;
        for (int v : vertices) {
            if (dist[v] != INF) pq.push({dist[v], v});
        }

        while (!pq.empty()) {
            auto [cost, v] = pq.top();
            pq.pop();
            if (cost != dist[v]) continue;

            for (auto [u, w] : adj[v]) {
                if (cost > INF - w) continue;
                long long nextCost = cost + w;
                if (nextCost < dist[u]) {
                    dist[u] = nextCost;
                    pq.push({nextCost, u});
                }
            }
        }

        // Keep distances, but remove these edges before the next color.
        for (int v : vertices) adj[v].clear();
    }

    cout << (dist[T] == INF ? -1LL : dist[T]) << '\n';

    return 0;
}
