#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100

typedef enum {
    REGULAR,
    ESPORADICO,
    OCASIONAL,
} TipoCliente;

typedef struct {
    int numerocliente; 
    char nomecliente[50]; 
    char nif[10]; 
    float valor; 
    TipoCliente tipo; 
    char dataregisto[11]; 
} TCAutomovel;


void InsereCliente(TCAutomovel cliente[], int* contador);
void GravarClientes(TCAutomovel clientes[], int contador, const char* nomeFicheiro);
int LerClientes(TCAutomovel cliente[], const char* nomeFicheiro);
void ListarClientes(TCAutomovel consultas[], int contador);
void OrdenarClientesNome(TCAutomovel consultas[], int contador);
int LerClientes(const char* nome_ficheiro, TCAutomovel** vetor);
void OrdenarClientes(TCAutomovel clientes[], int contador, int ordem);
void RemoverClientePorNumero(TCAutomovel clientes[], int* contador, int numerocliente);

