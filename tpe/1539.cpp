// Empresa de Telecom
// Complexidade: O(N³ + C) por caso de teste
//
// EXPLICAÇÃO:
// Este é um problema de caminho mínimo em um grafo direcionado ponderado.
// Cada antena é um nó, e existe uma aresta direcionada de i para j se a
// distância entre elas é menor ou igual ao raio de alcance da antena i.
// O peso da aresta é a distância Euclidiana entre as antenas.
//
// Importante: o grafo é DIRECIONADO! A antena A pode alcançar B (se dist ≤ R_A),
// mas B pode não alcançar A (se dist > R_B).
//
// Usamos Floyd-Warshall para calcular todos os caminhos mínimos:
// - Inicializamos dist[i][j] com a distância se houver conexão direta, INF caso contrário
// - Para cada nó intermediário k, atualizamos dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
//
// A saída deve ser TRUNCADA (não arredondada) para inteiro.
// Se não houver caminho, imprimimos -1.

#include <cstdio>
#include <cmath>
using namespace std;

const double INF = 1e18;
double dist[105][105];
int x[105], y[105], r[105];

double euclidean(int i, int j) {
    double dx = x[i] - x[j];
    double dy = y[i] - y[j];
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        for (int i = 1; i <= n; i++) {
            scanf("%d %d %d", &x[i], &y[i], &r[i]);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                } else {
                    double d = euclidean(i, j);
                    if (d <= r[i]) {
                        dist[i][j] = d;
                    } else {
                        dist[i][j] = INF;
                    }
                }
            }
        }

        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        int c;
        scanf("%d", &c);
        while (c--) {
            int a1, a2;
            scanf("%d %d", &a1, &a2);
            if (dist[a1][a2] >= INF) {
                printf("-1\n");
            } else {
                printf("%d\n", (int)dist[a1][a2]);
            }
        }
    }

    return 0;
}

