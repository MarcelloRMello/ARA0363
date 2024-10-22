#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem;
int recursos = 5;

void* usarRecurso(void* arg) {
    sem_wait(&sem);  // Decrementa o semáforo (bloqueia se for 0)
    printf("Processo %d usando recurso\n", *(int*)arg);
    recursos--;
    printf("Recursos restantes: %d\n", recursos);
    sem_post(&sem);  // Incrementa o semáforo (libera o recurso)
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    sem_init(&sem, 0, 2);  // Inicializa o semáforo com valor 2 (permite dois processos simultâneos)
    int id1 = 1, id2 = 2, id3 = 3;
    pthread_create(&t1, NULL, usarRecurso, &id1);
    pthread_create(&t2, NULL, usarRecurso, &id2);
    pthread_create(&t3, NULL, usarRecurso, &id3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    sem_destroy(&sem);  // Destroi o semáforo
    return 0;
}
