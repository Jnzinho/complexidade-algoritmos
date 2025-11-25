// Pontes de São Petersburgo
// Complexidade: O(R * K) por caso de teste
//
// EXPLICAÇÃO:
// Este problema é uma variação do problema das Pontes de Königsberg.
// Queremos saber se é possível selecionar um subconjunto de regiões tal que
// o número total de pontes incidentes seja exatamente K.
//
// Usamos Programação Dinâmica com memoização:
// - DP(regiao, pontes) = é possível, a partir da 'regiao', atingir exatamente K pontes?
// - Para cada região, temos duas escolhas:
//   1. NÃO incluir a região: DP(regiao + 1, pontes)
//   2. Incluir a região: DP(regiao + 1, pontes + graus[regiao])
// - Caso base: se pontes == K, retorna verdadeiro; se pontes > K, retorna falso
//
// Por que a tabela tem dimensão [101][4951]?
// - Temos no máximo 100 regiões
// - Cada ponte conecta 2 regiões, então a soma máxima de graus é 2*K
// - Com K ≤ 2475 (máximo de pontes), a soma máxima é 4950
//
// A memoização evita recalcular estados já visitados, garantindo O(R * K).

#include <iostream>
#include <cstring>

using namespace std;

int R, K;
int graus[101];
int resposta[101][4951];

int DP(int regiao, int pontes){
    if(regiao > R)  return 0;

    if(resposta[regiao][pontes] == -1){
        if(pontes == K){
            resposta[regiao][pontes] = 1;
        }else if(pontes > K){
            resposta[regiao][pontes] = 0;
        }else{
            resposta[regiao][pontes] = DP(regiao + 1, pontes) ||
                                       DP(regiao + 1, pontes + graus[regiao]);
        }
    }

    return resposta[regiao][pontes];
}

int main(){
    int A, B;

    while(cin >> R >> K){
        memset(graus, 0, sizeof(graus));
        memset(resposta, -1, sizeof(resposta));
         
        for(int i = 0; i < K; ++i){
            cin >> A >> B;
            ++graus[A];
            ++graus[B];
        }

        cout << (char) (DP(1, 0) ? 'S' : 'N') << endl;
    }

    return 0;
}