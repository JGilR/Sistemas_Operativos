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
