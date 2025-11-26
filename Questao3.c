#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ContadorTrocas = 0;

void ImprimirVetor(int vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void Troca(int vet[], int i, int j){
    int temp = vet[i];
    vet[i] = vet[j];
    vet[j] = temp;

    ContadorTrocas++;
}

int Particiona(int vet[], int p, int r) {
    int pivo = vet[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (vet[j] <= pivo) {
            i++;
            Troca(vet, i, j);
        }
    }
    Troca(vet, i + 1, r);
    return i + 1;
}