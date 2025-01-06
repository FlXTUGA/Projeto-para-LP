#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CONSULTAS 100

typedef struct {
	char nomeDono[50];
	char moradaDono[150];
	float valorConsulta;
	char dataConsulta[20];
	char nomeAnimal[50];
	char especieAnimal[50];
	char racaAnimal[50];
	char tipoConsulta[50];
} Consulta;

int validarData(const char* data) {
	int dia, mes, ano;
	if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
		return 0; // Se a leitura não for bem-sucedida, a data está no formato errado
	}
	if (mes < 1 || mes > 12) {
		return 0; // Mês inválido
	}
	if (ano < 1990) {
		return 0; // Ano inválido (abaixo do limite)
	}

	int diasPorMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))) {
		diasPorMes[2] = 29; // Fevereiro em ano bissexto
	}
	if (dia < 1 || dia > diasPorMes[mes]) {
		return 0; // Dia inválido
	}

	return 1; // Data válida
}


void adicionarConsulta(Consulta consultas[], int* contador) {
	if (*contador < MAX_CONSULTAS) {
		Consulta novaConsulta;

		printf("Nome do dono: ");
		scanf("%s", novaConsulta.nomeDono);
		fgets(novaConsulta.moradaDono, sizeof(novaConsulta.moradaDono), stdin);

		printf("Nome da morada: ");
		fgets(novaConsulta.moradaDono, sizeof(novaConsulta.moradaDono), stdin);

		printf("Valor da consulta: ");
		scanf("%f", &novaConsulta.valorConsulta);
		fgets(novaConsulta.dataConsulta, sizeof(novaConsulta.dataConsulta), stdin);

		do {
			printf("Data da consulta (DD/MM/AAAA): ");
			fgets(novaConsulta.dataConsulta, sizeof(novaConsulta.dataConsulta), stdin);
			novaConsulta.dataConsulta[strcspn(novaConsulta.dataConsulta, "\n")] = 0; // Remover o caractere de nova linha

			if (!validarData(novaConsulta.dataConsulta)) {
				printf("Data invalida! Por favor, insira novamente.\n");
			}
		} while (!validarData(novaConsulta.dataConsulta));

		printf("Nome do animal: ");
		fgets(novaConsulta.nomeAnimal, sizeof(novaConsulta.nomeAnimal), stdin);

		printf("Especie do animal: ");
		fgets(novaConsulta.especieAnimal, sizeof(novaConsulta.especieAnimal), stdin);

		printf("Raca do animal: ");
		fgets(novaConsulta.racaAnimal, sizeof(novaConsulta.racaAnimal), stdin);

		printf("Tipo de consulta: ");
		fgets(novaConsulta.tipoConsulta, sizeof(novaConsulta.tipoConsulta), stdin);

		consultas[*contador] = novaConsulta;
		(*contador)++;
		printf("Consulta adicionada com sucesso!\n");
		printf("------------------------------\n");
	}
	else {
		printf("Limite de consultas atingido!\n");
	}
}

//funçâo que grava as consultas num ficheiro
void gravarConsulta(Consulta consultas[], int contador, const char* nomeFicheiro) {
	FILE* fp = fopen(nomeFicheiro, "wb");
	if (fp == NULL) {
		printf("Erro na abertura do ficheiro\n");
		exit(1);
	}

	if (fwrite(&contador, sizeof(int), 1, fp) != 1) {
		printf("Erro ao escrever no ficheiro\n");
		exit(1);
	}

	if (fwrite(consultas, sizeof(Consulta), contador, fp) != contador) {
		printf("Erro ao escrever no ficheiro\n");
		exit(1);
	}

	fclose(fp);
}

//função que lê as consultas guardadas no ficheiro
int lerConsultas(Consulta consultas[], int contador, const char* nomeFicheiro) {
	FILE* fp = fopen(nomeFicheiro, "rb");
	if (fp == NULL) {
		printf("Erro na abertura do ficheiro\n");
		exit(1);
	}


	if (fread(&contador, sizeof(int), 1, fp) != 1) {
		printf("Erro ao ler do ficheiro\n");
		exit(1);
	}

	if (fread(consultas, sizeof(Consulta), contador, fp) != contador) {
		printf("Erro ao ler do ficheiro\n");
		exit(1);
	}

	fclose(fp);
	return contador;
}

//função que mostra as consultas guardadas no ficheiro
void mostrarConsultas(Consulta consultas[], int contador) {

	printf("Listagem de Consultas:\n");
	printf("------------------------------\n");

	printf("%d consultas gravadas\n", contador);


	for (int i = 0; i < contador; i++) {
		printf("Consulta %d:\n", i + 1);

		printf("Nome do dono: %s\n", consultas[i].nomeDono);
		printf("Morada do dono: %s\n", consultas[i].moradaDono);
		printf("Valor da consulta: %0.2f\n", consultas[i].valorConsulta);
		printf("Data da consulta: %s\n", consultas[i].dataConsulta);
		printf("Nome do animal: %s\n", consultas[i].nomeAnimal);
		printf("Especie do animal: %s\n", consultas[i].especieAnimal);
		printf("Raca do animal: %s\n", consultas[i].racaAnimal);
		printf("Tipo: %s\n", consultas[i].tipoConsulta);
		printf("------------------------------\n");
	}
}

int main() {
	Consulta consultas[MAX_CONSULTAS];
	int contador = 0;
	int opcao;
	do {
		printf("\nGestao de Consultas Veterinarias\n");
		printf("1. Adicionar Consulta\n");
		printf("2. Gravar Consulta\n");
		printf("3. Ler e Mostrar Consultas\n");
		printf("0. Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao); // Alteração: usando scanf para ler a opção

		switch (opcao) {
		case 1:
			adicionarConsulta(consultas, &contador);
			break;
		case 2:
			gravarConsulta(consultas, contador, "consultas.dat");
			break;
		case 3:
			contador = lerConsultas(consultas, contador, "consultas.dat"); // Captura o retorno de lerConsultas
			mostrarConsultas(consultas, contador);
			break;
		case 0:
			printf("A sair do programa...\n");
			break;
		default:
			printf("Opcao invalida! Tente novamente.\n");
		}

	} while (opcao != 0);
}