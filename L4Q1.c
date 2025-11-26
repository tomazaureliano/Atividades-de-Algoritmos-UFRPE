#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------- Estrutura do nó da AVL ----------------------
typedef struct No {
    int chave;
    int altura;
    struct No *esquerda;
    struct No *direita;
} No;

// ---------------------- Funções utilitárias ----------------------
int obterAltura(No *no) {
    return no ? no->altura : 0;
}

// Fator de balanceamento = h(dir) - h(esq)
int fatorBalanceamento(No *no) {
    return no ? obterAltura(no->direita) - obterAltura(no->esquerda) : 0;
}

int maior(int a, int b) {
    return a > b ? a : b;
}

No* criarNo(int chave) {
    No* no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->esquerda = no->direita = NULL;
    no->altura = 1;
    return no;
}

void atualizarAltura(No *no) {
    if (no)
        no->altura = 1 + maior(obterAltura(no->esquerda), obterAltura(no->direita));
}

// ---------------------- Rotações ----------------------
No* rotacaoDireitaSimples(No *y) {
    No *x = y->esquerda;
    No *subarvore = x->direita;

    x->direita = y;
    y->esquerda = subarvore;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

No* rotacaoEsquerdaSimples(No *x) {
    No *y = x->direita;
    No *subarvore = y->esquerda;

    y->esquerda = x;
    x->direita = subarvore;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

// ---------------------- Impressão em ordem com fator de balanceamento ----------------------
void imprimirEmOrdem(No *raiz) {
    if (!raiz) return;

    imprimirEmOrdem(raiz->esquerda);

    int fb = fatorBalanceamento(raiz);
    printf("%d(%+d) ", raiz->chave, fb);

    imprimirEmOrdem(raiz->direita);
}

// ---------------------- Controle da inserção ----------------------
typedef struct {
    int houveRotacao;
    char mensagemRotacao[50];
    int noResponsavel;
    int capturarInstantaneo;
    No *estadoAntes;
} InfoInsercao;

No* copiarArvore(No *raiz) {
    if (!raiz) return NULL;

    No *copia = criarNo(raiz->chave);
    copia->altura = raiz->altura;
    copia->esquerda = copiarArvore(raiz->esquerda);
    copia->direita = copiarArvore(raiz->direita);

    return copia;
}

// ---------------------- Inserção AVL ----------------------
No* inserir(No *no, int chave, InfoInsercao *info) {
    if (!no)
        return criarNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave, info);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave, info);
    else
        return no;

    atualizarAltura(no);

    int fb = fatorBalanceamento(no);

    if (abs(fb) > 1 && !info->houveRotacao) {
        info->noResponsavel = no->chave;
        info->capturarInstantaneo = 1;
        info->estadoAntes = copiarArvore(no);
    }

    // Caso 1: Left-Left
    if (fb < -1 && chave < no->esquerda->chave) {
        if (!info->houveRotacao) {
            info->houveRotacao = 1;
            strcpy(info->mensagemRotacao, "rotacao direita.");
        }
        return rotacaoDireitaSimples(no);
    }

    // Caso 2: Right-Right
    if (fb > 1 && chave > no->direita->chave) {
        if (!info->houveRotacao) {
            info->houveRotacao = 1;
            strcpy(info->mensagemRotacao, "rotacao esquerda.");
        }
        return rotacaoEsquerdaSimples(no);
    }

    // Caso 3: Left-Right
    if (fb < -1 && chave > no->esquerda->chave) {
        if (!info->houveRotacao) {
            info->houveRotacao = 1;
            strcpy(info->mensagemRotacao, "rotacao direita dupla.");
        }
        no->esquerda = rotacaoEsquerdaSimples(no->esquerda);
        return rotacaoDireitaSimples(no);
    }

    // Caso 4: Right-Left
    if (fb > 1 && chave < no->direita->chave) {
        if (!info->houveRotacao) {
            info->houveRotacao = 1;
            strcpy(info->mensagemRotacao, "rotacao esquerda dupla.");
        }
        no->direita = rotacaoDireitaSimples(no->direita);
        return rotacaoEsquerdaSimples(no);
    }

    return no;
}

// ---------------------- MAIN ----------------------
int main() {
    char linha[5000];
    int primeiroConjunto = 1;

    while (fgets(linha, sizeof(linha), stdin)) {

        if (!primeiroConjunto)
            printf("\n");

        primeiroConjunto = 0;

        No *raiz = NULL;
        char *token = strtok(linha, " \n");

        while (token) {
            int chave = atoi(token);

            InfoInsercao info = {0, "", 0, 0, NULL};

            raiz = inserir(raiz, chave, &info);

            if (info.houveRotacao) {
                printf("no responsavel: %d\n", info.noResponsavel);
                imprimirEmOrdem(info.estadoAntes);
                printf("\n%s\n", info.mensagemRotacao);
                imprimirEmOrdem(raiz);
                printf("\n%d\n", obterAltura(raiz));
            } else {
                printf("arvore ja balanceada.\n");
                imprimirEmOrdem(raiz);
                printf("\n%d\n", obterAltura(raiz));
            }

            token = strtok(NULL, " \n");
        }
    }

    printf("\n\n");
    return 0;
}
