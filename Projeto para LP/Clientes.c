#define _CRT_SECURE_NO_WARNINGS
#include "cliente.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarData(const char* data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0; //a data está no formato errado
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

void CarregarClientes(TCAutomovel clientes[], int* numClientes, const char* nomeFicheiro) {
    FILE* arquivo = fopen(nomeFicheiro, "rb");
    *numClientes = fread(clientes, sizeof(TCAutomovel), MAX_CLIENTES, arquivo);
    fclose(arquivo);
}

void InsereCliente(TCAutomovel cliente[], int* contador) {
    if (*contador < MAX_CLIENTES) {
        TCAutomovel novocliente;
        novocliente.numerocliente = *contador + 1;

        printf("Nome do Cliente: "); //colocar q ter um nome valido (so chars e nao int)
        scanf("%s", novocliente.nomecliente);
        fseek(stdin, 0, SEEK_END);
        printf("Valor total das Compras: "); //coloca compras >0 
        scanf("%f", &novocliente.valor);
        fseek(stdin, 0, SEEK_END);
        do {
            printf("Data (DD/MM/AAAA): ");
            fgets(novocliente.dataregisto, sizeof(novocliente.dataregisto), stdin);
            novocliente.dataregisto[strcspn(novocliente.dataregisto, "\n")] = 0;

            if (!validarData(novocliente.dataregisto)) {
                printf("Data invalida! Por favor, insira novamente.\n");
            }
        } while (!validarData(novocliente.dataregisto));

        int nifvalido = 0;
        while (!nifvalido) {
            printf("NIF: ");
            scanf("%s", novocliente.nif);
            nifvalido = validarNIF(novocliente.nif);
            if (!nifvalido) {
                printf("\nNIF invalido. Insira novamente.\n");
            }
        }

        printf("Tipo de Cliente:\n 0 - Regular\n 1 - Esporadico\n 2 - Ocasional\n- Introduza o numero: ");
        scanf("%d", &novocliente.tipo);

        cliente[*contador] = novocliente;
        (*contador)++;
        printf("\nCliente adicionado com sucesso!\n");
    }
    else {
        printf("\nLimite de clientes atingido!\n");
    }
}
void GravarClientes(TCAutomovel clientes[], int contador, const char* nomeFicheiro) {
    if (contador <= 0) {
        printf("Nenhum cliente para gravar.\n");
        return;
    }
    FILE* fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro\n");
        exit(1);
    }
    if (fwrite(&contador, sizeof(int), 1, fp) != 1) {
        printf("Erro ao escrever no ficheiro\n");
        exit(1);
    }
    if (fwrite(clientes, sizeof(TCAutomovel), contador, fp) != contador) {
        printf("Erro ao escrever no ficheiro\n");
        exit(1);
    }
    fclose(fp);
    printf("Cliente gravado com sucesso!\n");
    printf("------------------------------\n");
}

int LerClientes(TCAutomovel cliente[], const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "rb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return 0;
    }
    int contador = 0;
    if (fread(&contador, sizeof(int), 1, fp) != 1) {
        printf("Erro ao ler o contador ou o arquivo esta vazio.\n");
        return 0;
    }
    printf("Numero de clientes carregados: %d\n", contador); // Verificação
    if (contador > 0) {
        fread(cliente, sizeof(TCAutomovel), contador, fp);
    }
    fclose(fp);
    return contador;
}

void MostrarClientes(TCAutomovel cliente) {
    printf("\n------------------------------\n");
    printf("Nome: %s\n", cliente.nomecliente);
    printf("NIF: %s\n", cliente.nif);
    printf("Valor: %.2f\n", cliente.valor);
    printf("Tipo: ");
    switch (cliente.tipo) {
    case REGULAR:
        printf("Regular\n");
        break;
    case ESPORADICO:
        printf("Esporádico\n");
        break;
    case OCASIONAL:
        printf("Ocasional\n");
        break;
    default:
        printf("Tipo desconhecido\n");
        break;
    }
    printf("Data: %s\n", cliente.dataregisto);
    printf("------------------------------\n");
}

void ListarClientes(TCAutomovel consultas[], int contador) {
    for (int i = 0; i < contador; i++) {
        printf("\n------------------------------\n");
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", consultas[i].nomecliente);
        printf("NIF: %s\n", consultas[i].nif);
        printf("Valor: %.2f\n", consultas[i].valor); //biblioteca pa add €
        printf("Tipo:");
        if (consultas[i].tipo == REGULAR) {
            printf("Regular\n");
        }
        else if (consultas[i].tipo == ESPORADICO) {
            printf("Esporadico\n");
        }
        else if (consultas[i].tipo == OCASIONAL) {
            printf("Ocasional\n");
        }
        printf("Data: %s\n", consultas[i].dataregisto);
        printf("------------------------------\n");
    }
}

void ListarClientesPorTipo(TCAutomovel clientes[], int contador, TipoCliente tipo) {
    int encontrado = 0;

    for (int i = 0; i < contador; i++) {
        if (clientes[i].tipo == tipo) {
            printf("\n------------------------------\n");
            printf("Cliente %d:\n", clientes[i].numerocliente);
            printf("Nome: %s\n", clientes[i].nomecliente);
            printf("NIF: %s\n", clientes[i].nif);
            printf("Valor: %.2f\n", clientes[i].valor);
            printf("Tipo: ");
            if (clientes[i].tipo == REGULAR) {
                printf("Regular\n");
            }
            else if (clientes[i].tipo == ESPORADICO) {
                printf("Esporadico\n");
            }
            else if (clientes[i].tipo == OCASIONAL) {
                printf("Ocasional\n");
            }
            printf("Data: %s\n", clientes[i].dataregisto);
            printf("------------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("\nNenhum cliente encontrado para o tipo selecionado.\n");
    }
}

void OrdenarClientesTipo(TCAutomovel consultas[], int contador) {
    for (int i = 0; i < contador - 1; i++) {
        for (int j = i + 1; j < contador; j++) {
            if (consultas[i].tipo > consultas[j].tipo) {
                TCAutomovel temp = consultas[i];
                consultas[i] = consultas[j];
                consultas[j] = temp;
            }
        }
    }
    printf("Clientes ordenados por tipo.\n");
    ListarClientes(consultas, contador);
}

int LerClientes(TCAutomovel cliente[], const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "rb"); 
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro '%s'.\n", nomeFicheiro);
        return 0; 
    }

    int contador = 0; // Inicializa o contador 

    // cliente armazenados no arquivo
    if (fread(&contador, sizeof(int), 1, fp) != 1) {
        printf("Erro ao ler o contador ou o arquivo está vazio.\n");
        fclose(fp);
        return 0;
    }

    // Le os registros de clientes para o vetor
    if (fread(cliente, sizeof(TCAutomovel), contador, fp) != contador) {
        printf("Erro ao ler os clientes do ficheiro.\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    printf("Clientes carregados com sucesso! Total de clientes: %d\n", contador);
    return contador; 
}

void RemoverClientePorNumero(TCAutomovel clientes[], int* contador, int numerocliente) {
    int i, encontrado = 0;

    for (i = 0; i < *contador; i++) {
        if (clientes[i].numerocliente == numerocliente) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // move os que restam para preencher o espaço
        for (int j = i; j < *contador - 1; j++) {
            clientes[j] = clientes[j + 1];
        }
        (*contador)--; // Decrementa o contador de clientes
        printf("\nCliente com o número %d removido com sucesso!\n", numerocliente);
    }
    else {
        printf("\nCliente com o número %d não encontrado!\n", numerocliente);
    }
}

void CalcularValorTotal(TCAutomovel clientes[], int contador) {
    printf("\nValor Total de Compras de Cada Cliente:\n");
    for (int i = 0; i < contador; i++) {
        printf("Cliente: %s, Valor Total: %.2f\n", clientes[i].nomecliente, clientes[i].valor);
    }
}

void LerOrdenarGravarMostrar(TCAutomovel clientes[], int* contador, const char* nomeFicheiro) {
    *contador = LerClientes(clientes, nomeFicheiro);
    if (*contador > 0) {
        printf("\nClientes carregados com sucesso. Total: %d\n", *contador);
        int ordem;
        printf("Escolha a ordem para ordenacao (0 - Crescente, 1 - Decrescente): ");
        scanf("%d", &ordem);
        OrdenarClientes(clientes, *contador, ordem);
        GravarClientes(clientes, *contador, nomeFicheiro);
        ListarClientes(clientes, *contador);
    }
    else {
        printf("\nErro ao carregar clientes ou arquivo vazio.\n");
    }
}
