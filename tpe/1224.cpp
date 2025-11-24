// Jogo de Cartas (Game Theory - Minimax)
// Complexidade: O(n²) por caso de teste
//
// EXPLICAÇÃO:
// Este é um problema de teoria dos jogos onde dois jogadores (Alberto e Wanderley)
// jogam de forma ótima, alternando turnos. Alberto começa e quer maximizar seu score.
//
// Usamos DP de intervalo com a técnica Minimax:
// - dp[i] representa a vantagem (diferença de pontos) do jogador atual no intervalo [i, j]
// - Em cada turno, o jogador pode pegar a carta da esquerda ou da direita
// - Se pegar a esquerda: ganho = cards[i] - dp[i+1] (pega a carta e o oponente joga no resto)
// - Se pegar a direita: ganho = cards[j] - dp[i] (similar)
// - O jogador escolhe a opção que maximiza sua vantagem
//
// A subtração (-dp) representa que depois da jogada, é a vez do oponente,
// então a vantagem dele vira desvantagem nossa (zero-sum game).
//
// Otimização de espaço: em vez de dp[i][j], usamos apenas dp[i] e atualizamos
// in-place, processando por tamanho de intervalo crescente.
//
// No final:
// - diff = dp[0] = vantagem de Alberto sobre Wanderley
// - alberto = (total + diff) / 2

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<long long> cards(n);
        for (int i = 0; i < n; ++i) {
            cin >> cards[i];
        }

        vector<long long> dp(n);
        for (int i = 0; i < n; ++i) {
            dp[i] = cards[i];
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                long long take_left = cards[i] - dp[i + 1];
                long long take_right = cards[j] - dp[i];
                dp[i] = max(take_left, take_right);
            }
        }

        long long total = 0;
        for (long long value : cards) {
            total += value;
        }

        long long diff = dp[0];
        long long alberto = (total + diff) / 2;
        cout << alberto << '\n';
    }

    return 0;
}
