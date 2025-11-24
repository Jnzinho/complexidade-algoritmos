// Navegador Web
// Complexidade: O((N + Q) * L) onde L é o comprimento máximo das strings (100)
//
// EXPLICAÇÃO:
// Este problema pede para implementar um sistema de autocomplete.
// Para cada consulta (prefixo), precisamos contar quantas palavras têm esse prefixo
// e encontrar o comprimento da maior delas.
//
// Usamos uma Trie (árvore de prefixos):
// - Cada nó armazena: count (palavras com este prefixo) e maxLen (maior comprimento)
// - Inserção: percorremos a palavra caractere a caractere, incrementando count
//   e atualizando maxLen em cada nó visitado
// - Consulta: navegamos até o nó correspondente ao prefixo e retornamos count e maxLen
//
// Complexidade:
// - Construção da Trie: O(N * L)
// - Consultas: O(Q * L)

#include <cstdio>
#include <cstring>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    int count;
    int maxLen;

    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = 0;
        count = 0;
        maxLen = 0;
    }
};

TrieNode* root;

void insert(const char* word) {
    int len = strlen(word);
    TrieNode* node = root;
    for (int i = 0; i < len; i++) {
        int idx = word[i] - 'a';
        if (!node->children[idx]) {
            node->children[idx] = new TrieNode();
        }
        node = node->children[idx];
        node->count++;
        if (len > node->maxLen) node->maxLen = len;
    }
}

void query(const char* prefix, int& cnt, int& mxLen) {
    int len = strlen(prefix);
    TrieNode* node = root;
    for (int i = 0; i < len; i++) {
        int idx = prefix[i] - 'a';
        if (!node->children[idx]) {
            cnt = -1;
            return;
        }
        node = node->children[idx];
    }
    cnt = node->count;
    mxLen = node->maxLen;
}

void clear(TrieNode* node) {
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            clear(node->children[i]);
        }
    }
    delete node;
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        root = new TrieNode();
        char word[105];

        for (int i = 0; i < n; i++) {
            scanf("%s", word);
            insert(word);
        }

        int q;
        scanf("%d", &q);

        for (int i = 0; i < q; i++) {
            scanf("%s", word);
            int cnt, mxLen;
            query(word, cnt, mxLen);
            if (cnt == -1) {
                printf("-1\n");
            } else {
                printf("%d %d\n", cnt, mxLen);
            }
        }

        clear(root);
    }

    return 0;
}

