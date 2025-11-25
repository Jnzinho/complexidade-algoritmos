// O Cavalo no Xadrez 3D
// Complexidade: O(N * M * L)

#include <cstdio>
#include <queue>
#include <cstring>
#include <cstdlib>
using namespace std;

int dist[105][105][105];
int moves[24][3];
int numMoves;

int main() {
    numMoves = 0;
    for (int a = -2; a <= 2; a++) {
        for (int b = -2; b <= 2; b++) {
            for (int c = -2; c <= 2; c++) {
                int s0 = abs(a), s1 = abs(b), s2 = abs(c);
                if (s0 > s1) { int t = s0; s0 = s1; s1 = t; }
                if (s1 > s2) { int t = s1; s1 = s2; s2 = t; }
                if (s0 > s1) { int t = s0; s0 = s1; s1 = t; }
                if (s0 == 0 && s1 == 1 && s2 == 2) {
                    moves[numMoves][0] = a;
                    moves[numMoves][1] = b;
                    moves[numMoves][2] = c;
                    numMoves++;
                }
            }
        }
    }

    int N, M, L;
    scanf("%d %d %d", &N, &M, &L);

    int i1, j1, k1, i2, j2, k2;
    scanf("%d %d %d", &i1, &j1, &k1);
    scanf("%d %d %d", &i2, &j2, &k2);

    memset(dist, -1, sizeof(dist));

    queue<int> qi, qj, qk;
    qi.push(i1); qj.push(j1); qk.push(k1);
    dist[i1][j1][k1] = 0;

    while (!qi.empty()) {
        int i = qi.front(); qi.pop();
        int j = qj.front(); qj.pop();
        int k = qk.front(); qk.pop();

        if (i == i2 && j == j2 && k == k2) {
            printf("%d\n", dist[i][j][k]);
            return 0;
        }

        for (int m = 0; m < numMoves; m++) {
            int ni = i + moves[m][0];
            int nj = j + moves[m][1];
            int nk = k + moves[m][2];

            if (ni >= 1 && ni <= N && nj >= 1 && nj <= M && nk >= 1 && nk <= L && dist[ni][nj][nk] == -1) {
                dist[ni][nj][nk] = dist[i][j][k] + 1;
                qi.push(ni); qj.push(nj); qk.push(nk);
            }
        }
    }

    return 0;
}
