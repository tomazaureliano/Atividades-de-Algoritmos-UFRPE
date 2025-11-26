#include <stdio.h>
#include <stdlib.h>

int contadorTrocas = 0;
int contadorMaxHeapfy = 0;

// Função para imprimir o vetor
void imprimeVetor(int vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

// Função para trocar dois elementos e contar a troca
void trocar(int vet[], int i, int j) {
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
    contadorTrocas++;
}

// Função maxHeapfy (mantém a propriedade de max-heap)
void maxHeapfy(int vet[], int n, int i) {
    contadorMaxHeapfy++;
    printf("maxheapfy %d\n", i);

    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && vet[esquerda] > vet[maior])
        maior = esquerda;
    if (direita < n && vet[direita] > vet[maior])
        maior = direita;

    if (maior != i) {
        trocar(vet, i, maior);
        maxHeapfy(vet, n, maior);
    }

    imprimeVetor(vet, n);
}

// Função para construir o heap máximo
void construirMaxHeap(int vet[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapfy(vet, n, i);
    }
}

// Função heapsort
void heapsort(int vet[], int n) {
    construirMaxHeap(vet, n);

    printf("Vetor após construirMaxHeap:\n");
    imprimeVetor(vet, n);

    for (int i = n - 1; i > 0; i--) {
        trocar(vet, 0, i);
        maxHeapfy(vet, i, 0);
    }
}

int main() {
    int opcao = 1;

    do {
        contadorTrocas = 0;
        contadorMaxHeapfy = 0;

        int M;
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &M);

        int vet[M];
        printf("Digite os %d elementos do vetor:\n", M);
        for (int i = 0; i < M; i++) {
            scanf("%d", &vet[i]);
        }

        printf("\nVetor original:\n");
        imprimeVetor(vet, M);

        heapsort(vet, M);

        printf("\nNúmero total de chamadas a maxHeapfy: %d\n", contadorMaxHeapfy);
        printf("Número total de trocas: %d\n", contadorTrocas);

        printf("\nVetor ordenado final:\n");
        imprimeVetor(vet, M);
     
        printf("\nDeseja ordenar outro vetor? (1-Sim / 0-Não): ");
     
        scanf(" %d", &opcao);
        printf("\n");

    } while (opcao == 1);

    printf("Encerrando o programa...\n");
    return 0;
}
