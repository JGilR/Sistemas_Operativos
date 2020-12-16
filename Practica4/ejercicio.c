#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define SIZE 20
#define DATA 20

pthread_mutex_t mutex;
pthread_cond_t not_empty;
pthread_cond_t not_full;

int elementos_array;
int buffer[SIZE];


void productor(void){
    int info;
    for(int i=0; i<DATA; i++){
        info = i;
        pthread_mutex_lock(&mutex);

        while(elementos_array == SIZE){ //! Si buffer lleno
            pthread_cond_wait(&not_empty, &mutex); //! Se bloquea
        }
        buffer[i] = i;
        elementos_array++;
        pthread_cond_signal(&not_empty);
        printf("Producing data: %d\n", info);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void consumidor(void){
    int info;
    for(int i=0; i<DATA; i++){
        pthread_mutex_lock(&mutex);

        while(elementos_array == 0){
            pthread_cond_wait(&not_full, &mutex);
        }
        info = buffer[i];
        pthread_cond_signal(&not_full);
        printf("Data consume: %d\n", info);
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    pthread_t h1, h2;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);

    pthread_create(&h1, NULL, (void *)&productor, NULL);
    pthread_create(&h2, NULL, (void *)&consumidor, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);
    exit(0);
}
