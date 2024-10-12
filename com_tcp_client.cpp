#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") // Biblioteca Winsock 2

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char server_reply[2000];
    int recv_size;

    printf("\nInicializando Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("Erro ao inicializar Winsock. Código: %d",WSAGetLastError());
        return 1;
    }
    printf("Winsock inicializado.\n");

    // Criando o socket do cliente
    client_socket = socket(AF_INET , SOCK_STREAM , 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Falha ao criar socket: %d" , WSAGetLastError());
    }
    printf("Socket do cliente criado.\n");

    // Configuração do endereço e porta do servidor
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP do servidor (localhost)
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    // Conectar ao servidor
    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Erro ao conectar ao servidor.");
        return 1;
    }
    printf("Conectado ao servidor.\n");

    // Receber resposta do servidor
    if ((recv_size = recv(client_socket, server_reply, 2000, 0)) == SOCKET_ERROR) {
        printf("Falha ao receber resposta.");
    }
    server_reply[recv_size] = '\0';
    printf("Resposta recebida: %s\n", server_reply);

    // Fechar o socket
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
