/**
 * Exercise 6
 * Write a program that calculates the prime numbers using the sieve of Erathosthenes.
 * The program should be made with the use of OpenMP.
 **/
#include<stdio.h>
#include<math.h>
#include<omp.h>
#define T 4

int main(){

    #define S 1000
    int array[S],tab,j;
    int max = sqrt(S);
    int threads = 4;
    omp_set_num_threads(threads);

    for(int i = 0; i < S; i++){
        array[i] = i + 1;
    }

    
    for(int i = 1; i <= max; i++){

        if(array[i] != 0){
	    #pragma omp parallel for private(j) firstprivate(i)
            for(j = pow(array[i], 2); j <= S; j = j + array[i]){
                array[j - 1] = 0;
            }
        }
    }

    printf("Primes until %d\n", S);
    for(int i = 1; i < S; i++){
        if(array[i] != 0){
            printf("%d\n", array[i]);
        }
    }

    printf("\n");

    return 0;
}

/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/