/**
 * 3º Exercise
 * Write a program that calculates the value of the expression using the Mclaurin series.
 * Compare the obtained value with the value from the math library. Measure the time of
 * execution of the program for the different number of threads.
 * The program should be made with the use of MPI or Pthreads.
 * -----------------------------------------------------------------------------------------
 * 
 * The Maclaurin series is a template that allows you to express many other functions as power series.
 * It is the source of formulas for expressing both sin x and cos x as infinite series.
 * 
 */

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long double x, fact[150], pwr[150], s[1];
int i, term;

//Power functions allow us to gradually approximate its.
//The pow() function takes two arguments (base value and power value) and, returns the power raised to the base number.
void *Power(void *temp) {
    int k;
    for (k = 0; k < 150; k++) {
        pwr[k] =pow(x, (double) k);
    }
    return pwr;
}

// Factorial function is the product of all positive integers less than or equal to n. 
//The factorial of n also equals the product of n with the next smaller factorial:
void *Fact(void *temp) {
    long double f;
    int j;
    fact[0] = 1.0;
    for (term = 1; term < 150; term++) {
        f = 1.0;
        for (j = term; j > 0; j--)
            f = f * j;
        fact[term] = f;
    }
    return fact;
}

//One thread overwrite the same variable concurrently with partial calculation results
void *Exp(void *temp) {
    int t;
    s[0] = 0;
    for (t = 0; t < 150; t++)
        s[0] = s[0] + (pwr[t] / fact[t]);
    return s;
}


int main(void) {

    time_t start,stop;
    pthread_t thread1, thread2, thread3;
    long double **sum;
    time(&start);

    //Prints the main loop activity
    printf("Enter the value of x (0-100)for calculating exp(x):");
    scanf("%Lf", &x);

    printf("\n Threads creating.....\n");
    pthread_create(&thread1, NULL, Power, NULL); //calling power function
    pthread_create(&thread2, NULL, Fact, NULL); //calling factorial function

    printf("Threads created\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Principal thread and terminated threads are joining\n");

    printf("Result collected in Principal thread\n");
    pthread_create(&thread3, NULL, Exp, NULL);
    pthread_join(thread3, NULL);

    printf("Value of exp(%.2Lf) according math library is : %f\n\n", x, exp(x));

    printf("\nValue of exp(%.2Lf) according this program is :
    %Lf\n\n", x, s[0]);

    time(&stop);

    printf("Execution time:%ld s\n",stop-start);
    exit(1);
}

/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/