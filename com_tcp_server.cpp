#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") // Linka a biblioteca Winsock

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int c;
    const char *message; // Variável const para armazenar string literal

    printf("\nInicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("Erro ao inicializar Winsock. Código: %d", WSAGetLastError());
        return 1;
    }
    printf("Winsock inicializado.\n");

    // Criando o socket do servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Falha ao criar socket: %d" , WSAGetLastError());
        return 1;
    }
    printf("Socket do servidor criado.\n");

    // Configuração do endereço e porta do servidor
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind (associar o socket à porta)
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Erro no bind: %d" , WSAGetLastError());
        return 1;
    }
    printf("Bind feito.\n");

    // Ouvir por conexões
    listen(server_socket, 3);
    printf("Aguardando por conexões...\n");

    // Aceitar conexões de entrada
    c = sizeof(struct sockaddr_in);
    client_socket = accept(server_socket, (struct sockaddr *)&client, &c);
    if (client_socket == INVALID_SOCKET) {
        printf("Falha ao aceitar conexão: %d" , WSAGetLastError());
        return 1;
    }
    printf("Conexão aceita.\n");

    // Enviar mensagem ao cliente
    message = "Olá, cliente!\n";
    send(client_socket, message, strlen(message), 0);
    printf("Mensagem enviada ao cliente.\n");

    // Fechar o socket
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
