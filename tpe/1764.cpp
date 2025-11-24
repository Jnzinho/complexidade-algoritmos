// Itinerário do Papai Noel
// Complexidade: O(N log N)
//
// EXPLICAÇÃO:
// Este problema é uma aplicação clássica de Árvore Geradora Mínima (MST).
// O Papai Noel precisa criar um mapa conectando todas as cidades com a menor
// soma total de rotas possível, permitindo chegar em qualquer cidade.
//
// Usamos o algoritmo de Kruskal com Union-Find (DSU):
// 1. Ordenamos todas as arestas (rotas) por peso (distância) crescente
// 2. Para cada aresta, verificamos se ela conecta dois componentes diferentes
// 3. Se conectar, adicionamos ao MST e unimos os componentes
// 4. Paramos quando tivermos M-1 arestas (árvore completa)
//
// Union-Find com compressão de caminho e união por rank garante operações
// quase O(1) (amortizado). A ordenação domina: O(N log N).
//
// A escolha do Kruskal é adequada aqui pois o grafo pode ser esparso
// (N < 50000 arestas para M < 40000 vértices).

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent[40005];
int rnk[40005];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;
    if (rnk[px] < rnk[py]) swap(px, py);
    parent[py] = px;
    if (rnk[px] == rnk[py]) rnk[px]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    while (cin >> m >> n && (m || n)) {
        vector<pair<int, pair<int, int>>> edges(n);

        for (int i = 0; i < m; i++) {
            parent[i] = i;
            rnk[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            edges[i] = {z, {x, y}};
        }

        sort(edges.begin(), edges.end());

        long long total = 0;
        int count = 0;

        for (int i = 0; i < n; i++) {
            int w = edges[i].first;
            int u = edges[i].second.first;
            int v = edges[i].second.second;

            if (find(u) != find(v)) {
                unite(u, v);
                total += w;
                if (++count == m - 1) break;
            }
        }

        cout << total << "\n";
    }

    return 0;
}
