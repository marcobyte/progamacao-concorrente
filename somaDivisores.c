#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    long int numero = 1500000000;
    long int j = 1;
    double soma;
    double inicio = omp_get_wtime();

    for(int j=1; j<numero; j++){
        if(numero%j==0){
            soma += j;
        }
    }
    double fim = omp_get_wtime();
    printf("Soma sequencial: %f \n", soma);
    printf("Tempo Sequencial: %f \n", fim-inicio);

    soma = 0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for
            for(j=1;j<numero;j++){
                if(numero%j==0){
                    sum += j;
                }
            }
        #pragma omp critical
            soma += sum;
    }
    fim = omp_get_wtime();

    printf("Soma paralela: %f \n", soma);
    printf("Tempo paralelo: %f \n", fim-inicio);

    soma = 0.0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for schedule(static, omp_get_num_threads())
            for(j=1;j<numero;j++){
                if(numero%j==0){
                    sum += j;
                }
            }
        soma +=sum;
    }
    printf("Static: %f \n", soma);
    fim = omp_get_wtime();
    printf("Tempo static: %f \n", fim-inicio);

    soma = 0.0;

    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(3)
    {
        double sum = 0.0;
        #pragma omp for schedule(dynamic, omp_get_num_threads())
            for(j=1;j<numero;j++){
                if(numero%j==0){
                    sum += j;
                }
            }
        soma +=sum;
    }
    printf("Dynamic: %f \n", soma);
    fim = omp_get_wtime();
    printf("Tempo dynamic: %f \n", fim-inicio);
    return 0;
}