#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t recurso1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t recurso2 = PTHREAD_MUTEX_INITIALIZER;

void* processo1(void* arg) {
    pthread_mutex_lock(&recurso1);  // P1 bloqueia o recurso1
    printf("Processo 1 bloqueou o recurso 1\n");

    // Simula algum trabalho
    sleep(1);

    printf("Processo 1 tentando bloquear o recurso 2\n");
    pthread_mutex_lock(&recurso2);  // P1 tenta bloquear o recurso2
    printf("Processo 1 bloqueou o recurso 2\n");

    pthread_mutex_unlock(&recurso2);  // P1 libera o recurso2
    pthread_mutex_unlock(&recurso1);  // P1 libera o recurso1

    return NULL;
}

void* processo2(void* arg) {
    pthread_mutex_lock(&recurso2);  // P2 bloqueia o recurso2
    printf("Processo 2 bloqueou o recurso 2\n");

    // Simula algum trabalho
    sleep(1);

    printf("Processo 2 tentando bloquear o recurso 1\n");
    pthread_mutex_lock(&recurso1);  // P2 tenta bloquear o recurso1
    printf("Processo 2 bloqueou o recurso 1\n");

    pthread_mutex_unlock(&recurso1);  // P2 libera o recurso1
    pthread_mutex_unlock(&recurso2);  // P2 libera o recurso2

    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, processo1, NULL);
    pthread_create(&t2, NULL, processo2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
