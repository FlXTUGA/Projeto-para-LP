
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONSULTAS 100

typedef enum {
    REGULAR,
    ESPORADICO,
    OCASIONAL,
} TipoCliente;

typedef struct {
    int numeroCliente;
    char nomeCliente[50];
    char NIF[9];
    float valor;
    TipoCliente tipo;
    char dataRegisto[11];
} TCAutomovel;

// Coisas dos clientes
void InsereCliente(TCAutomovel cliente[], int* contador);
void GravarClientes(TCAutomovel clientes[], int contador, const char* nomeFicheiro);
int LerClientes(TCAutomovel cliente[], const char* nomeFicheiro);
void ListarClientes(TCAutomovel consultas[], int contador);
void OrdenarClientesNome(TCAutomovel consultas[], int contador);
