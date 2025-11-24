// Resgate em Queda Livre

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