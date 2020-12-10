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

            wait(NULL); // Eperamos a que finalize el hijo
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
