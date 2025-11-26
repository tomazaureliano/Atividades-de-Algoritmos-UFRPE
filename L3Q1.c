#include <stdio.h>
#include <stdlib.h>
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    struct No* pai;
} No;
typedef struct Arvore {
    No* raiz;
} Arvore;

No* criarNo(int valor, No* pai) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->pai = pai;
    return novoNo;
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int BuscarValor(No* atual, int valor) {
    if (atual == NULL) {
        return 0; 
    }
    else if (valor == atual->valor) {
        return 1; 
    }
    else if (valor < atual->valor) {
        return BuscarValor(atual->esquerda, valor);
    }
    else {
        return BuscarValor(atual->direita, valor);
    }
  
   
}

int InserirValor(No* atual, int valor) {
    if(valor < atual->valor) {
        if(atual->esquerda == NULL) {
            atual->esquerda = criarNo(valor, atual);
            return 1;
        }
        else {
            return InserirValor(atual->esquerda, valor);
        }
    }
    else if (valor > atual->valor) {
        if(atual->direita == NULL) {
            atual->direita = criarNo(valor, atual);
            return 1;
        }
        else {
            return InserirValor(atual->direita, valor);
        }
    }
    else {
        return 0; 
    }
}
    No* minimo(No* no) {
        while(no->esquerda != NULL) {
            no = no->esquerda;
        }
        return no;
}
No* Sucessor(No* no) {
    if(no->direita != NULL) {
        return minimo(no->direita);
    }
    No* pai = no->pai;
    while(pai != NULL && no == pai->direita) {
        no = pai;
        pai = pai->pai;
    }
    return pai;
}
No* removerValor(No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (valor < raiz->valor) {
        raiz->esquerda = removerValor(raiz->esquerda, valor);
        if(raiz->esquerda != NULL) {
            raiz->esquerda->pai = raiz;
        }
    } else if (valor > raiz->valor) {
        raiz->direita = removerValor(raiz->direita, valor);
        if(raiz->direita != NULL) {
            raiz->direita->pai = raiz;
        }
    } else {
        // Caso 1: Nó com apenas um filho ou nenhum
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            if (temp != NULL) {
                temp->pai = raiz->pai;
            }
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            if (temp != NULL) {
                temp->pai = raiz->pai;
            }
            free(raiz);
            return temp;
        } else {
        // Caso 2: Nó com dois filhos
        No* sucessor = Sucessor(raiz);
        raiz->valor = sucessor->valor;
        raiz->direita = removerValor(raiz->direita, sucessor->valor);
        if(raiz->direita != NULL) {
            raiz->direita->pai = raiz;
        }
    }
    }
    return raiz;
}

int main(void) {
    int x;
    Arvore* minhaArvore = (Arvore*)malloc(sizeof(Arvore));
    minhaArvore->raiz = criarNo(10, NULL);
    minhaArvore->raiz->esquerda = criarNo(5, minhaArvore->raiz);
    minhaArvore->raiz->direita = criarNo(15, minhaArvore->raiz);
    minhaArvore->raiz->esquerda->esquerda = criarNo(3, minhaArvore->raiz->esquerda);
    minhaArvore->raiz->esquerda->direita = criarNo(7, minhaArvore->raiz->esquerda);
    minhaArvore->raiz->direita->esquerda = criarNo(12, minhaArvore->raiz->direita);
    minhaArvore->raiz->direita->direita = criarNo(18, minhaArvore->raiz->direita);

    printf("Árvore binária de busca criada.\n");
    do{
    printf("Qual operação deseja realizar?\n");
    printf("1. Buscar valor\n");
    printf("2. Inserir valor\n");
    printf("3. Encontrar sucessor\n");
    printf("4. Remover valor\n");
    int opcao;
    scanf("%d", &opcao);
    if(opcao == 2) {
        int valorParaInserir;
        printf("Digite o valor a ser inserido na árvore: ");
        scanf("%d", &valorParaInserir);
        InserirValor(minhaArvore->raiz, valorParaInserir);
        printf("Valor %d inserido na árvore.\n", valorParaInserir);
    }
    else if (opcao == 1) {
    int valorParaBuscar;
    printf("Digite o valor a ser buscado na árvore: ");
    scanf("%d", &valorParaBuscar);
    if (BuscarValor(minhaArvore->raiz, valorParaBuscar)) {
        printf("Valor %d encontrado na árvore.\n", valorParaBuscar);
    } else {
        printf("Valor %d não encontrado na árvore.\n", valorParaBuscar);
    }
  }
  else if (opcao == 3) {
      int valorParaBuscarSucessor;
      printf("Digite o valor para encontrar o sucessor: ");
      scanf("%d", &valorParaBuscarSucessor);
      No* noAtual = minhaArvore->raiz;
      while(noAtual != NULL && noAtual->valor != valorParaBuscarSucessor) {
          if(valorParaBuscarSucessor < noAtual->valor) {
              noAtual = noAtual->esquerda;
          } else {
              noAtual = noAtual->direita;
          }
      }
      if(noAtual == NULL) {
          printf("Valor %d não encontrado na árvore.\n", valorParaBuscarSucessor);
      } else {
          No* sucessor = Sucessor(noAtual);
          if(sucessor != NULL) {
              printf("O sucessor de %d é %d.\n", valorParaBuscarSucessor, sucessor->valor);
          } else {
              printf("O valor %d não tem sucessor na árvore.\n", valorParaBuscarSucessor);
          }
      }
  }
  else if (opcao == 4) {
      int valorParaRemover;
      printf("Digite o valor a ser removido da árvore: ");
      scanf("%d", &valorParaRemover);
      if(!BuscarValor(minhaArvore->raiz, valorParaRemover)) {
          printf("Valor %d não encontrado na árvore.\n", valorParaRemover);
      } else {
          minhaArvore->raiz = removerValor(minhaArvore->raiz, valorParaRemover);
          if(minhaArvore->raiz != NULL) {
              minhaArvore->raiz->pai = NULL;
          }
          printf("Valor %d removido da árvore.\n", valorParaRemover);
      }
  }
}while (1);
    liberarArvore(minhaArvore->raiz);
    free(minhaArvore);
    scanf("%d", &x);
    return 0;
    
}