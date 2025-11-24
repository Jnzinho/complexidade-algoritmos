// Lanchonete
// Complexidade: O(N * V) por caso de teste
//
// EXPLICAÇÃO:
// Este é o problema clássico de Soma de Subconjuntos (Subset Sum).
// Precisamos verificar se existe um subconjunto de moedas cuja soma é exatamente V.
//
// Usamos Programação Dinâmica:
// - dp[i] = true se é possível formar a soma i com algum subconjunto de moedas
// - Inicialmente, dp[0] = true (soma 0 sem usar moedas)
// - Para cada moeda de valor c, atualizamos dp[j] = dp[j] || dp[j-c]
// - Percorremos de trás para frente para não usar a mesma moeda duas vezes
//   (cada moeda só pode ser usada uma vez, diferente do problema do troco)
//
// Resposta: dp[V] indica se é possível pagar exatamente o valor do lanche

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
