#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

#ifdef _unix_
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

int readercount = 0;
int writercount = 0;
int N = 30; // Number of threads for readers and writers 
sem_t mutexwriter, mutexreader;

int limitforreader = 10;
int limitforwriter = 10;
int data=10;
int inactiveReader=0;
int inactiveWriter=10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t number = PTHREAD_COND_INITIALIZER;

using namespace std;

void *readerFunction(void *threadid) {
pthread_mutex_lock(&mutex);
    long tid;
    tid = (long)threadid;

        if(readercount < limitforreader) {
            readercount++;
            sem_wait(&mutexreader);


            printf("New reader %ld\n", tid);
            printf("Reader %ld is accesing the Data %d.\n", tid, data);
            printf("Number of active reader threads at the moment are %d\n", tid+1);
            printf("Number of inactive reader thread(s) at the moment are%d\n",inactiveReader);
            printf("Number of active writer thread(s) at the moment are %d\n", writercount);
            sleep(2);

            /*
            if(tid==5 || tid==7) {
                inactiveReader++;
                while(!number){
                pthread_cond_wait(&number, &mutex);
                }
            
            }
            */

               }
            sem_post(&mutexreader);
     pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *writerFunction(void *threadid) {
pthread_mutex_lock(&mutex);
        long tid;
        tid = (long)threadid;


            if(writercount < limitforwriter) {
             if(tid==0 || tid==1){
               inactiveWriter--;
               writercount++;


               if(tid==1){
               // pthread_mutex_lock(&mutex);
                data=11;
               // pthread_mutex_unlock(&mutex);
               }

                printf("New writer %ld\n", tid);
                printf("Writer %ld accessing the Data %d.\n", tid, data);
                printf("Number of active writer thread(s) at the moment are %d\n", tid);
                printf("Number ofInactive writer thread(s) at the moment are %d\n", inactiveWriter);
                sleep(2);
                sem_post(&mutexwriter);
             }

            }
            else if(tid!=0 || tid !=1) {
                  while(!number){
                pthread_cond_wait(&number, &mutex);
                }
            }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);

}

int main() {

    pthread_t readerThreads[N], writerThreads[N];
    sem_init(&mutexwriter, 0,1);
    sem_init(&mutexreader, 0,1);
    int writecount, i , readcount;

    for(i = 0; i <N; i++) {


    writecount = pthread_create(&writerThreads[i], NULL, writerFunction, (void *)i);

     readcount = pthread_create(&readerThreads[i], NULL, readerFunction, (void *)i);


        if ( readcount!=0 || writecount !=0) {
         cout << "Thread is not created. Try again\n" << readcount << endl;
         exit(-1);
      }

   }

   for(i = 0; i <N; i++) {
       pthread_join(writerThreads[i], NULL);

       pthread_join(readerThreads[i], NULL);



   }


   pthread_exit(NULL);

}