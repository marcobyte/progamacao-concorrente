#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define num_steps 100000000
int main(){
    double step;
    double x, pi;
    int t = omp_get_num_threads();
    x = 0;
    pi = 0;
    double soma = 0;
    double inicio = omp_get_wtime();
    step = 1.0/(double) num_steps;
    #pragma omp parallel num_threads(4)
    {
        double x,soma=0.0;
        int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for (i=id,soma=0.0;i< num_steps; i=i+nthrds){
            x = (i + 0.5) * step;
            soma = soma + 4.0 / (1.0 + x*x);
        }
        #pragma omp critical
            pi+=soma*step;
    }
    double fim = omp_get_wtime();
    double t_paralelo = fim-inicio;
    printf("Pi: %f\n",pi);
    printf("Execucao paralela(s): %f\n",t_paralelo);

    return 0;
}