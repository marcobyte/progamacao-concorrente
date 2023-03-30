#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define MAX 10000000

float *gerar_vetor(int n);

int main(){
    double soma, media;
    int i;
    time_t t;
    srand(time(NULL));
    double inicio = omp_get_wtime();
    float *vetor = (float*)malloc(MAX*sizeof(float));
    vetor = gerar_vetor(MAX);

    #pragma omp parallel num_thread(4)
    {
        #pragma omp for
        for(i = 0; 1<MAX; i++){
            soma += vetor[i];
        }
    }
    media = soma/(float)MAX;
    double fim = omp_get_wtime();
    double t_paralelo = fim - inicio;
    printf("Media: %lf \n", media);
    printf("execucao paralela sequencial: %lf \n", t_paralelo);

    float somaP;
    float mediaP;

    double inicioParalelo = omp_get_wtime();
    float *vetor1 = (float*)malloc(MAX*sizeof(float));
    vetor1 = gerar_vetor(MAX);

    for ( i = 0; i < MAX; i++)
    {
        somaP = somaP + vetor1[i];
    }
    
    mediaP = somaP/(float)MAX;
    double fimParalelo = omp_get_wtime();
    double t_serial = fimParalelo - inicioParalelo;
    double speedup = (t_paralelo - t_serial);
    media = soma/(double)MAX;
    printf("Soma: %lf\n",somaP);
    printf("Media: %lf\n",mediaP);
    printf("Tempo paralelo: %.4f\n",t_paralelo);
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiência: %f\n",eficiencia);
      
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand()%100000);
        vetor[i] = num;
    }
    return vetor;
}