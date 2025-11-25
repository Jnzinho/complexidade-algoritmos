// Empresa de Telecom
// Complexidade: O(N³ + C) por caso de teste

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

