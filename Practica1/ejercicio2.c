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
