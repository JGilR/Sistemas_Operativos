#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_t  h1;
pthread_t  h2;

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
    pthread_create(&h1, NULL, thread, (void *)num1);
    pthread_create(&h2, NULL, thread, (void *)num2);
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
}
