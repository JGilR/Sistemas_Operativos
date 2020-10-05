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
