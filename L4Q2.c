#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// -------------------------------- GRAFO --------------------------------

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int nVertices;
    Aresta **adj;
} Grafo;

// Cria grafo com n vértices
Grafo* criarGrafo(int n) {
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->nVertices = n;
    g->adj = (Aresta**) malloc(n * sizeof(Aresta*));

    for (int i = 0; i < n; i++)
        g->adj[i] = NULL;

    return g;
}

// Adiciona aresta não direcionada
void adicionarAresta(Grafo *g, int u, int v, int peso) {
    Aresta *a = (Aresta*) malloc(sizeof(Aresta));
    a->destino = v;
    a->peso = peso;
    a->prox = g->adj[u];
    g->adj[u] = a;

    // grafo não direcionado → adiciona outra direção
    a = (Aresta*) malloc(sizeof(Aresta));
    a->destino = u;
    a->peso = peso;
    a->prox = g->adj[v];
    g->adj[v] = a;
}

// ----------------------------- PRIM -------------------------------------

int extrairMin(int chave[], int visitado[], int n) {
    int minValor = INT_MAX;
    int minIndice = -1;

    for (int i = 0; i < n; i++) {
        if (!visitado[i] && chave[i] < minValor) {
            minValor = chave[i];
            minIndice = i;
        }
    }
    return minIndice;
}

void prim(Grafo *g, int origem) {
    int n = g->nVertices;

    int chave[n];     // menor peso para alcançar o vértice
    int pai[n];       // árvore
    int visitado[n];  // marcação

    for (int i = 0; i < n; i++) {
        chave[i] = INT_MAX;
        pai[i] = -1;
        visitado[i] = 0;
    }

    chave[origem] = 0;

    for (int c = 0; c < n - 1; c++) {

        int u = extrairMin(chave, visitado, n);
        visitado[u] = 1;

        Aresta *atual = g->adj[u];

        while (atual != NULL) {
            int v = atual->destino;
            int peso = atual->peso;

            if (!visitado[v] && peso < chave[v]) {
                pai[v] = u;
                chave[v] = peso;
            }

            atual = atual->prox;
        }
    }

    // Exibe resultados
    int custoTotal = 0;
    printf("Arestas da AGM (Prim):\n");

    for (int i = 0; i < n; i++) {
        if (pai[i] != -1) {
            printf("%d - %d (peso %d)\n", pai[i], i, chave[i]);
            custoTotal += chave[i];
        }
    }

    printf("Custo total = %d\n", custoTotal);
}

// -------------------------------- MAIN EXEMPLO -----------------------------

int main() {
    int n = 5;
    Grafo *g = criarGrafo(n);

    adicionarAresta(g, 0, 1, 2);
    adicionarAresta(g, 0, 3, 6);
    adicionarAresta(g, 1, 2, 3);
    adicionarAresta(g, 1, 3, 8);
    adicionarAresta(g, 1, 4, 5);
    adicionarAresta(g, 2, 4, 7);
    adicionarAresta(g, 3, 4, 9);

    prim(g, 0);

    return 0;
}
