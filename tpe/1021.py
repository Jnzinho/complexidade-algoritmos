# Notas e Moedas
# Complexidade: O(1) - tempo constante
#
# EXPLICAÇÃO:
# Este é um problema clássico de algoritmo guloso (greedy).
# O objetivo é decompor um valor monetário no menor número de notas e moedas.
#
# A estratégia gulosa funciona aqui porque o sistema monetário brasileiro é "canônico":
# cada denominação é pelo menos o dobro da anterior, garantindo que escolher
# a maior denominação possível sempre leva à solução ótima.
#
# Algoritmo:
# 1. Convertemos o valor para centavos (evita erros de ponto flutuante)
# 2. Para cada denominação (da maior para menor):
#    - Calculamos quantas cabem no valor restante (divisão inteira)
#    - Subtraímos do valor (resto da divisão)
# 3. O número de operações é fixo (6 notas + 6 moedas = 12 iterações)
#
# Por que converter para centavos?
# Operações com float podem gerar erros como 0.1 + 0.2 = 0.30000000000000004
# Trabalhando com inteiros, evitamos esses problemas de precisão.

valor = float(input())

# Evitar erros de precisão com ponto flutuante
valor_centavos = int(round(valor * 100))

notas = [10000, 5000, 2000, 1000, 500, 200]
moedas = [100, 50, 25, 10, 5, 1]

print("NOTAS:")
for nota in notas:
    quantidade = valor_centavos // nota
    print(f"{quantidade} nota(s) de R$ {nota/100:.2f}")
    valor_centavos %= nota

print("MOEDAS:")
for moeda in moedas:
    quantidade = valor_centavos // moeda
    print(f"{quantidade} moeda(s) de R$ {moeda/100:.2f}")
    valor_centavos %= moeda
