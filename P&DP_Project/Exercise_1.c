/**
 * Design a program to simulate the lift. Passengers come to random floors and if the lift is idle, they 
 * call for it. When the lift is in motion, the passenger has to wait on his floor, until it becomes idle and 
 * then he can invoke it. It may happen that the lift will stop on the floor because someone is getting 
 * off. In such case it can take passengers, who are going in the same direction as the lift. The lift is
 * idle on the floor where all the passengers leaves it and no one is waiting for it. The program should 
 * be made with the use of MPI.
 * reference to understand the exercise. This code have a example of the main task of this exercise = http://freesourcecode.net/cprojects/105757/Elevator-simulation-in-c#.YdTEbGgWWUk
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv) {
    
    // MPI Variables 
    int rank, value, size;
    int aux[3];
    int *msg = aux;
    MPI_Request request;
    MPI_Status status;

    //Elevator and user variables
    int e_status e_floor, e_destination = e_status = e_floor = e_destination = 0;
    int u_floor, u_destination = u_floor = 0;

    MPI_Init(&argc,&argv); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
    MPI_Comm_size(MPI_COMM_WORLD,&size); 

    // MPI rank & treatment
    if (rank == 0) {
        // Start
        MPI_Bcast(&value, 1, MPI_INT, rank, MPI_COMM_WORLD);
    } else if (rank == 1) {
    // Start Elevator task
        for(int i = 0; i < size - 2; i++) {
                // Loop for the number of number of users
                printf("[!] E_Status : IDLE\n");
                
                MPI_Irecv (msg, 3, MPI_INT,  MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &request);
                MPI_Wait(&request, &status);

                u_floor = e_destination = msg[0];
                u_destination = msg[1];

                printf("[S]\tE_Status : Picking User %d - Elevator started moving from %d to %d.\n", msg[2] , e_floor , u_floor);

                e_status = 1;


                // User destination;
                while (e_status != -1) {
                    // Loop that iterate until user arrives to floor desired
                    if (e_status == 1) {
                        // Picking condition            
                        printf("\t\tE_Status : In floor %d.\n", e_floor);

                        // Elevator move
                        if (e_floor < u_floor) {
                            e_floor += 1;
                        } else if (e_floor > u_floor) {
                            e_floor -= 1;
                        } else {
                            e_status = 2;
                            // Delivery mode

                            printf("[E]\t\tE_Status : Elevator Reached Destination.\n");

                            e_destination = u_destination;

                            printf("[S]\tE_Status : Delivering User %d - Elevator started moving from %d to %d.\n",msg[2] , e_floor , u_destination);
                        }
                    } else {
                        // Delivering status
                        printf("\t\tE_Status : In floor %d.\n", e_floor);
                        
                        // elevator movement
                        if (e_floor < e_destination) {
                            e_floor += 1;
                        } else if (e_floor > e_destination) {
                            e_floor -= 1;
                        } else {
                            e_status = -1;
                            // End mode
                            printf("[E]\t\tE_Status : Elevator Reached Destination.\n");
                        }
                    }
                    sleep(1);
            }
        }
    } else {
        // Start user process
        srand(time(NULL) + rank);
        // Random number generator by time and rank seed
        u_floor = rand() % 10;
        u_destination = rand() % 10;

        aux[0] = u_floor;
        aux[1] = u_destination;
        aux[2] = rank - 1;
        msg = aux;

        MPI_Isend (msg, 3, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);   
    }

    MPI_Finalize();
    return(0); 
}

/**
 * Last Date: 04/01/2022
 * @author Romen Adama Caetano Ramirez
**/