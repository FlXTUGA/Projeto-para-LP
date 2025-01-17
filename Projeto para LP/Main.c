#define _CRT_SECURE_NO_WARNINGS
#include "clientes.h"

void menu() {
    printf("\nGestao de Stand Automoveis\n");
    printf(" [1] Inserir Informacao dos Clientes\n");
    printf(" [2] Listar todos os Registos de Clientes inseridos\n");
    printf(" [3] Listar Clientes por tipo de Cliente\n");
    printf(" [4] Gravar Registos de Clientes no Ficheiro\n");
    printf(" [5] Remover Clientes por Número de Registo\n");
    printf(" [6] Ler registos do Ficheiro e Mostrar\n");
    printf(" [7] Ler do Ficheiro, Ordenar, Gravar e Mostrar\n");
    printf(" [8] Calcular o Valor Total de Compras de cada Cliente\n");
    printf(" [0] Sair\n");
    printf("- Escolha uma opcao: ");
}

int main(){
    TCAutomovel clientes[MAX_CLIENTES];
    int contador = 0, opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            InserirCliente(clientes, &contador);
            break;
        case 2:
            ListarCliente(clientes, contador);
            break;
      case 3:
            printf("\nEscolha o tipo de Cliente para listar (0-REGULAR, 1-ESPORADICO, 2-OCASIONAL): ");
            int tipo;
            scanf("%d", &tipo);
            if (tipo < 0 || tipo > 2) {
                printf("\nTipo inválido! Escolha entre 0, 1 ou 2.\n");
            }
            else {
                ListarClientePorTipo(clientes, contador);
            }
            break;
        case 4:
            GravarClientes(clientes, contador, "clientes.bin");
            break;
       case 5:
           printf("Digite o numero de cliente a ser removido: ");
           int numeroCliente;
           scanf("%d", &numeroCliente);
           RemoverClientePorNumero(clientes, &contador, numeroCliente);
           break;
       case 6:
           contador = LerClientes(clientes, "clientes.bin");
           ListarCliente(clientes, contador);
           break;

           break;
       case 7:
           contador = LerClientes(clientes, "clientes.bin");
           ListarClientePorTipo(clientes, contador);
           GravarClientes(clientes, contador, "clientes.bin");
           ListarCliente(clientes, contador);
           break;
       case 8:
           contador = LerClientes(clientes, "clientes.bin");
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
