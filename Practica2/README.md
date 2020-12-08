## Practica 2
### *Ejercicio 1*

Implementar un programa que reciba dos números enteros como parámetros de
entrada y calcule sus factoriales de forma concurrente utilizando dos hilos que
se ejecutan en paralelo con el hilo principal. El hilo principal deberá esperar a que
terminen los otros dos hilos.

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t  h1;
pthread_t  h2;
pthread_t  thmain;

int num1 = 3, num2 = 5;

void *thread(void *arg){
    int *num;
    num = (int *)arg;

    int fact = factorial(num);
    printf("El factorial de %d es: %d\n", num, fact);
    pthread_exit(NULL);
}

int factorial(int n){
    int fact = 1;
    if(n < 0){
        return -1;
    }else{
        for(int i = 1; i <= n; i++){
            fact *= i;
        }
    }
    return fact;
}



int  main(int  argc , char *argv []) {
    thmain = pthread_self();
    pthread_create(&h1, NULL, thread, (void *)num1);
    pthread_create(&h2, NULL, thread, (void *)num2);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
}
```

> Solución:
>- Primero creamos la función factorial, que nos calcula el factorial de un número.
>- Después creamos una función thread que ejecutará cada uno de los hilos. En cada hilo se realizará la función factorial para un número.
>- En el main creamos los dos hilos correspondientes con *pthread_create*, los parámetros que le pasamos son el propio hilo, los atributos (NULL) que obtiene los atributos normales, la función que queremos que realize y por último le pasamos el número como argumento.


> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica2/Exit_ejercicio1.png)


### *Ejercicio 2*

El programa que se muestra a continuación cuenta el número de veces que el
carácter ’a’ o ’A’ aparece en el fichero indicado como parámetro de entrada.
Modificarlo para que ahora se cree un hilo y sea éste el que ejecute la función de
contar.

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLON 1000

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
    cuenta(argv[1]);
    return 0;
}
```

> Solución:
>- Para modificar el código de arriba, basta con crear un hilo que se encargue de ejecutar la función *cuenta()*. Así obtenemos:

```c
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
```


### *Ejercicio 3*

Generar un programa en C que muestre el funcionamiento de mutex a través de
la creación de un par de threads, donde cada uno escriba su propio mensaje por
la salida estándar de forma sincronizada secuenciando las tareas. 

```c
# include < stdio .h >
# include < stdlib .h >
# include < string .h >
# include < unistd .h >
# include < pthread .h >

void * hola ( void * arg ) {
    char * msg = " Hola ";
    int i;

    for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
        printf (" %c" , msg [ i ]) ;
        fflush ( stdout ) ;
        usleep (1000000) ;
    }
    return NULL ;
}

void * mundo ( void * arg ) {
    char * msg = " mundo ";
    int i;
    
    for ( i = 0 ; i < strlen ( msg ) ; i ++ ) {
        printf (" %c" , msg [ i ]) ;
        fflush ( stdout ) ;
        usleep (1000000) ;
    }
    return NULL ;
}

int main ( int argc , char * argv []) {
    pthread_t h1 ;
    pthread_t h2 ;
    pthread_create (& h1 , NULL , hola , NULL );
    pthread_create (& h2 , NULL , mundo , NULL );
    printf ( " Fin \n ");
}
```

`Este programa lo hemos extraído de https://www.um.es/earlyadopters/actividades/a3/PCD_Activity3_Session1.pdf`

> Solución:
>- Primero hemos extraído un programa simple que escribe "Hola Mundo" con dos hilos distintos, el primero escribe *Hola* y el segundo *Mundo*.
>- Le hemos puesto un delay de 1 segundo para cada letra, para ver como al ejecutarse los dos hilos a la vez, se intercalan las letras.


> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica2/Exit_ejercicio3_holamundo.png)

>- Ahora lo vamos a modificar utilizando el *mutex* para que escriba primero *Hola* y luego *Mundo*.

```c
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
```

> Solución:
>- Primero creamos el mutex *pthread_mutex_t mutex*. Este se encargará de bloquear la función *mundo* y la desbloquearemos cuando se ejecute la función *hola*.
>- Para ello utilizamos *pthread_mutex_lock* y *pthread_mutex_unlock*. Así si nos fijamos en el main primero creamos el hilo para la función mundo y esta se bloquea hasta que se ejecute el siguiente hilo con la función hola.


> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica2/Exit_ejercicio3.png)


