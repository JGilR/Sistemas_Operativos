## Practica 3
### *Ejercicio 1*

Implementar un programa productor-consumidor mediante tuberías/pipes
donde el proceso hijo genera datos y el proceso padre los consume.

```c
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
```

> Solución:
>- Como ya vimos en el ejemplo, los *pipes* son como tuberías que conectan procesos, así el padre puede obtener datos del hijo y viceversa.
>- En nuestro programa el hijo (productor) escribe un mensaje para el padre (consumidor).
>- Con un *switch* accedemos al hijo y como este es quien escribe, cerramos el descriptor de lectura del *pipe*. Escribimos el mensaje con *write()* y lo copiamos en el *buffer*. Y por últimos cerramos el descriptor de escritura, ya que no vamos a utilizarlo más.
>- En el caso de padre es al revés, cerramos el descriptor de escritura, ya que vamos a leer. Leemos el mensaje con *read()* y lo imprimimos por pantallas, finalmente cerramos el descriptor de lectura.


> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica3/Exit_ejercicio1.png)

### *Ejercicio 2*

El problema del productor-consumidor con buffer limitado (circular):
Planteamiento: 

* El proceso productor produce información y la almacena en un buffer.
* El proceso consumidor accede al buffer y consume la información.
* El productor y el consumidor comparten variables.
* El productor no puede acceder al buffer si está lleno.
* El consumidor no puede acceder al buffer si está vacío. 

![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/ejemplo.PNG)

```c
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
```

> Solución:
>- Hemos realizado el problema productor-consumidor con un buffer inicialmente vacio, en el que el productor produce información, en este caso rellena el buffer con numeros del 0 al 9, y el consumidor los consume, es decir, los pone a 0.
>- Como viene planteado el problema, la funcion *productor* no se ejecuta si el *buffer* está lleno, de lo contrario la función *consumidor* no se ejecuta si el *buffer* está vacío. 
>- En el caso PRODUCTOR: antes de realizar la comprobación de si está vacío o no ponemos el semáforo a "rojo" (0) con *sem_wait()*. Solo volverá a "verde" (1) cuando se haya realizado la función *produce_info()*.
>- En el caso CONSUMIDOR: antes de realizar la comprobación de si está lleno o no ponemos el semáforo a "rojo" (0) con *sem_wait()*. Solo volverá a "verde" (1) cuando se haya realizado la función *consume_info()*.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica3/Exit_ejercicio2.png)

>- Este ejercicio se realiza con semáforos ya que si no, los procesos se entrelazarian, es decir, las funciones se ejecutarían al mismo tiempo dejandonos un resultado como este:

> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica3/Exit_ejercicio2_fail.png)

