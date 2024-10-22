#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Cria um novo processo
    
    if (pid == 0) {
        // Código executado pelo processo filho
        printf("Processo filho. PID: %d\n", getpid());
    } else {
        // Código executado pelo processo pai
        printf("Processo pai. PID: %d\n", getpid());
    }

    int fd[2];  // Descritores de arquivo
    pipe(fd);   // Cria o pipe

    if (fork() == 0) {
        close(fd[0]);  // Fecha a leitura
        write(fd[1], "Mensagem", 9);  // Escreve no pipe
    } else {
        close(fd[1]);  // Fecha a escrita
        char buffer[10];
        read(fd[0], buffer, 9);  // Lê do pipe
        printf("Pai leu: %s\n", buffer);
    }

    return 0;
}

int sockfd, newsockfd;
listen(sockfd, 5);
while ((newsockfd = accept(sockfd, NULL, NULL))) {
    if (fork() == 0) {
        // Processo filho trata a conexão
        close(sockfd);  // Fecha o socket no processo filho
        // Lida com a conexão
        exit(0);  // Finaliza o processo filho
    } else {
        close(newsockfd);  // Fecha o socket no processo pai
    }
}
