#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLON 1000

pthread_t h1, hmain;
char * string;

void *thread(void *arg){
    printf("Thread 1 realiza la cuenta de letras.");
    cuenta(string);
    pthread_exit(NULL);
}


void cuenta(char * nombre){
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;

    fd = fopen(nombre, O_RDONLY);
    while((leidos = read (fd, cadena, MAXLON)) != 0){
        for(pos = 0; pos < leidos; pos++){
            if((cadena[pos] == 'a') || (cadena[pos] == 'A')){
                cont++;
            }
            printf("Fichero%s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
            close(fd);
        }
    }
}

int main (int argc, char *argv[]){
    if(argc != 2){
        printf("Indica el nombre de un fichero.\n");
        exit(0);
    }
    string = argv[1];
    hmain = pthread_self();
    pthread_create(&h1, NULL, thread, NULL);
    pthread_join(h1, NULL);
    return 0;
}
