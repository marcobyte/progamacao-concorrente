#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 1000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);

int main() {
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    int x = 10;
    int i, count = 0;
    double inicio = omp_get_wtime();
    // sequencial
    for (i = 0; i < TAMANHO; i++)
    {
        if(x == vetor[i]){
            count++;
        }
    }
    double fim = omp_get_wtime();
    double t_sequencial = fim-inicio;
    printf("repeticoes de x: %d\n", count);
    printf("tempo sequencial: %f\n", t_sequencial);
    count = 0;

    //paralelo
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        int count_p = 0;
        #pragma omp for
            for (i = 0; i < TAMANHO; i++)
            {
                if(x == vetor[i]){
                count_p++;
            }
    }
        #pragma omp critical
            count += count_p;
    }
    fim = omp_get_wtime();
    double t_paralelo = fim-inicio;
    printf("repeticoes de x: %d\n", count);
    printf("tempo paralelo: %f\n", t_paralelo);
    double speedup = t_sequencial/t_paralelo;
    printf("Speedup: %f\n", speedup);
    printf("Eficiencia: %f\n", speedup/3);
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}