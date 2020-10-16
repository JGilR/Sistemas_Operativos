# Sistemas_Operativos
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
