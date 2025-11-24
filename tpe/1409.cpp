#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int M, N, G, K;
    while (cin >> M >> N >> G >> K && (M || N || G || K)) {
        vector<pair<int, int>> spells(M);
        for (int i = 0; i < M; i++) {
            cin >> spells[i].first >> spells[i].second; // custo de mana, dano
        }
        
        // DP: minMana[d] = custo de mana minimo para causar pelo menos d dano
        const int MAX_HP = 1001;
        const long long INF = 1e18;
        vector<long long> minMana(MAX_HP, INF);
        minMana[0] = 0;
        
        for (int d = 1; d < MAX_HP; d++) {
            for (size_t i = 0; i < spells.size(); i++) {
                int cost = spells[i].first;
                int damage = spells[i].second;
                int prev = max(0, d - damage);
                if (minMana[prev] + cost < minMana[d]) {
                    minMana[d] = minMana[prev] + cost;
                }
            }
        }
        
        // Construir lista de adjacência
        vector<vector<int>> adj(N + 1);
        for (int i = 0; i < G; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        
        // Computar custo para limpar cada sala (soma de mana para matar todos os monstros)
        vector<long long> roomCost(N + 1, 0);
        for (int i = 0; i < K; i++) {
            int room, hp;
            cin >> room >> hp;
            roomCost[room] += minMana[hp];
        }
        
        // Dijkstra da sala 1 para a sala N
        vector<long long> dist(N + 1, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        
        dist[1] = roomCost[1];
        pq.push(make_pair(dist[1], 1));
        
        while (!pq.empty()) {
            pair<long long, int> top = pq.top();
            pq.pop();
            
            long long d = top.first;
            int u = top.second;
            if (d > dist[u]) continue;
            
            for (int v : adj[u]) {
                long long newDist = dist[u] + roomCost[v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push(make_pair(newDist, v));
                }
            }
        }
        
        if (dist[N] >= INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[N] << "\n";
        }
    }
    
    return 0;
}
