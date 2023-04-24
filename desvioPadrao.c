#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define n 10000000

int main() {
    float vetor[n];
    int i;
    float soma = 0.0, mean, diferenca = 0.0, resultado;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        vetor[i] = (float)rand() / RAND_MAX;
    }

    #pragma omp parallel for reduction(+:soma)
    for (i = 0; i < n; i++) {
        soma += vetor[i];
    }
    mean = soma / n;


    #pragma omp parallel for reduction(+:soma_sq_diff)
    for (i = 0; i < n; i++) {
        float a = vetor[i] - mean;
        diferenca += a * a;
    }
    resultado = sqrt(diferenca / n);

    printf("Desvio padrao: %.5f\n", resultado);

    return 0;
}