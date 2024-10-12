#include <Windows.h>
#include <stdio.h>
	
int main(void)
{
HANDLE hComm;                          
char  ComPortName[] = "COM5";  	//Nome da porta a ser aberta.
BOOL  Status;                          		// Estado de operaçãoes 
DWORD dwEventMask;          		// Máscara de Evento para capturar
	char  TempChar;                        // Caracter temporºario
	char  SerialBuffer[2560];            	// Buffer Contendo  dados recebidos
	DWORD NoBytesRead;             	// Bytes lidos pela função ReadFile()
		int i = 0;
		char c;

printf("\n\n +====================================+");
printf("\n |                 Recepcao por porta serial                             |");
printf("\n +===================================+\n");


	/*--------- Abrindo a porta serial -------------*/
			
hComm = CreateFile( ComPortName,     // Nome da porta
GENERIC_READ | GENERIC_WRITE, 	// Modo Leitura/Escrita
0,       					// Sem compartilhamento 
NULL,       					// Sem segurança
OPEN_EXISTING,                		//Abre somente a porta existente
0,                            			// Sem sobreposição de E/S
NULL);                        			// Null para porta serial

if (hComm == INVALID_HANDLE_VALUE)
printf("\n    Erro! - Porta %s nao pode ser aberta\n", ComPortName);
else
printf("\n    Porta %s aberta\n ", ComPortName);


	/*--- Ajustando os parâmetros para porta serial -----*/

DCB dcbSerialParams = { 0 };          // Inicializando a estrutura DCB 
dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

Status = GetCommState(hComm, &dcbSerialParams);      //Recebendo o estado atual

if (Status == FALSE)
printf("\n    Erro em GetCommState()");

// Ajustando BaudRate = 115200
dcbSerialParams.BaudRate = CBR_115200;
// Ajustando StopBits = 1      
dcbSerialParams.StopBits = ONESTOPBIT;
// Tamanho do byte = 8 dados
dcbSerialParams.ByteSize = 8;             
// Ajustando sem paridade
dcbSerialParams.Parity = NOPARITY;        

Status = SetCommState(hComm, &dcbSerialParams);  //Configurando a porta de acordo com os ajustes em DCB 

		if (Status == FALSE)
		{
		printf("\n    Erro em ajustar estrtura DCB");
		}
		else 		//Se houve sucesso, mostra os valores ajustados
		{
		//printf("\n\n    Setting DCB Structure Successfull\n");
		printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
		printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
		printf("\n       StopBits = %d", dcbSerialParams.StopBits);
		printf("\n       Parity   = %d", dcbSerialParams.Parity);
		}

		/*------Ajustando Timeouts --------------*/
			
		COMMTIMEOUTS timeouts = { 0 };
		timeouts.ReadIntervalTimeout         = 50;
		timeouts.ReadTotalTimeoutConstant    = 50;
		timeouts.ReadTotalTimeoutMultiplier  = 10;
		timeouts.WriteTotalTimeoutConstant   = 50;
		timeouts.WriteTotalTimeoutMultiplier = 10;
			
		if (SetCommTimeouts(hComm, &timeouts) == FALSE)
		printf("\n\n    Erro em ajustar TimeOuts");


	/*---------Ajustando a máscara para receber -----------------*/
			
//Configura Windows para Monitorar a porta serial
Status = SetCommMask(hComm, EV_RXCHAR); 
	
		if (Status == FALSE)
		printf("\n\n    Erro! em ajustar CommMask");
		else
		printf("\n\n    Aguardando recepcao de dados\n\n...   ");

		while (1){ 
  			
/*------------Ajustando evento WaitComm() -------*/
Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Aguarda por caractere
	
/*--------Programa aguarda aqui até o caractere ser recebido------------*/				

	if (Status == FALSE)
	{
	printf("\n    Erro ao ajustar WaitCommEvent()");
	}
	else //SE  WaitCommEvent()==True Lê a string com ReadFile();
	{

	i=0;
	do
	{
    Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
    SerialBuffer[i] = TempChar;
    i++;
  }
	while (NoBytesRead > 0);

	/*------------Imprime a string lida----------------------*/
	printf("\n    ");
	int j =0;
	for (j = 0; j < i-1; j++)		// j < i-1 para remover o último caractere duplicado
	  printf("%c", SerialBuffer[j]);
	}	
			
	}
	CloseHandle(hComm);		//Fecha a porta serial
	printf("\n +==========================================+\n");
	//getch();
	}

