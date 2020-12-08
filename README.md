<!-- ⚠️ This README has been generated from the file(s) "blueprint.md" ⚠️--><h1 align="center">SISTEMAS OPERATIVOS</h1>

<p align="center">
	<a>
		<img src="https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/sistemasoperativos.jpg"  />
	</a>
</p>
<br />
<details>
<summary>📖 Table of Contents</summary>
<br />

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)

## ➤ Table of Contents

* [➤ Practica 1](#-practica1)
* [➤ Practica 2](#-practica2)
* [➤ Practica 3](#-practica3)

</details>

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#table-of-contents)


## Practica 1
### *Ejercicio 1*

Llamada al sistema para la apertura y lectura del fichero “ejemplo” creado en el primer
programa mostrado.

### *Ejercicio 2*

Implementar una aplicación concurrente que calcule el cuadrado de los 20 primeros
números naturales y almacene el resultado, repartiendo la tarea entre dos procesos:
Para ello se deben crear dos procesos Hijos: 
- Hijo1 realiza la operación sobre los números pares. 
- Hijo2 realiza la operación sobre los números impares. 

El proceso padre espera la terminación de los hijos, ‘obtiene’ el resultado de cada hijo
y muestra los valores ordenados en pantalla.

### *Ejercicio 3*

Observa el siguiente código y escribe la jerarquía de procesos resultante. Ahora
compila y ejecuta el código para comprobarlo. Presta atención al orden de terminación
de los procesos, ¿qué observas? ¿por qué?

```c
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int num;
	pid_t pid;

	srandom(getpid());
	for(num=0; num<3; num++){
		pid=fork();
		printf("Soy el proceso de PID %d y mi padre tiene %d de PID\n", getpid(), getppid());
		if(pid == 0){
			break;
		}
	}
	if(pid==0) 
		sleep(random()%5);
	else 
		for(num=0; num<3; num++){
			printf("Fin del proceso de PID %d.\n", wait (NULL));
		}
	return 0;
}
```

### *Ejercicio 4*

Implementar un código que genere la estructura de procesos de la siguiente figura:

![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica1/JerarquiaProcessEjemplo.PNG)


[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#-practica1)


## Practica 2
### *Ejercicio 1*

Implementar un programa que reciba dos números enteros como parámetros de
entrada y calcule sus factoriales de forma concurrente utilizando dos hilos que
se ejecutan en paralelo con el hilo principal. El hilo principal deberá esperar a que
terminen los otros dos hilos.

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

### *Ejercicio 3*

Generar un programa en C que muestre el funcionamiento de mutex a través de
la creación de un par de threads, donde cada uno escriba su propio mensaje por
la salida estándar de forma sincronizada secuenciando las tareas. 

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#-practica2)


## Practica 3
### *Ejercicio 1*

Implementar un programa productor-consumidor mediante tuberías/pipes
donde el proceso hijo genera datos y el proceso padre los consume.

### *Ejercicio 2*

El problema del productor-consumidor con buffer limitado (circular):
Planteamiento: 

* El proceso productor produce información y la almacena en un buffer.
* El proceso consumidor accede al buffer y consume la información.
* El productor y el consumidor comparten variables.
* El productor no puede acceder al buffer si está lleno.
* El consumidor no puede acceder al buffer si está vacío. 

![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/ejemplo.png)

[![-----------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png)](#-practica3)

