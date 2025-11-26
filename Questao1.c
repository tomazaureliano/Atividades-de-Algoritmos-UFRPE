#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int *elementos;
    int tamanho;
    int capacidade;
} Vetor;

Vetor* CriarVetor(Vetor *vetor) {
    int capacidade;
    printf("Qual a capacidade inicial do vetor? ");
    scanf("%d", &capacidade);
    vetor = (Vetor *)malloc(sizeof(Vetor));
    vetor->elementos = (int *)malloc(capacidade * sizeof(int));
    vetor->tamanho = 0;
    vetor->capacidade = capacidade;
    return vetor;
}



void ImprimirVetor(Vetor *vetor) {
    for(int i = 0; i < vetor->tamanho; i++) {
        if(vetor->elementos[i] != 0){
        printf("%d ", vetor->elementos[i]);
        }
        else{
            printf("NIL ");
    }
    printf("\n");
}
}

void inserir(Vetor *vetor, int valor) {
    if (vetor->tamanho == vetor->capacidade) {
        int novaCapacidade = vetor->capacidade * 2;
        int *novoArray = (int*) malloc(novaCapacidade * sizeof(int));

        
        for (int i = 0; i < vetor->tamanho; i++) {
            novoArray[i] = vetor->elementos[i];
        }


        free(vetor->elementos);
        vetor->elementos = novoArray;
        vetor->capacidade = novaCapacidade;

        printf("Capacidade aumentada para: %d\n", novaCapacidade);
    }

    // Insere o novo elemento
    vetor->elementos[vetor->tamanho] = valor;
    vetor->tamanho++;
}

int buscarElemento(Vetor *vetor, int valor) { 
    for (int i = 0; i < vetor->tamanho; i++) {
        if (vetor->elementos[i] == valor) {
            return i; 
        }
        else{
            printf("Elemento %d não encontrado no vetor.\n", valor);
        }
    }
     
}

void remover(Vetor *vetor, int valor) {
    int indice = buscarElemento(vetor, valor);
    if (indice != -1) {
        for (int i = indice; i < vetor->tamanho - 1; i++) {
            vetor->elementos[i] = vetor->elementos[i + 1];
        }
        vetor->tamanho--;
        printf("Elemento %d removido.\n", valor);
    } else {
        printf("Elemento %d não encontrado no vetor.\n", valor);
    }
}


int main(void){
	
    printf("Iniciando o programa...\n");
    Vetor *vetor = CriarVetor(vetor);
    int continuar = 1;
    do {
    printf("Qual operação você deseja realizar?\n");
    printf("1 - Inserir elemento\n");
    printf("2 - Remover elemento\n");
    printf("3 - Buscar elemento\n");
    printf("4 - Imprimir vetor\n");
    int operacao, valor;
    scanf("%d", &operacao);
    switch(operacao) {
        case 1:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(vetor, valor);
            break;
        case 2:
            printf("Digite o valor a ser removido: ");
            scanf("%d", &valor);
            remover(vetor, valor);
            break;
        case 3:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            int indice = buscarElemento(vetor, valor);
            if (indice != -1) {
                printf("Elemento %d encontrado no índice %d.\n", valor, indice);
            } else {
                printf("Elemento %d não encontrado no vetor.\n", valor);
            }
            break;
        case 4:
            ImprimirVetor(vetor);
            break;
        default:
            printf("Operação inválida.\n");
            break;
    }
    printf("Deseja realizar outra operação? (1 - Sim, 0 - Não): ");
    scanf("%d", &continuar);

} while(continuar == 1);

	return 0;
}