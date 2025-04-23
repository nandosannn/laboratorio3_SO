#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20

typedef struct {
    int n;
    int *fib_sequence;
} thread_data;


void *calculate_fibonacci(void *arg) {
    thread_data *data = (thread_data *)arg;
    int n = data->n;
    int *fib = data->fib_sequence;

    printf("Sou a thread filha, e vou calcular a Sequencia de Fibonacci.\n");

    fib[0] = 0;
    if (n > 0) {
        fib[1] = 1;
    }

    for (int i = 2; i < n + 1; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    pthread_exit(NULL);
}

int main() {
    printf("Sou a thread principal, vou criar uma thread para calcular a Sequencia de Fibonacci.\n");

    int fib_sequence[N+1];
    
    thread_data data;
    data.n = N;
    data.fib_sequence = fib_sequence;

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, calculate_fibonacci, (void *)&data);
    
    if (rc) {
        printf("Erro ao criar thread; código de erro: %d\n", rc);
        exit(-1);
    }

    pthread_join(thread, NULL);

    printf("Sou a thread principal e a thread filha calculou esta sequencia:");
    for (int i = 0; i <= N; i++) {
        printf(" %d", fib_sequence[i]);
    }
    printf(".\n");

    return 0;
}