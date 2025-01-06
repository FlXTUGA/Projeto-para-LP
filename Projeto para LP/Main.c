#include "cliente.h"

int main() {
    TCAutomovel clientes[MAX_CONSULTAS];
    int contador = 0, opcao;

    do {
        printf("Gestão de Stand Automóveis\n");
        printf("1. Inserir Cliente\n");
        printf("2. Gravar Clientes\n");
        printf("3. Ler e Listar Clientes\n");
        printf("4. Ordenar e Listar Clientes\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            InsereCliente(clientes, &contador);
            break;
        case 2:
            GravarClientes(clientes, contador, "clientes.dat");
            break;
        case 3:
            contador = LerClientes(clientes, "clientes.dat");
            ListarClientes(clientes, contador);
            break;
        case 4:
            OrdenarClientesNome(clientes, contador);
            ListarClientes(clientes, contador);
            break;
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
