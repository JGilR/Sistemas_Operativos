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
