#include <stdio.h>
#include <stdlib.h>
typedef struct No {
    int chave;
    struct No* prox;
} No;

typedef struct {
    int chave;
    No* lista;   
    int ocupado; 
} Entrada;

typedef struct {
  int m;
  int ocupados;
  Entrada* tabela;
} TabelaHash;

int hash(int k, int m) {
    return k % m;
}

void inicializarTabela(TabelaHash* th, int m) {
    th->m = m;
    th->ocupados = 0;
    th->tabela = (Entrada*) malloc(m * sizeof(Entrada));
    for (int i = 0; i < m; i++) {
        th->tabela[i].ocupado = 0;
        th->tabela[i].lista = NULL;
    }
}
int inserirLinear(TabelaHash* th, int k) {
    if (th->ocupados >= th->m)
        return 0; // tabela cheia

    int i = hash(k, th->m);
    int original = i;

    // sondagem linear
    while (th->tabela[i].ocupado) {
        i = (i + 1) % th->m;
        if (i == original) // voltou ao início -> cheia
            return 0;
    }
    th->tabela[i].chave = k;
    th->tabela[i].ocupado = 1;
    th->ocupados++;
    return 1;
}

void inserirEncadeado(TabelaHash* th, int k) {
    int i = hash(k, th->m);
    No* novo = (No*) malloc(sizeof(No));
    novo->chave = k;
    novo->prox = th->tabela[i].lista;
    th->tabela[i].lista = novo;
}

void inserir(TabelaHash* th, int k) {
    if (th->ocupados < th->m) {
        int ok = inserirLinear(th, k);
        if (!ok)
            inserirEncadeado(th, k);
    } else {
        inserirEncadeado(th, k);
    }
}
void imprimirTabela(TabelaHash* th) {
    printf("\n===== CONTEÚDO DA TABELA HASH =====\n");
    for (int i = 0; i < th->m; i++) {
        printf("[%d]: ", i);
        if (th->tabela[i].ocupado)
            printf("%d ", th->tabela[i].chave);
        No* aux = th->tabela[i].lista;
        while (aux != NULL) {
            printf("-> %d ", aux->chave);
            aux = aux->prox;
        }
        printf("\n");
    }
    printf("===================================\n");
}

// Libera memória
void liberarTabela(TabelaHash* th) {
    for (int i = 0; i < th->m; i++) {
        No* aux = th->tabela[i].lista;
        while (aux) {
            No* tmp = aux;
            aux = aux->prox;
            free(tmp);
        }
    }
    free(th->tabela);
}

// Programa principal
int main() {
    TabelaHash th;
    int m, n, valor;

    printf("Digite o tamanho da tabela hash (m): ");
    scanf("%d", &m);
    inicializarTabela(&th, m);

    printf("Quantas chaves deseja inserir? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Chave %d: ", i + 1);
        scanf("%d", &valor);
        inserir(&th, valor);
    }

    imprimirTabela(&th);
    liberarTabela(&th);

    return 0;
}