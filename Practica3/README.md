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

![Image of capture](https://raw.githubusercontent.com/JGilR/Sistemas_Operativos/main/ejemplo.PNG)
