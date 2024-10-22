#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;
int saldo = 100;

void* atualizarSaldo(void* arg) {
    pthread_mutex_lock(&lock);  // Bloqueia o mutex
    int temp = saldo;
    temp -= 10;  // Modifica o saldo
    saldo = temp;
    printf("Saldo atualizado: %d\n", saldo);
    pthread_mutex_unlock(&lock);  // Desbloqueia o mutex
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);  // Inicializa o mutex
    pthread_create(&t1, NULL, atualizarSaldo, NULL);
    pthread_create(&t2, NULL, atualizarSaldo, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);  // Destroi o mutex
    return 0;
}
