#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int buffer = 0;  // Inicialmente, o buffer está vazio

void* produtor(void* arg) {
    pthread_mutex_lock(&lock);  // Bloqueia o mutex
    buffer = 1;  // Produz um item
    printf("Produtor produziu um item\n");
    pthread_cond_signal(&cond);  // Sinaliza o consumidor
    pthread_mutex_unlock(&lock);  // Desbloqueia o mutex
    return NULL;
}

void* consumidor(void* arg) {
    pthread_mutex_lock(&lock);  // Bloqueia o mutex
    while (buffer == 0) {
        pthread_cond_wait(&cond, &lock);  // Espera o sinal do produtor
    }
    printf("Consumidor consumiu o item\n");
    buffer = 0;
    pthread_mutex_unlock(&lock);  // Desbloqueia o mutex
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&t1, NULL, consumidor, NULL);
    pthread_create(&t2, NULL, produtor, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
