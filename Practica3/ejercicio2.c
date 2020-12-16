#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

int buffer[SIZE];
pthread_t h1, h2;
sem_t sem;
int cont = 0;

//TODO: Funciones esta vacio o lleno el buffer
int is_empty(int b[]){
    for( int i=0; i<SIZE; i++){
        if(b[i] != 0){
            return -1; // Return false
        }
    }
    return 0; // Return true
}

int is_full(int b[]){
    for( int i=0; i<SIZE; i++){
        if(b[i] == 0){
            return -1; // Return false
        }
    }
    return 0; // Return true
}

//TODO: Funciones producir info en buffer y consumir info en buffer
int produce_info(int b[]){
    for(int i=0; i<SIZE; i++){
        if(is_empty){
            b[i] = i;
        }
    }
}

int consume_info(int b[]){
    for(int i=0; i<SIZE; i++){
        if(is_full){
            b[i] = 0;
        }
    }
}


//TODO: Funciones productor-consumidor
void *productor(void * arg){
    for(int i=0; i<SIZE; i++){
        sem_wait(&sem);
        if(is_empty){
            //! Produce informacion
            produce_info(buffer);
            printf("Info added to the buffer.\n");
        }
        sem_post(&sem);
    }
}

void *consumidor(void * arg){
    for(int i=0; i<SIZE; i++){
        sem_wait(&sem);
        if(is_full){
            //! Consume informacion
            consume_info(buffer);
            printf("Info was consumed.\n");
        }
        sem_post(&sem);
    }
}




int main(void){
    sem_init(&sem, 0, 1);
    pthread_create(&h1, NULL, *productor, NULL);
    pthread_create(&h2, NULL, *consumidor, NULL);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    return 0;
}
