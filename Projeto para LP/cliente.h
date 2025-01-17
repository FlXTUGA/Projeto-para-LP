#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>


#define MAX_CLIENTES 100

typedef enum {
	REGULAR,
	ESPORADICO,
	OCASIONAL,

} TipoCliente;

typedef struct {
	int numerocliente;
	char nomecliente[100];
	char nif[10]; // por culpa do \0
	float valor;
	TipoCliente tipo;
	char dataregisto[11];
}TCAutomovel;

void InserirCliente(TCAutomovel cliente[], int* contador);
void ListarCliente(TCAutomovel clientes[], int *contador);
int LerClientes(TCAutomovel clientes[], const char* nomeFicheiro);
void ListarClientePorTipo(TCAutomovel cliente[], int *contador);
void GravarClientes(TCAutomovel clientes[], const char* nomeFicheiro);
void OrdenarClientes(TCAutomovel clientes[], int contador, int ordem);
void RemoverClientePorNumero(TCAutomovel cliente[], int* contador, int numerocliente);
void CalcularValorTotal(TCAutomovel cliente[], int contador);
