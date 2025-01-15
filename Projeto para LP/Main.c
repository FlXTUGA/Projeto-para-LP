#include "cliente.h"

void menu() {
    printf("\nGestao de Stand Automoveis\n");
    printf(" [1] Inserir Informacao dos Clientes\n");
    printf(" [2] Listar todos os Registos de Clientes inseridos\n");
    printf(" [3] Listar Clientes por tipo de Cliente\n");
    printf(" [4] Gravar Registos de Clientes no Ficheiro\n");
    printf(" [5] Carregar Registos de Clientes do Ficheiro\n");
    printf(" [6] Ordenar Clientes\n");
    printf(" [7] Ler do Ficheiro, Ordenar, Gravar e Mostrar\n");
    printf(" [8] Calcular o Valor Total de Compras de cada Cliente\n");
    printf(" [0] Sair\n");
    printf("- Escolha uma opcao: ");
}

int main() {
    TCAutomovel clientes[MAX_CLIENTES];
    int contador = 0, opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            InsereCliente(clientes, &contador);
            break;
        case 2:
            ListarClientes(clientes, contador);
            break;
        case 3:
            printf("\nEscolha o tipo de Cliente para listar (0-REGULAR, 1-ESPORADICO, 2-OCASIONAL): ");
            int tipo;
            scanf("%d", &tipo);
            if (tipo < 0 || tipo > 2) {
                printf("\nTipo inválido! Escolha entre 0, 1 ou 2.\n");
            }
            else {
                ListarClientesPorTipo(clientes, contador, (TipoCliente)tipo);
            }
            break;
        case 4:
            GravarClientes(clientes, contador, "clientes.bin");
            break;
        case 5:
            contador = LerClientes(clientes, "clientes.bin");
            if (contador > 0) {
                printf("\nClientes carregados com sucesso. Total: %d\n", contador);
            }
            else {
                printf("\nErro ao carregar clientes ou arquivo vazio.\n");
            }
            break;
        case 6:
            printf("\nEscolha a ordem (0 - Crescente, 1 - Decrescente): ");
            int ordem;
            scanf("%d", &ordem);
            if (ordem != 0 && ordem != 1) {
                printf("\nOpcao invalida. Escolha 0 para crescente ou 1 para decrescente.\n");
            }
            else {
                OrdenarClientes(clientes, contador, ordem);
            }
            break;
        case 7:
            LerOrdenarGravarMostrar(clientes, &contador, "clientes.bin");
            break;
        case 8:
            CalcularValorTotal(clientes, contador);
            break;
        case 0:
            printf("\nEncerrar...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
