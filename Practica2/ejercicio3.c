#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *hola(void *arg) {
    char *msg = "Hola";
    int i;

    printf("Thread 1: ");
    for ( i = 0 ; i < strlen (msg) ; i++ ) {
        printf (" %c", msg[i]);
        fflush (stdout );
        usleep (1000000) ;
    }
    pthread_mutex_unlock(&mutex);
}

void *mundo(void *arg ) {
    char *msg = "Mundo ";
    int i;

    pthread_mutex_lock(&mutex);
    printf("\nThread 2: ");
    for ( i = 0 ; i < strlen (msg) ; i++ ) {
        printf (" %c", msg[i]);
        fflush (stdout );
        usleep (1000000) ;
    }
    printf("\n");
}

int  main(int  argc , char *argv []) {
    pthread_t  h1;
    pthread_t  h2;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    pthread_create(&h2, NULL , mundo , NULL);
    pthread_create(&h1, NULL , hola , NULL);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}

