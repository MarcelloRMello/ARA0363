#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link para a biblioteca Winsock

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_count = 0; // Contador de clientes que receberam a mensagem
    int c;
    char *message;

    // Inicializar Winsock
    printf("Inicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Falha na inicializacao. Erro: %d\n", WSAGetLastError());
        return 1;
    }
    
    // Criar socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Erro ao criar socket: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Socket criado.\n");

    // Preparar a estrutura sockaddr_in
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Vincular
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Erro ao vincular socket: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Vinculacao feita.\n");

    // Colocar o servidor em modo de escuta
    listen(server_socket, 3);

    printf("Aguardando conexoes...\n");
    c = sizeof(struct sockaddr_in);

    // Loop infinito para enviar mensagens para os clientes
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client, &c);
        if (client_socket == INVALID_SOCKET) {
            printf("Falha ao aceitar conexao: %d\n", WSAGetLastError());
            continue; // Voltar para o início do loop e aguardar uma nova conexão
        }

        printf("Conexao aceita.\n");
        client_count++; // Incrementar o contador de clientes

        // Criar a mensagem com o número de clientes atendidos
        char buffer[1024];
        sprintf(buffer, "Ola, cliente! Voce e o cliente numero %d a receber esta mensagem.\n", client_count);
        message = buffer;

        // Enviar a mensagem para o cliente
        send(client_socket, message, strlen(message), 0);

        // Fechar o socket do cliente após enviar a mensagem
        closesocket(client_socket);
    }

    // Fechar o socket do servidor (nunca chegaremos aqui por causa do loop infinito)
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
