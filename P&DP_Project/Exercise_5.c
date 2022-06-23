/**
 * Exercise 5
 * Write a parallel program that solves the following system
 * of linear equations with the use of OpenMP:
 * To undestand this code, I search about info in internet
 * Based on this page: https://notesformsc.org/c-gauss-elimination-method/
 **/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(){

    int n,i,j,k;
    float a[10][10]={0.0}, x[10]={0.0};
    float pivot = 0.0;
    float factor = 0.0;
    float sum = 0.0;
    double start,stop;

    printf("Solution by Simple Gauss Elimination \n\n");
    printf("Text n numbers value for N:");

    scanf("%d",&n);
    printf("\nCreate your equation. \n");
    printf("\nInput coeficients, row-wise:\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=n+1;j++){
                if(j>i && j<n+1){
                a[i][j]=0;
                }else{
                        scanf("%f",&a[i][j]);
                }
        }
    }
    printf("\n\n");
    start = omp_get_wtime();
    for(i=1;i<=n;i++){
        for(j=1;j<=n+1;j++){
                if(j==1){
                        printf("%1.0fX%d",a[i][j],j);
                }else if(j<n+1){
                        printf("+%1.0fX%d",a[i][j],j);
                }else{
                        printf("=%1.0f",a[i][j]);
                }
        }

       printf("\n\n");

   }

   for(k=1;k<=n-1;k++){
        //Error detector
        if(a[k][k]==0.0){
                printf("error");
        }else{
                pivot = a[k][k];

                for(j=k;j<=n+1;j++){
                        a[k][j]= a[k][j]/pivot;
                }

                        for(i=k+1;i<=n;i++){   
                factor = a[i][k];
                                #pragma omp parallel for reduction(*:a) private(k) firstprivate(i)
                                for(j = k;j<=n+1;j++){
                                        a[i][j] = a[i][j] - factor * a[k][j];
                                }
                        }
        }
        //Error detector
        if(a[n][n]==0){
                printf("error");
        }else{
                x[n] = a[n][n+1]/a[n][n];
                for(i=n-1;i>=1;i--){
                        #pragma omp parallel for reduction(*:sum) private(j) firstprivate(i)
                        for(j=i+1;j<=n;j++){
                                sum = sum + a[i][j] * x[j];
                                x[i]= ( a[i][n+1]- sum )/a[i][i];
                        }
                }
        }
   }
    stop = omp_get_wtime();
    for(i=1;i<=n;i++){
        printf("\nX%1d=%5.4f",i,x[i]);
    }
    printf("\nExecution time=%f\n",stop-start);
    return 0;
}
/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/