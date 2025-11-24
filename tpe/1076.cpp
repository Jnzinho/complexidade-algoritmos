// Desenhando Labirintos
// Complexidade: O(V² + 2^k * k) onde k é o número de vértices de grau ímpar
//
// EXPLICAÇÃO:
// Este é o Problema do Carteiro Chinês (Chinese Postman Problem).
// Queremos percorrer todas as arestas pelo menos uma vez, retornando ao início.
//
// Se todos os vértices têm grau par, existe um circuito Euleriano e a resposta
// é simplesmente o número de arestas.
//
// Se existem vértices de grau ímpar (sempre em número par), precisamos
// "duplicar" algumas arestas para tornar todos os graus pares.
// O custo mínimo é encontrado fazendo um emparelhamento perfeito de peso mínimo
// entre os vértices de grau ímpar, usando as distâncias mais curtas entre eles.
//
// Usamos BFS para calcular distâncias e DP iterativo com bitmask para o emparelhamento.
//
// Resposta = número de arestas + custo do emparelhamento

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1000000000;
int adj[50][50];
int dist[50][50];
int degree[50];
int V;

void bfs(int src) {
    queue<int> q;
    q.push(src);
    dist[src][src] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < V; v++) {
            if (adj[u][v] && dist[src][v] == INF) {
                dist[src][v] = dist[src][u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, A;
        scanf("%d", &N);
        scanf("%d %d", &V, &A);

        memset(adj, 0, sizeof(adj));
        memset(degree, 0, sizeof(degree));

        int edges = 0;
        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            if (adj[u][v] == 0) {
                edges++;
                adj[u][v] = adj[v][u] = 1;
                degree[u]++;
                degree[v]++;
            }
        }

        vector<int> odd;
        for (int i = 0; i < V; i++) {
            if (degree[i] % 2 == 1) {
                odd.push_back(i);
            }
        }

        int oddCount = odd.size();

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = INF;
            }
        }
        for (int i = 0; i < oddCount; i++) {
            bfs(odd[i]);
        }

        int extra = 0;
        if (oddCount > 0) {
            int fullMask = (1 << oddCount) - 1;
            vector<int> dp(1 << oddCount, INF);
            dp[0] = 0;

            for (int mask = 0; mask < fullMask; mask++) {
                if (dp[mask] == INF) continue;

                int i = 0;
                while (mask & (1 << i)) i++;

                for (int j = i + 1; j < oddCount; j++) {
                    if (!(mask & (1 << j))) {
                        int newMask = mask | (1 << i) | (1 << j);
                        int cost = dist[odd[i]][odd[j]];
                        if (cost < INF && dp[mask] + cost < dp[newMask]) {
                            dp[newMask] = dp[mask] + cost;
                        }
                    }
                }
            }
            extra = dp[fullMask];
        }

        printf("%d\n", edges + extra);
    }

    return 0;
}
