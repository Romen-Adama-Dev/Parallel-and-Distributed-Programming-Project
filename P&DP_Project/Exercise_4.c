/**
 * 4º Exercise
 * Euler gamma constant is defined as the limit of a sequence gn.
 * Write a concurrent program that calculates gn, with the following assumptions: 
 * - N - the number of elements of the sum is loaded from the keyboard 
 * - P - number of processes, which will compute the sum is a constant in a program
 * Each process calculate his own fragment of the sum - for example, for n = 100, p = 10,
 * the first process computes elements 1 to 10, the second from 11 to 20, etc.,
 * at the end the partial sums are added and logarithm is subtracted.
 *  Note: n may not be divisible by p. The program can be made using any familliar technique . 
 **/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include <math.h>

int main(void)
{
    #define N 10000
    int threads = 10;
    omp_set_num_threads(threads);
    double sum = 0;
    double count;
    #pragma omp parallel for shared(sum)
    for(int i = 1; i < (N + 1) ; i++){
        count = i;
        sum += 1/count;
    }
    printf("Starting Counting \n\n")
    //Double log(double x) returns the natural logarithm (base-e logarithm) of x
    double euler = sum - log(N);

    printf("The result of Euler function %d with iterations and threads %d is : %f \n\n",N,threads,euler);
}

/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/
