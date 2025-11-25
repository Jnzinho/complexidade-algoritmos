# Explicações dos Exercícios - TPE

## 1076 - Desenhando Labirintos

**Complexidade:** O(V² + 2^k · k), onde k é o número de vértices de grau ímpar

### Explicação

Este é o **Problema do Carteiro Chinês** (Chinese Postman Problem). Queremos percorrer todas as arestas pelo menos uma vez, retornando ao início.

- Se todos os vértices têm grau par, existe um **circuito Euleriano** e a resposta é simplesmente o número de arestas.

- Se existem vértices de grau ímpar (sempre em número par), precisamos "duplicar" algumas arestas para tornar todos os graus pares. O custo mínimo é encontrado fazendo um **emparelhamento perfeito de peso mínimo** entre os vértices de grau ímpar, usando as distâncias mais curtas entre eles.

**Algoritmo:**

- Usamos **BFS** para calcular distâncias entre vértices de grau ímpar
- Usamos **DP iterativo com bitmask** para o emparelhamento

**Resposta** = número de arestas + custo do emparelhamento

---

## 1203 - Pontes de São Petersburgo

**Complexidade:** O(R · K)

### Explicação

Este problema é uma variação do problema das **Pontes de Königsberg**. Queremos saber se é possível selecionar um subconjunto de regiões tal que o número total de pontes incidentes seja exatamente K.

Usamos **Programação Dinâmica** com memoização:

- `DP(regiao, pontes)` = é possível, a partir da 'regiao', atingir exatamente K pontes?
- Para cada região, temos duas escolhas:
  1. **NÃO incluir** a região: `DP(regiao + 1, pontes)`
  2. **Incluir** a região: `DP(regiao + 1, pontes + graus[regiao])`
- Caso base: se `pontes == K`, retorna verdadeiro; se `pontes > K`, retorna falso

A memoização evita recalcular estados já visitados.

---

## 1224 - Cartões

**Complexidade:** O(n²)

### Explicação

Este é um problema de **teoria dos jogos** onde dois jogadores (Alberto e Wanderley) jogam de forma ótima, alternando turnos. Alberto começa e quer maximizar seu score.

Usamos **DP de intervalo** com a técnica **Minimax**:

- `dp[i]` representa a vantagem (diferença de pontos) do jogador atual no intervalo [i, j]
- Em cada turno, o jogador pode pegar a carta da esquerda ou da direita
- Se pegar a esquerda: `ganho = cards[i] - dp[i+1]` (pega a carta e o oponente joga no resto)
- Se pegar a direita: `ganho = cards[j] - dp[i]` (similar)
- O jogador escolhe a opção que maximiza sua vantagem

A subtração (`-dp`) representa que depois da jogada, é a vez do oponente, então a vantagem dele vira desvantagem nossa (**zero-sum game**).

**Otimização de espaço:** em vez de `dp[i][j]`, usamos apenas `dp[i]` e atualizamos in-place, processando por tamanho de intervalo crescente.

No final:

- `diff = dp[0]` = vantagem de Alberto sobre Wanderley
- `alberto = (total + diff) / 2`

---

## 1409 - Zak Galou

**Complexidade:** O(M · HP + (N + G) · log N)

### Explicação

Este problema combina duas técnicas: **Programação Dinâmica** e **Dijkstra**.

**PARTE 1 - DP para calcular custo mínimo de mana para matar monstros:**

- `minMana[d]` = custo mínimo de mana para causar exatamente d de dano
- Para cada dano d, testamos todas as M magias disponíveis
- Se uma magia causa 'damage' de dano com custo 'cost', então:
  `minMana[d] = min(minMana[d], minMana[d - damage] + cost)`
- Isso é similar ao problema da **mochila ilimitada** (cada magia pode ser usada várias vezes)

**PARTE 2 - Dijkstra para encontrar caminho de menor custo:**

- Cada sala tem um custo = soma das manas para matar todos os monstros nela
- Usamos **Dijkstra** para encontrar o caminho da sala 1 até a sala N
- O custo de entrar em uma sala é o custo de limpar ela

---

## 1539 - Empresa de Telecom

**Complexidade:** O(N³ + C)

### Explicação

Este é um problema de **caminho mínimo** em um grafo **direcionado** ponderado. Cada antena é um nó, e existe uma aresta direcionada de i para j se a distância entre elas é menor ou igual ao raio de alcance da antena i. O peso da aresta é a **distância Euclidiana** entre as antenas.

**Importante:** o grafo é **DIRECIONADO**! A antena A pode alcançar B (se dist ≤ R_A), mas B pode não alcançar A (se dist > R_B).

Usamos **Floyd-Warshall** para calcular todos os caminhos mínimos:

- Inicializamos `dist[i][j]` com a distância se houver conexão direta, INF caso contrário
- Para cada nó intermediário k, atualizamos: `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

A saída deve ser **TRUNCADA** (não arredondada) para inteiro. Se não houver caminho, imprimimos -1.

---

## 1552 - Resgate em Queda Livre

**Complexidade:** O(n²)

### Explicação

Este problema é uma aplicação clássica de **Árvore Geradora Mínima (MST)**. O objetivo é conectar todas as pessoas usando o mínimo de teia possível.

Usamos o **algoritmo de Prim**:

1. Começamos com uma pessoa na árvore (a primeira)
2. Repetidamente, adicionamos a pessoa mais próxima que ainda não está conectada
3. Para cada pessoa adicionada, atualizamos as distâncias mínimas das outras

A escolha do **Prim** (em vez de Kruskal) é eficiente aqui porque o grafo é **denso** (todas as pessoas podem se conectar com todas), então temos O(n²) arestas. Com Kruskal precisaríamos ordenar O(n²) arestas = O(n² log n), que é pior.

As coordenadas são em centímetros, então dividimos por 100 para obter metros.

---

## 1764 - Itinerário do Papai Noel

**Complexidade:** O(N log N)

### Explicação

Este problema é uma aplicação clássica de **Árvore Geradora Mínima (MST)**. O Papai Noel precisa criar um mapa conectando todas as cidades com a menor soma total de rotas possível, permitindo chegar em qualquer cidade.

Usamos o **algoritmo de Kruskal** com **Union-Find (DSU)**:

1. Ordenamos todas as arestas (rotas) por peso (distância) crescente
2. Para cada aresta, verificamos se ela conecta dois componentes diferentes
3. Se conectar, adicionamos ao MST e unimos os componentes
4. Paramos quando tivermos M-1 arestas (árvore completa)

**Union-Find** com compressão de caminho e união por rank garante operações quase O(1) (amortizado). A ordenação domina: O(N log N).

A escolha do **Kruskal** é adequada aqui pois o grafo pode ser **esparso**.

---

## 1931 - Mania de Par

**Complexidade:** O((V + E) · log V)

### Explicação

Patrícia precisa ir da cidade 1 à cidade C pagando um número **PAR** de pedágios. Este é um problema de **caminho mínimo com restrição de paridade**.

Usamos **Dijkstra com estados expandidos**:

- **Estado:** `(cidade, paridade)` onde paridade é 0 (par) ou 1 (ímpar)
- `dist[cidade][paridade]` = custo mínimo para chegar com essa paridade de arestas

**Transições:**

- Cada aresta muda a paridade: de `(u, p)` para `(v, 1-p)` com custo w
- Começamos em `dist[1][0] = 0` (cidade 1 com 0 pedágios = par)

**Resposta:** `dist[C][0]` (chegar em C com número par de pedágios). Se não for possível, retornamos -1.

---

## 1952 - O Cavalo no Xadrez 3D

**Complexidade:** O(N · M · L)

### Explicação

Este é um problema de **caminho mínimo** em um espaço **3D**. O cavalo pode pular de (i1, j1, k1) para (i2, j2, k2) se `{|di|, |dj|, |dk|} = {0, 1, 2}`. Isso significa que uma coordenada muda 0, uma muda 1, e uma muda 2.

Usamos **BFS** (busca em largura) pois todas as arestas têm peso 1:

- Geramos os **24 movimentos válidos** (permutações de {0, 1, 2} com sinais)
- BFS a partir da posição inicial até encontrar a posição final

Cada posição é visitada no máximo uma vez.

---

## 2089 - Lanchonete

**Complexidade:** O(N · V)

### Explicação

Este é o problema clássico de **Soma de Subconjuntos (Subset Sum)**. Precisamos verificar se existe um subconjunto de moedas cuja soma é exatamente V.

Usamos **Programação Dinâmica**:

- `dp[i]` = true se é possível formar a soma i com algum subconjunto de moedas
- Inicialmente, `dp[0] = true` (soma 0 sem usar moedas)
- Para cada moeda de valor c, atualizamos `dp[j] = dp[j] || dp[j-c]`
- **Percorremos de trás para frente** para não usar a mesma moeda duas vezes (cada moeda só pode ser usada uma vez, diferente do problema do troco)

**Resposta:** `dp[V]` indica se é possível pagar exatamente o valor do lanche.

---

## 2635 - Navegador Web

**Complexidade:** O((N + Q) · L), onde L é o comprimento máximo das strings

### Explicação

Este problema pede para implementar um sistema de **autocomplete**. Para cada consulta (prefixo), precisamos contar quantas palavras têm esse prefixo e encontrar o comprimento da maior delas.

Usamos uma **Trie** (árvore de prefixos):

- Cada nó armazena: `count` (palavras com este prefixo) e `maxLen` (maior comprimento)
- **Inserção:** percorremos a palavra caractere a caractere, incrementando count e atualizando maxLen em cada nó visitado
- **Consulta:** navegamos até o nó correspondente ao prefixo e retornamos count e maxLen

**Complexidade:**

- Construção da Trie: O(N · L)
- Consultas: O(Q · L)
