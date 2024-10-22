#include <pthread.h>
#include <stdio.h>

void* func(void* arg) {
    printf("Thread em execução\n");
    return NULL;
}

int main() {
    pthread_t thread;  // Identificador do thread
    pthread_create(&thread, NULL, func, NULL);  // Cria o thread
    pthread_join(thread, NULL);  // Aguarda o thread finalizar
    return 0;
}
