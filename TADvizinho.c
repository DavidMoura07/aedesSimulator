#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADcasa.h"
#include "TADvizinho.h"
#include "TADmosquito.h"

struct vizinho {
	Casa* casa;
	Vizinho* prox;
	Vizinho* ant;
};

struct listavizinho {
	Vizinho* prim;
	Vizinho* ult;
};

Vizinho* criaVizinho(void* casa)
{
	Vizinho* vizinho = (Vizinho*) malloc(sizeof(Vizinho));
	vizinho->casa = (Casa*) casa;
	vizinho->prox = vizinho->ant = NULL;
	return vizinho;
}

ListaVizinho* criaListaVizinho()
{
	ListaVizinho* listavizinho = (ListaVizinho*) malloc(sizeof(ListaVizinho));
	listavizinho->prim = listavizinho->ult = NULL;
	return listavizinho;
}

ListaVizinho* insereVizinho(Vizinho* vizinho, ListaVizinho* lista)
{
	if (vizinho != NULL) {
		if (lista->prim == NULL) {
			lista->prim = vizinho;
			lista->ult = vizinho;
		} else if (lista->prim == lista->ult) {
			lista->prim->prox = vizinho;
			lista->ult = vizinho;
			lista->ult->ant = lista->prim;
		} else {
			vizinho->ant = lista->ult;
			lista->ult->prox = vizinho;
			lista->ult = vizinho;
		}
	}
	return lista;
}

void liberaListaVizinho(ListaVizinho* lista)
{
	Vizinho* vizinho;
	Vizinho* vizinhoAux;
	if(lista->prim != NULL){
		vizinho = lista->prim;
		while(vizinho != NULL){
			vizinhoAux = vizinho->prox;
			free(vizinho);
			vizinho = vizinhoAux;
		}
	}
	free(lista);
}

char* retornaNomeVizinho(Vizinho* vizinho)
{
	return retornaNomeCasa(vizinho->casa);
}

void imprimeListaVizinho(ListaVizinho* lista)
{
	Vizinho* aux;
	if (lista->prim != NULL || lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			imprimeVizinho(aux);
		}
	} else {
		printf("Vazio\n");
	}
}

void imprimeVizinho(Vizinho* vizinho)
{
	if (vizinho != NULL) {
		printf("%s ", retornaNomeCasa(vizinho->casa));
	}
}

void imprimeListaVizinhoArquivo(char* arq, ListaVizinho* lista)
{
	Vizinho* aux;
	FILE* arquivo;
	if (lista->prim != NULL || lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			imprimeVizinhoArquivo(arq, aux);
			if (aux->prox != NULL) {
				arquivo = fopen(arq, "a");
				fprintf(arquivo, " -> ");
				fclose(arquivo);
			}
		}
	} else {
		arquivo = fopen(arq, "a");
		fprintf(arquivo, " vazio ");
		fclose(arquivo);
	}
}

void imprimeVizinhoArquivo(char* arq, Vizinho* vizinho)
{
	if (vizinho != NULL) {
		FILE* arquivo = fopen(arq, "a");
		fprintf(arquivo, "%s", retornaNomeCasa(vizinho->casa));
		fclose(arquivo);
	}
}

Vizinho* buscaVizinho(char* nome, ListaVizinho* lista)
{
	Vizinho* aux = NULL;
	if (lista->prim != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			if (!strcmp(retornaNomeCasa(aux->casa), nome))
				return aux;
		}
	}
	return aux;
}

int tamListaVizinho(ListaVizinho* lista)
{
	Vizinho* aux;
	int tam = 0;
	if (lista->prim != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			tam++;
		}
	}
	return tam;
}

Vizinho* retornaListaPrimVizinho(ListaVizinho* lista)
{
	return lista->prim;
}

Vizinho* retornaProxVizinho(Vizinho* vizinho)
{
	return vizinho->prox;
}

Vizinho* pegaVizinho(int posicao, ListaVizinho* lista)
{
	Vizinho* aux;
	int i;

	if (retornaListaPrimVizinho(lista) != NULL) {
		for (i = 0, aux = retornaListaPrimVizinho(lista); i < posicao; i++, aux = retornaProxVizinho(aux));
		return aux;
	}
	return NULL;
}
