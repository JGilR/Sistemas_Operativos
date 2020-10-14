## Practica 1
### *Ejercicio 1*

Llamada al sistema para la apertura y lectura del fichero “ejemplo” creado en el primer
programa mostrado.

```c
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
	FILE* fichero;
	char lineas[100];
	fichero = fopen("ejemplo", "r");
	
	if(fichero == NULL){
		exit(1);
	}else{
		printf("El contenido es:\n\n");
		while(fgets(lineas, 100, fichero)){
			printf("%s", lineas);
		}
		fclose(fichero);
	}
	return 0;
}
```

> Solución:
>- Unicamente hemos abierto un fichero con la función *fopen()* y hemos realizado un *while* para recorrer cada linea con la función *fgets()* del fichero y mostrarla por pantalla.

> ![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica1/Exit_ejercicio1.png)


### *Ejercicio 2*

Implementar una aplicación concurrente que calcule el cuadrado de los 20 primeros
números naturales y almacene el resultado, repartiendo la tarea entre dos procesos:
Para ello se deben crear dos procesos Hijos: 
- Hijo1 realiza la operación sobre los números pares. 
- Hijo2 realiza la operación sobre los números impares. 

El proceso padre espera la terminación de los hijos, ‘obtiene’ el resultado de cada hijo
y muestra los valores ordenados en pantalla.

```c
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

int main(void)
{
    int result1[20], result2[20];

    pid_t pid1, pid2;
    int status1, status2;

    if((pid1=fork()) == 0){
        printf("Soy el primer hijo(%d, hijo de %d)\n", getpid(), getppid());
        for(int i=1; i<=20; i++){
            if((i % 2) == 0){
                printf("%d - ", i*i);
                result1[i] = i*i;
            }
        }
        printf("\n");
    }else{
        if((pid2=fork()) == 0){
            printf("Soy el segundo hijo(%d, hijo de %d)\n", getpid(), getppid());
            for(int i=1; i<=20; i++){
                if((i % 2) != 0){
                    printf("%d - ", i*i);
                    result2[i] = i*i;
                }
            }
            printf("\n");
        }else{
            waitpid(pid1,&status1,0);
            waitpid(pid2,&status2,0);
            printf("Soy el padre(%d, hijo de %d)\n", getpid(), getppid());
        }
    }
    return 0;
}
```
> Solución:
>- Hemos realizado las operaciones de calcular los cuadrados de los 20 primeros números, los pares para el primer hijo *pid1* y los impares para el segundo hijo *pid2*.
>- Nos hemos dado cuenta de que el padre no puede obtener los array de cada uno de sus hijos, *result1[]* y *result2[]*.
>- Sin embargo descubrimos como pasar variables de un hijo a un padre con *exit()* y el *WEXITSTATUS()*. Lo demostramos con el siguiente programa:

```c
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

#define length(x) (sizeof(x) / sizeof(int))
#define max 10

int main(void)
{
	pid_t pid = fork();
	int array[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int status, sum = 0;

	if(pid == 0){
		for(int i=0; i<20; i++){
			if((i%2) != 0){
					printf("%d + %d\n", sum, array[i]);
					sum = sum + array[i];
			}
		}
		printf("Resultado (sum): %d\n", sum);
		exit(sum);
	}else{
		wait(&status);
		printf("Resultado de pasar variable del hijo al padre: %d \n", WEXITSTATUS(status));

	}

}

```
> Solución:
>- En este programa el hijo *pid* realiza la suma de los 20 primeros numeros naturales y pasamos este resultado *sum* al padre.
>- En el proceso hijo realizamos la operación y sacamos el resultado con *exit(sum)*.
>- Después en el padre esperamos con *wait(&status)* a que termine el proceso hijo y lo imprimimos por pantalla con un *printf* del *WEXITSTATUS(status)*.


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

![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/Practica1/Captura.PNG)
