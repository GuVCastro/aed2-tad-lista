/*****************************************************************************************
 * NOME DO ARQUIVO: lista.c 
 * 
 * AUTOR: Gustavo Valadares Castro
 *
 * DESCRIÇÃO:	Programa cria uma lista com nomes e URLs e permite pesquisa e edição de 
 *				seus elementos.
 *
 * MUDANÇAS:
 *				DATA		AUTOR	DETALHES
 *				2021/10/14	Gustavo	Programa completo
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOMES 20
#define TAM_LINKS 25
#define TAM_LISTA 20

typedef struct	Lista {
	char **nomes;
	char **links;
	int n;
	int MAX;
} Lista;

void newLista(Lista *l, int tamanhoLista)
{
	l->MAX = tamanhoLista;
	l->nomes = malloc(tamanhoLista * sizeof(char*));
	l->links = malloc(tamanhoLista * sizeof(char*));
	
	for (int i = 0; i < tamanhoLista; i++) {
		l->nomes[i] = malloc(TAM_NOMES * sizeof(char));
		l->links[i] = malloc(TAM_LINKS * sizeof(char));
	}

	l->n = 0;
}

void inserir(Lista *l, char *novoNome, char *novoLink)
{
	if (l->n >= l->MAX)
		exit(1);

	strcpy(l->nomes[l->n], novoNome);
	strcpy(l->links[l->n], novoLink);
	l->n++;
}

void inserirPadroes(Lista *l, char **nomes, char **links)
{
	for (int i = 0; i < 10; i++)
		inserir(l, nomes[i], links[i]);
}

void remover(Lista *l, char *nome)
{
	int pos;
	for (int i = 0; i < l->n; i++) {
		if (strcmp(l->nomes[i], nome) == 0) {
			pos = i;
			break;
		}
	}

	l->n--;

	for (int i = pos; i < l->n; i++) {
		strcpy(l->nomes[i], l->nomes[i + 1]);
		strcpy(l->links[i], l->links[i + 1]);
	}
}

void mostrarNomes(Lista *l)
{
	printf("Nomes: \n");
	for (int i = 0; i < l->n; i++) {
		printf("{ %s }\n", l->nomes[i]);
	}
	printf("\n");
}

void pesquisar(Lista *l, char *nome)
{
	int pos = -1;
	char auxNomes[TAM_NOMES], auxLinks[TAM_LINKS];

	for (int i = 0; i < l->n; i++) {
		if (strcmp(l->nomes[i], nome) == 0) {
			pos = i;
			break;		
		}
	}

	if (pos == -1)
		printf("\nResultado: NAO ENCONTRADO\n\n");
	else {
		printf("\nResultado: { %s, %s }\n\n", l->nomes[pos], l->links[pos]);
		
		strcpy(auxNomes, l->nomes[pos]);
		strcpy(auxLinks, l->links[pos]);

		for (int i = pos; i > 0; i--) {
			strcpy(l->nomes[i], l->nomes[i - 1]);
			strcpy(l->links[i], l->links[i - 1]);
		}
		
		strcpy(l->nomes[0], auxNomes);
		strcpy(l->links[0], auxLinks);
	}
}

int main(void)
{
	Lista l;
	newLista(&l, TAM_LISTA);
	
	char *nomesPadrao[10] = {
		"Google",
		"Facebook",
		"Instagram",
		"Whatsapp",
		"Linkedin",
		"Amazon",
		"Pinterest",
		"Tiktok",
		"Spotify",
		"Snapchat"
	};
	char *linksPadrao[10] = {
		"google.com",
		"facebook.com",
		"instagram.com",
		"web.whatsapp.com",
		"linkedin.com",
		"amazon.com",
		"pinterest.com",
		"tiktok.com",
		"spotify.com",
		"snapchat.com"
	};
	inserirPadroes(&l, nomesPadrao, linksPadrao);
	
	char nome[TAM_NOMES] = "", novoNome[TAM_NOMES] = "", novoLink[TAM_LINKS] = "";

	int opcao = -1;
	while(opcao != 0) {
		printf("*****************************************\n");
		printf("[1] Mostrar lista\n");
		printf("[2] Pesquisar URL\n");
		printf("[3] Inserir endereco\n");
		printf("[4] Remover endereco\n");
		printf("[0] Sair\n");
		printf("*****************************************\n");
		printf("\nInsira uma das opcoes: ");
		scanf("%i", &opcao);
		printf("\n");

		switch (opcao) {
			case 0:
				system("clear");
				printf("ATE MAIS\n");

			case 1:
				system("clear");
				mostrarNomes(&l);
				break;

			case 2:
				system("clear");
				mostrarNomes(&l);
				printf("Insira o nome: ");
				scanf(" %[^\n]%*c", nome);
				pesquisar(&l, nome);
				mostrarNomes(&l);
				break;
			
			case 3:
				system("clear");
				printf("Insira o nome: ");
				scanf(" %[^\n]%*c", novoNome);
				printf("Insira o link: ");
				scanf(" %[^\n]%*c", novoLink);	
				inserir(&l, novoNome, novoLink);
				mostrarNomes(&l);
				break;

			case 4:
				system("clear");
				mostrarNomes(&l);
				printf("Insira o nome: ");
				scanf(" %[^\n]%*c", nome);
				remover(&l, nome);
				mostrarNomes(&l);
				break;

			default: system("clear"); printf("OPCAO INVALIDA\n");	
		}
	}

	return 0;
}

