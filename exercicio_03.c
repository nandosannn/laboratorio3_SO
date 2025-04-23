#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10


int shared_sum = 0;

typedef struct {
    int value;
} thread_data;

void *add_to_sum(void *arg) {
    thread_data *data = (thread_data *)arg;
    shared_sum += data->value;  
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N-1];
    thread_data thread_args[N-1];


    shared_sum = 0;

    for (int i = 1; i < N; i++) {
        thread_args[i-1].value = i;
        int rc = pthread_create(&threads[i-1], NULL, add_to_sum, (void *)&thread_args[i-1]);
        
        if (rc) {
            printf("Erro ao criar thread %d; código: %d\n", i, rc);
            exit(-1);
        }
    }

    for (int i = 0; i < N-1; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Sou a thread principal e a soma é %d.\n", shared_sum);

    return 0;
}