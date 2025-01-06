#include "cliente.h"

void InsereCliente(TCAutomovel cliente[], int* contador) {
    if (*contador < MAX_CONSULTAS) {
        TCAutomovel novoCliente;
        printf("Nome do Cliente: ");
        scanf("%s", novoCliente.nomeCliente);

        printf("Valor total das Compras: ");
        scanf("%f", &novoCliente.valor);

        printf("Insira a data de registo (DD/MM/YYYY): ");
        scanf("%s", novoCliente.dataRegisto);

        int NIFvalido = 0;
        while (!NIFvalido) {
            printf("NIF: ");
            scanf("%s", novoCliente.NIF);
            NIFvalido = validarNIF(novoCliente.NIF);
            if (!NIFvalido) {
                printf("NIF inválido. Insira novamente.\n");
            }
        }

        printf("Tipo de Cliente (introduza o número):\n 0 - Regular\n 1 - Esporádico\n 2 - Ocasional\n");
        scanf("%d", &novoCliente.tipo);

        cliente[*contador] = novoCliente;
        (*contador)++;
        printf("Cliente adicionado com sucesso!\n");
    }
    else {
        printf("Limite de clientes atingido!\n");
    }
}

void GravarClientes(TCAutomovel clientes[], int contador, const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "wb");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    fwrite(&contador, sizeof(int), 1, fp);
    fwrite(clientes, sizeof(TCAutomovel), contador, fp);
    fclose(fp);
    printf("Dados gravados com sucesso!\n");
}

int LerClientes(TCAutomovel cliente[], const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "rb");
    if (!fp) {
        printf("Erro ao abrir o ficheiro.\n");
        return 0;
    }
    int contador = 0;
    fread(&contador, sizeof(int), 1, fp);
    fread(cliente, sizeof(TCAutomovel), contador, fp);
    fclose(fp);
    return contador;
}

void ListarClientes(TCAutomovel consultas[], int contador) {
    for (int i = 0; i < contador; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", consultas[i].nomeCliente);
        printf("NIF: %s\n", consultas[i].NIF);
        printf("Valor: %.2f\n", consultas[i].valor);
        printf("Tipo: %d\n", consultas[i].tipo);
        printf("Data: %s\n", consultas[i].dataRegisto);
        printf("------------------------------\n");
    }
}

void OrdenarClientesNome(TCAutomovel consultas[], int contador) {
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (strcmp(consultas[i].nomeCliente, consultas[j].nomeCliente) > 0) {
                TCAutomovel temp = consultas[i];
                consultas[i] = consultas[j];
                consultas[j] = temp;
            }
        }
    }
    printf("Clientes ordenados por nome.\n");
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
    return (11 - resto) == (nif[8] - '0');
}