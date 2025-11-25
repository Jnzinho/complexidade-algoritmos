// Lanchonete
// Complexidade: O(N * V) por caso de teste

#include <cstdio>
#include <cstring>
using namespace std;

bool dp[100005];

int main() {
    int V, N;
    while (scanf("%d %d", &V, &N) && (V || N)) {
        memset(dp, false, sizeof(dp));
        dp[0] = true;

        for (int i = 0; i < N; i++) {
            int c;
            scanf("%d", &c);
            for (int j = V; j >= c; j--) {
                if (dp[j - c]) {
                    dp[j] = true;
                }
            }
        }

        printf("%s\n", dp[V] ? "sim" : "nao");
    }

    return 0;
}
