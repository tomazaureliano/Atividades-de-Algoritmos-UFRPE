#include <stdio.h>
#include <stdlib.h>

int contadorChamadas = 0;

// Função para imprimir o vetor
void imprimeVetor(int vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

// Função merge
void merge(int vet[], int p, int q, int r) {
    printf("merge %d %d %d\n", p, q, r);

    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = vet[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = vet[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);

    imprimeVetor(vet, r + 1); // imprime vetor modificado até r
}

// Função mergesort
void mergesort(int vet[], int p, int r) {
    contadorChamadas++;
    printf("mergesort %d %d: empilhado!\n", p, r);

    if (p < r) {
        int q = (p + r) / 2;
        mergesort(vet, p, q);
        mergesort(vet, q + 1, r);
        merge(vet, p, q, r);
    }

    printf("mergesort %d %d: desempilhado!\n", p, r);
}

int main() {
    int opcao = 1;
    do{
    int M;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &M);

    int vet[M];
    printf("Digite %d elementos do vetor:\n", M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &vet[i]);
    }

    printf("\nVetor original:\n");
    imprimeVetor(vet, M);

    mergesort(vet, 0, M - 1);

    printf("\nNúmero total de chamadas ao mergesort: %d\n", contadorChamadas);

    printf("\nVetor ordenado final:\n");
    imprimeVetor(vet, M);
    
    printf("\nDeseja ordenar outro vetor? (1-Sim / 0-Não): ");
    scanf("%d", &opcao);
    if(opcao == 0){
        break;
    }
    }while(opcao != 0);

    return 0;
}
