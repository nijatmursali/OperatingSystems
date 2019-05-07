#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define N 5
#define M 4 

int main(int argc, char *argv[]) {

    int R[N][M];
    
    int available[] = {2, 1, 3, 5};

    int maximum[N][M] = {{3, 2, 4, 5}, 
                        {2, 4, 5, 1}, 
                        {7, 0, 4, 3}, 
                        {3, 2, 4, 2}, 
                        {1, 3, 3, 4}}; 
    
    int C[N][M] =   {{0, 1, 0, 1}, 
                    {2, 0, 0, 5}, 
                    {3, 0, 2, 3}, 
                    {2, 1, 1, 3}, 
                    {0, 0, 2, 2}}; 

    int i, j, p , k, cnt = 0;
    bool isSafe;
    for (i = 0; i < N; i++)
    {
        /* code */
        for (j = 0; j < M; j++)
        {
            /* code */
            R[i][j] = maximum[i][j] - C[i][j]; // finding request matrix
        }
    }
    
    bool finishedState[N] = {0};

    int safeSequence[N];

    int work[M];
    while(cnt < N) {
        isSafe = false;

        for (p = 0; p < N; p++)
        {
            /* code */
            if (finishedState[p] == 0) 
            {
                /* code */
                for (j = 0 ; j < M; j++) 
                    if(R[p][j] > available[j])
                        break;

                if(j == M) {
                    for(k = 0; k < M; k++)
                        available[k] += C[p][k];

                    safeSequence[cnt++] = p;
                    finishedState[p] = 1;
                    isSafe = true;
                }
            }
            
        }
        if (isSafe == false)
        {
            /* code */
            printf("This is not safe state.\n");
            return false;
           
        }
        
        
    }
    printf("This is safe state.\n");
    return true;

}