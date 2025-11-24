// Resgate em Queda Livre
// Complexidade: O(n²) por caso de teste
//
// EXPLICAÇÃO:
// Este problema é uma aplicação clássica de Árvore Geradora Mínima (MST).
// O objetivo é conectar todas as pessoas usando o mínimo de teia possível.
//
// Usamos o algoritmo de Prim:
// 1. Começamos com uma pessoa na árvore (a primeira)
// 2. Repetidamente, adicionamos a pessoa mais próxima que ainda não está conectada
// 3. Para cada pessoa adicionada, atualizamos as distâncias mínimas das outras
// 4. O loop externo roda n vezes, e o interno também n vezes = O(n²)
//
// A escolha do Prim (em vez de Kruskal) é eficiente aqui porque o grafo é denso
// (todas as pessoas podem se conectar com todas), então temos O(n²) arestas.
// Com Kruskal precisaríamos ordenar O(n²) arestas = O(n² log n), que é pior.
//
// As coordenadas são em centímetros, então dividimos por 100 para obter metros.

#include <stdio.h>
#include <math.h>
#include <float.h>

int main() {
    int C;
    scanf("%d", &C);

    while (C--) {
        int n;
        scanf("%d", &n);

        int x[500], y[500];
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
        }

        double minDist[500];
        bool inMST[500];

        for (int i = 0; i < n; i++) {
            minDist[i] = DBL_MAX;
            inMST[i] = false;
        }

        minDist[0] = 0;
        double totalWeight = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            double minVal = DBL_MAX;
            for (int i = 0; i < n; i++) {
                if (!inMST[i] && minDist[i] < minVal) {
                    minVal = minDist[i];
                    u = i;
                }
            }

            inMST[u] = true;
            totalWeight += minDist[u];

            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    double dx = x[u] - x[v];
                    double dy = y[u] - y[v];
                    double dist = sqrt(dx * dx + dy * dy);
                    if (dist < minDist[v]) {
                        minDist[v] = dist;
                    }
                }
            }
        }

        printf("%.2f\n", totalWeight / 100.0);
    }

    return 0;
}