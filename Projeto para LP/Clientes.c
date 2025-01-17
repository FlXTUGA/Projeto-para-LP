#define _CRT_SECURE_NO_WARNINGS
#include "clientes.h"

int validarData(const char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; 
    }
    if (mes < 1 || mes > 12) {
        return 0;
    }
    if (ano < 1990) {
        return 0;
    }
    int diasPorMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
        diasPorMes[2] = 29; // Fevereiro ano bissexto
    }
    if (dia < 1 || dia > diasPorMes[mes]) {
        return 0;
    }
    return 1;
}
int validarNIF(const char* nif) {
    if (strlen(nif) != 9) return 0;

    for (int i = 0; i < 8; i++) {
        if (nif[i] < '0' || nif[i] > '9') return 0;
    }
    int soma = 0;
    for (int i = 0; i < 8; i++) {
        soma += (nif[i] - '0') * (9 - i);
    }
    int resto = soma % 11;
    int digcontrol = 0;

    if (resto < 2) {
        digcontrol = 0;
    }
    else {
        digcontrol = 11 - resto;
    }
    return digcontrol == (nif[8] - '0');
}

void InserirCliente(TCAutomovel cliente[], int* contador) {


	if (*contador < MAX_CLIENTES) {
		TCAutomovel novocliente;
		novocliente.numerocliente = *contador + 1;

		printf("Nome do Cliente: ");
		scanf("%s", novocliente.nomecliente);
		fseek(stdin, 0, SEEK_END);
		printf("Valor total da Compra: ");
		scanf("%f", &novocliente.valor);
        fseek(stdin, 0, SEEK_END);
        while(novocliente.valor < 0){
			printf("Valor invaldio, insira outro valor: ");
		} 

        do {
            printf("Data (DD/MM/AA): ");
            scanf("%10s", novocliente.dataregisto);
            if (validarData(novocliente.dataregisto)) {
                break;
            }
            printf("Data invalida. Porfavor insira novamente");
        } while (1);

        int nifvalido = 0;

        do {
            printf("NIF: ");
            scanf("%s", novocliente.nif);
            nifvalido = validarNIF(novocliente.nif);
            if (!nifvalido) {
                printf("\n NIF invaldio. Insira novamente.\n");
            }
        } while (!nifvalido);

        printf("Tipo de Cliente:");
        printf("\n0 - Regular\n");
        printf("1 - Esporadico\n");
        printf("2 - Ocasional\n");
        scanf("%d", &novocliente.tipo);

        cliente[*contador] = novocliente;
        (*contador)++;
        printf("%d º cliente adicionado com sucesso", novocliente.numerocliente);
    }
}

void GravarClientes(TCAutomovel clientes[], int contador, const char* nomeFicheiro) {
    if (contador <= 0) {
        printf("Nenhum cliente para gravar\n");
        exit(1);
    }

    if (clientes == NULL) {
        printf("Erro ponteiro de clientes é nulo\n");
    }

    FILE* fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro\n");
        exit(1);
    }

    if (fwrite(&contador, sizeof(int), 1, fp) != 1) {
        printf("Erro ao gravar no ficheiro\n");
        fclose(fp);
        exit(1);
    }
    if (fwrite(clientes, sizeof(TCAutomovel), contador, fp) != contador) {
        printf("Erro ao gravar o cliente no ficheiro\n");
        fclose(fp);
        exit(1);
    }
    fclose(fp);
    printf("----------------------------");
    printf("\nCliente gravado com sucesso!\n");
    printf("----------------------------\n");
}

int LerClientes(TCAutomovel clientes[], const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "rb");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro\n");
        fclose(fp);
        return 0;
    }
    int contador;
    if (fread(&contador, sizeof(int), 1, fp) != 1) {
        printf("Erro ao ler do ficheiro\n");
        fclose(fp);
        return 0;
    }
    if (fread(clientes, sizeof(TCAutomovel), contador, fp) != contador) {
        printf("Erro ao ler do ficheiro\n");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return contador;
}

void ListarCliente(TCAutomovel clientes[], int contador) {
    for (int i = 0; i < contador; i++) {
        printf("\n----------------------------");
        printf("\n          Cliente %d        \n", i + 1);
        printf("------------------------------\n");
        printf("Nome:  %s\n", clientes[i].nomecliente);
        printf("Data:  %s\n", clientes[i].dataregisto);
        printf("NIF:   %s\n", clientes[i].nif);
        printf("Valor: %.2f\n", clientes[i].valor);
        printf("Tipo:  ");
        if (clientes[i].tipo == REGULAR) {
            printf("Regular\n");
        }
        else if (clientes[i].tipo == ESPORADICO) {
            printf("Esporadico\n");
        }
        else if (clientes[i].tipo == OCASIONAL) {
            printf("Ocasional\n");
        }
    }
}

void ListarClientePorTipo(TCAutomovel clientes[], int contador) {
    for (int i = 0; i < contador; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (clientes[i].tipo > clientes[j].tipo) {
                TCAutomovel temp = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = temp;
            }
        }
    }
    printf("Clientes ordenados por Tipo\n");
    ListarCliente(clientes, contador);
}

void RemoverClientePorNumero(TCAutomovel clientes[], int *contador, int numerocliente) {

    int i, encontrado = 0;
    for (i = 0; i < *contador; i++) {
        if (clientes[i].numerocliente == numerocliente) {
            for (int j = i; j < *contador - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            (*contador)--;
            printf("Cliente %d removido com sucesso\n", numerocliente);
            encontrado = 1;
            break;
        }
    }
  if (!encontrado) {
        printf("Cliente com numero %d nao encontrado", numerocliente);
  }
}

void CalcularValorTotal(TCAutomovel clientes[], int contador) {
    if (contador == 0) {
        printf("Nenhum cliente registrado");
        exit(1);
    }
    printf("Valor Total de Compras por Cliente:\n");
    for (int i = 0; i < contador; i++) {
        printf("---------------------------");
        printf("\nCliente %s: %.2f euros\n",clientes[i].nomecliente, clientes[i].valor);
        printf("\n---------------------------\n");
    }
}
