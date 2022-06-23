#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define f(x) (1/(1+x*x))
#define NUM_THR 10



void* trapeRule(void *thread_id){

        double a = 0, b = 1, h, ifx = 0.0, i;
        int n = 1000, id, aux;

        id = *(int *)(&thread_id);

        h = (b-a) / n;
        ifx = ifx + f(a) + f(b);
        aux = (a+h)/NUM_THR;

        for (i = id*aux; i < (id+1)*b;){
                ifx = ifx + (2 * f(i));
                i = i + h;
        }

        ifx = (ifx * h / 2)*4;
        printf("The definite integral value using the Trapezoidal Rule is %lf\n", ifx);
}

int main (){

        int thread, i;
        void * j;
        double t;
        pthread_t thread_array[NUM_THR];
        time_t start,stop;
        time(&start);
        for(i=0; i<NUM_THR; i++){
                pthread_create( &thread_array[i], NULL, &trapeRule, j );
        }

        for(i=0; i<NUM_THR; i++){
                pthread_join(thread_array[i], NULL);
        }
        time(&stop);
        printf("Execution time:%ld s\n",stop-start);
}

/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/