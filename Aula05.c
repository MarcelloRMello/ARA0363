#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>

void exibirDataHoraAtual() {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    char buffer[80];

    // Formatação da data e hora no formato brasileiro
    strftime(buffer, 80, "%A, %d de %B de %Y, %H:%M:%S", tempoLocal);
    printf("Data e hora atuais: %s\n", buffer);
}

void exibirDataHoraUTC() {
    time_t agora = time(NULL);
    struct tm *tempoUTC = gmtime(&agora);
    char buffer[80];

    // Formatação da data e hora no formato brasileiro (UTC)
    strftime(buffer, 80, "%A, %d de %B de %Y, %H:%M:%S", tempoUTC);
    printf("Data e hora em UTC: %s\n", buffer);
}

void calcularTempoDecorrido() {
    time_t inicio, fim;
    double tempoDecorrido;

    inicio = time(NULL);
    printf("Pressione ENTER para parar o temporizador...\n");
    getchar();
    fim = time(NULL);

    tempoDecorrido = difftime(fim, inicio);
    printf("Tempo decorrido: %.2f segundos\n", tempoDecorrido);
}

void adicionarIntervaloDeTempo() {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    char buffer[80];

    // Exibe a data e hora atuais
    strftime(buffer, 80, "%A, %d de %B de %Y, %H:%M:%S", tempoLocal);
    printf("Data e hora atuais: %s\n", buffer);

    // Adicionando 5 dias à data atual
    tempoLocal->tm_mday += 5;

    time_t novoTempo = mktime(tempoLocal);
    strftime(buffer, 80, "%A, %d de %B de %Y, %H:%M:%S", localtime(&novoTempo));
    printf("Data e hora após 5 dias: %s\n", buffer);
}

void formatarDataHora() {
    time_t agora = time(NULL);
    struct tm *tempoLocal = localtime(&agora);
    char buffer[80];

    // Formatação personalizada da data e hora no formato brasileiro
    strftime(buffer, 80, "Hoje é %A, %d de %B de %Y, %H:%M:%S", tempoLocal);
    printf("Data e hora formatadas: %s\n", buffer);
}

int main() {
    // Configura o local para português do Brasil
    setlocale(LC_TIME, "pt_BR.UTF-8");

    setenv("TZ", "America/Sao_Paulo", 1);
    tzset();  // Aplica a configuração de fuso horário

    int opcao;

    do {
        printf("\nMenu de Operações com Tempo\n");
        printf("1. Exibir Data e Hora Atuais\n");
        printf("2. Exibir Data e Hora no Formato UTC\n");
        printf("3. Calcular Tempo Decorrido\n");
        printf("4. Adicionar Intervalo de Tempo à Data Atual\n");
        printf("5. Formatador de Data e Hora\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Captura o ENTER após a escolha

        switch(opcao) {
            case 1:
                exibirDataHoraAtual();
                break;
            case 2:
                exibirDataHoraUTC();
                break;
            case 3:
                calcularTempoDecorrido();
                break;
            case 4:
                adicionarIntervaloDeTempo();
                break;
            case 5:
                formatarDataHora();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 6);

    return 0;
}
