#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADcasa.h"
#include "TADvizinho.h"
#include "TADmosquito.h"

struct mosquito {
	int movimentos;
	int flag;
	int qtdMovAtual;
	struct mosquito* prox;
	struct mosquito* ant;
};

struct listamosquito {
	Mosquito* prim;
	Mosquito* ult;
};

Mosquito* criaMosquito()
{
	Mosquito* mosquito = (Mosquito*) malloc(sizeof(Mosquito));
	mosquito->movimentos = 0;
	mosquito->flag = 0;
	mosquito->qtdMovAtual = 0;
	mosquito->prox = mosquito->ant = NULL;
	return mosquito;
}

ListaMosquito* criaListaMosquito()
{
	ListaMosquito* lista = lista = (ListaMosquito*) malloc(sizeof(ListaMosquito));
	lista->prim = lista->ult = NULL;
	return lista;
}

ListaMosquito* insereMosquito(Mosquito* mosquito, ListaMosquito* lista)
{
	//printf("insere mosquito\n");
	if (mosquito != NULL) {
		//printf("mosquito != vazio\n");
		if (lista != NULL) {
			if (lista->prim == NULL) {
				//printf("lista vazia\n");
				mosquito->prox = mosquito->ant = NULL;
				lista->prim = mosquito;
				lista->ult = mosquito;
			} else {
				//printf("lista com mais de um elemento\n");
				lista->ult->prox = mosquito;
				mosquito->ant = lista->ult;
				mosquito->prox = NULL;
				lista->ult = mosquito;
			}
		}
	}
	return lista;
}

/*Mosquito* retiraMosquito(ListaMosquito* listamosq){
	Mosquito* auxmosq;
	if(listamosq->prim != NULL){
		auxmosq = listamosq->prim;
		if(auxmosq->flag == 0){
			listamosq->prim = listamosq->prim->prox;
			auxmosq->prox = NULL;
			auxmosq->flag = 1;
			auxmosq->movimentos++;
			return auxmosq;
		}
	}
	return NULL;
}*/

Mosquito* retiraMosquito(Mosquito* mosquito, ListaMosquito* lista)
{
	if (lista != NULL) {
		if (lista->prim != NULL) {
			if (mosquito != NULL) {
				if (mosquito == lista->prim && mosquito == lista->ult) {
					lista->prim = lista->ult = NULL;
					mosquito->prox = mosquito->ant = NULL;
					//printf("mosquito == lista->prim && mosquito == lista->ult\n");
				} else if (mosquito == lista->prim) {
					lista->prim = lista->prim->prox;
					lista->prim->ant = NULL;
					//printf("mosquito == lista->prim\n");
				} else if (mosquito == lista->ult) {
					lista->ult = lista->ult->ant;
					lista->ult->prox = NULL;
					//printf("mosquito == lista->ult\n");
				} else {
					mosquito->ant->prox = mosquito->prox;
					mosquito->prox->ant = mosquito->ant;
					mosquito->ant = mosquito->prox = NULL;
					//printf("mosquito->ant != NULL\n");
				}
			}
			return mosquito;
		}
	}
	return NULL;
}

void retiraPrimMosquito(ListaMosquito* lista)
{

	if (lista->prim != NULL) {
		if (lista->prim != lista->ult) {
			lista->prim = lista->prim->prox;

		} else {
			lista->prim = NULL;
			lista->ult = NULL;
			lista = NULL;
		}
	}
}

void liberaMosquito(Mosquito* mosquito)
{
	free(mosquito);
}

/*ListaMosquito* liberaListaMosquito(ListaMosquito* lista) {
	Mosquito* aux;
	while (lista->prim != NULL) {
		aux = lista->prim;
		//liberaMosquito(retiraMosquito(lista));
		lista = (retiraMosquito(aux, lista));
		liberaMosquito(aux);
	}
}*/

/*void liberaListaMosquito(ListaMosquito* lista)
{
	Mosquito* aux;
	Mosquito* aux2;

	if (lista->prim != NULL) {
		aux = lista->prim;
		while (aux != NULL) {
			aux2 = aux->prox;
			free(aux);
			aux = aux2;
		}
	}
	free(lista);
}*/

void liberaListaMosquito(ListaMosquito* lista) {
    Mosquito* aux;
    while (lista->prim != NULL) {
        aux = lista->prim;
        retiraMosquito(aux,lista);
        liberaMosquito(aux);
    }
}

int retornaMovimentos(Mosquito* mosquito)
{
	return mosquito->movimentos;
}

int tamListaMosquito(ListaMosquito* lista)
{
	Mosquito* aux;
	int tam = 0;
	if (lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			tam++;
		}
	}
	return tam;
}

void imprimeMosquito(Mosquito* mosquito)
{
	printf("movimentos do mosquito: %d | ", mosquito->movimentos);
	printf("Flag: %d\n", mosquito->flag);
}

void imprimeListaMosquito(ListaMosquito* lista)
{
	Mosquito* aux;
	int i, qtd = 0;
	qtd = tamListaMosquito(lista);
	if (lista != NULL && lista->prim != NULL && qtd > 0) {
		for (i = 1, aux = lista->prim; aux != NULL; aux = aux->prox, i++) {
			printf("%d- ", i);
			imprimeMosquito(aux);
		}
	} else {
		//printf("lista vazia\n");
	}
}

void imprimeListaMosquitoArquivo(char* arq, ListaMosquito* lista)
{
	FILE* arquivo;
	Mosquito* aux;
	int qtd = 0;
	if (lista != NULL && lista->prim != NULL) {
		qtd = tamListaMosquito(lista);
		if (qtd > 0) {
			for (aux = lista->prim; aux != NULL; aux = aux->prox) {
				arquivo = fopen(arq, "a");
				fprintf(arquivo, " -> M");
				fclose(arquivo);
			}
		}
	} else {
		//printf("lista vazia\n");
	}
}

Mosquito* incrementaMovimento(int valor, Mosquito* mosquito)
{
	mosquito->movimentos += valor;
	return mosquito;
}

Mosquito* incrementaQtdMovAtual(int valor, Mosquito* mosquito)
{
	mosquito->qtdMovAtual += valor;
	return mosquito;
}

Mosquito* alteraQtdMovAtual(int valor, Mosquito* mosquito)
{
	mosquito->qtdMovAtual = valor;
	return mosquito;
}

Mosquito* retornaListaPrimMosquito(ListaMosquito* lista)
{
	if (lista != NULL) {
		if (lista->prim != NULL) {
			return lista->prim;
		}
	} else {
		return NULL;
	}
}

Mosquito* retornaProxMosquito(Mosquito* mosquito)
{
	if (mosquito != NULL) { ///ahhhhhhh esses ifs malditos!!!!!!!!!!!!!
		if (mosquito->prox != NULL) { ////if do capeta desgraçado!!!!!!
			return mosquito->prox;
		}
	} else {
		return NULL;
	}
}

int retornaFlag(Mosquito* mosquito)
{
	return mosquito->flag;
}

int retornaQtdMovAtual(Mosquito* mosquito)
{
	return mosquito->qtdMovAtual;
}

void alteraFlag(int a, Mosquito* mosquito)
{
	mosquito->flag = a;
}

void zeraFlag(ListaMosquito* lista)
{
	Mosquito* aux;
	if (lista->prim != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			aux->flag = 0;
		}

	}
}

int movimentoListaMosquito(ListaMosquito* lista){
	Mosquito* mosquito;
	int i=0;
	
	if(lista->prim != NULL){
		for(mosquito = lista->prim; mosquito != NULL; mosquito = mosquito->prox){
			i += mosquito->movimentos;
		}
	}
	
	return i;
}