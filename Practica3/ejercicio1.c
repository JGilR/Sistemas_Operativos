#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define SIZE 512

int main (int argc, char **argv){
    pid_t pid;
    char buffer[SIZE];
    int p[2];

    pipe(p);

    pid = fork();

    switch(pid){

        case -1: // Error

            printf("Error, no se pudo crear hijo.");
            exit(-1);
            break;
        
        case 0: // Hijo

            close(p[0]); // Cerramos el descriptor de lectura

            printf("El hijo escribe en el PIPE ... \n");
            usleep(1000000);
            strcpy(buffer, "Hola Papichulo");
            write(p[1], buffer, SIZE);
            close(p[1]); // Cerramos el descriptor de escritura
            break;

        default: // Padre

            close(p[1]);

            wait(NULL); // Eperamos a que finalice el hijo
            printf("El papi lee en el PIPE ... \n");
            usleep(1000000);
            read(p[0], buffer, SIZE);
            printf("Mensaje del PIPE: %s\n", buffer);
            close(p[0]);

    }
    
}
