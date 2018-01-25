#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADcasa.h"
#include "TADmosquito.h"
#include "TADvizinho.h"

struct casa {
	char* nome;
	struct casa* prox;
	struct casa* ant;
	ListaVizinho* vizinhos;
	ListaMosquito* listaMosquito;
};

struct listacasa {
	Casa* prim;
	Casa* ult;

};

Casa* criaCasa(char* nome)
{
	Casa* casa = (Casa*) malloc(sizeof(Casa));
	casa->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
	strcpy(casa->nome, nome);
	casa->ant = casa->prox = NULL;
	casa->vizinhos = criaListaVizinho();
	casa->listaMosquito = criaListaMosquito();
	return casa;
}

ListaCasa* criaListaCasa()
{
	ListaCasa* lista = (ListaCasa*) malloc(sizeof(ListaCasa));
	lista->prim = lista->ult = NULL;
	return lista;
}

ListaCasa* insereCasa(Casa* casa, ListaCasa* lista)
{
	if (casa != NULL) {
		if (lista->prim == NULL) {
			lista->prim = casa;
			lista->ult = casa;
		} else if (lista->prim == lista->ult) {
			lista->prim->prox = casa;
			lista->ult = casa;
			lista->ult->ant = lista->prim;
		} else {
			casa->ant = lista->ult;
			lista->ult->prox = casa;
			lista->ult = casa;
		}
	}
	return lista;
}

Casa* retiraCasa(ListaCasa* lista, char* nome)
{

}

void liberaListaCasa(ListaCasa* lista)
{
	Casa* casa;
	Casa* casaAux;
	if(lista->prim != NULL){
		casa = lista->prim;
		while( casa != NULL ){
			casaAux = casa->prox;
			liberaListaMosquito(casa->listaMosquito);
			free(casa->listaMosquito);
			liberaListaVizinho(casa->vizinhos);
			free(casa->nome);
			free(casa);
			casa = casaAux;
		}
	}
	free(lista);
}

char* retornaNomeCasa(Casa* casa)
{
	return casa->nome;
}

ListaMosquito* retornaListaMosquito(Casa* casa)
{
	return casa->listaMosquito;
}

void imprimeListaCasa(ListaCasa* lista)
{
	Casa* aux;
	if (lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			imprimeCasa(aux);
		}
	} else {
		printf("Vazio\n");
	}
}

void imprimeCasa(Casa* casa)
{
	if (casa != NULL) {
		printf("Nome: %s\n", casa->nome);
		printf("Quantidade de mosquitos: %d\n", tamListaMosquito(casa->listaMosquito));
		imprimeListaMosquito(casa->listaMosquito);
		printf("Vizinhos: ");
		imprimeListaVizinho(casa->vizinhos);
		printf("\n\n");
	}
}

void imprimeListaCasaArquivo(char* arq, ListaCasa* lista)
{
	Casa* aux;
	FILE* arquivo;
	if (lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			imprimeCasaArquivo(arq, aux);
			arquivo = fopen(arq, "a");
			fprintf(arquivo, "\n");
			fclose(arquivo);
		}
	} else {
		arquivo = fopen(arq, "a");
		fprintf(arquivo, " vazio ");
		fclose(arquivo);
	}
}

void imprimeCasaArquivo(char* arq, Casa* casa)
{

	if (casa != NULL) {
		FILE* arquivo = fopen(arq, "a");
		fprintf(arquivo, "%s", casa->nome);
		if (tamListaVizinho(casa->vizinhos) > 0) {
			fprintf(arquivo, " -> ");
		}
		fclose(arquivo);
		imprimeListaVizinhoArquivo(arq, casa->vizinhos);
		imprimeListaMosquitoArquivo(arq, casa->listaMosquito);
	}
}

Casa* buscaCasa(char* nome, ListaCasa* lista)
{
	Casa* aux;
	if (lista != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			if (!strcmp(aux->nome, nome))
				return aux;
		}
	}
	return NULL;
}

ListaVizinho* retornaListaVizinho(Casa* casa)
{
	return casa->vizinhos;
}

int tamListaCasa(ListaCasa* lista)
{
	Casa* aux;
	int tam = 0;
	if (lista->prim != NULL) {
		for (aux = lista->prim; aux != NULL; aux = aux->prox) {
			tam++;
		}
	}
	return tam;
}

Casa* retornaListaPrim(ListaCasa* lista)
{
	return lista->prim;
}

Casa* retornaListaUlt(ListaCasa* lista)
{
	return lista->ult;
}

Casa* retornaProxCasa(Casa* casa)
{
	return casa->prox;
}

Casa* pegaCasa(int posicao, ListaCasa* lista)
{
	Casa* aux;
	int i;

	if (retornaListaPrim(lista) != NULL) {
		for (i = 0, aux = retornaListaPrim(lista); i < posicao; i++, aux = retornaProxCasa(aux));
		return aux;
	}
	return NULL;
}

/*void mosquito_move(ListaCasa* lista) {
	Casa* casaAux;
	Casa* casaNova;
	Mosquito* mosquito;
	Mosquito* mosquitoAux;
	int qtdMosquito = 0;
	int qtdVizinhos = 0;
	int aleat;
	if (lista->prim != NULL) {
		//percorre todas as casas
		for (casaAux = lista->prim; casaAux != NULL; casaAux = casaAux->prox) {
			qtdMosquito = tamListaMosquito(casaAux->listaMosquito);
			qtdVizinhos = tamListaVizinho(casaAux->vizinhos);
			if (qtdMosquito > 0 && qtdVizinhos > 0) {
				//percorre todos os mosquitos da lista
				for (mosquito = retornaListaPrimMosquito(casaAux->listaMosquito); mosquito != NULL; mosquito = retornaProxMosquito(mosquito)) {
					if (retornaFlag(mosquito) == 0) {//se o mosquito ainda nao se moveu nesta chamada da função (flag == 0)
						alteraFlag(1, mosquito);
						incrementaMovimento(1, mosquito);
						//imprimeMosquito(mosquito);

						//BUSCANDO CASA NOVA ALEATORIAMENTE
						aleat = aleatorio(qtdVizinhos);
						if (aleat >= qtdVizinhos)
							aleat = qtdVizinhos - 1; // SUBTRAIO 1 POIS A CONTAGEM DE VIZINHOS COMEÇA POR ZERO
						casaNova = buscaCasa(retornaNomeVizinho(pegaVizinho(aleat, casaAux->vizinhos)), lista);
						//imprimeCasa(casaNova);                        

						//TROCANDO O MOSQUITO DE CASA   
						mosquitoAux = retornaProxMosquito(mosquito);
						casaAux->listaMosquito = retiraMosquito(mosquito, casaAux->listaMosquito);
						insereMosquito(mosquito, retornaListaMosquito(casaNova));
						qtdMosquito = tamListaMosquito(casaAux->listaMosquito);
						if (qtdMosquito > 0) {
							mosquito = mosquitoAux;
						} else {
							break;
						}
					}
				}
			}
		}
		for (casaAux = lista->prim; casaAux != NULL; casaAux = casaAux->prox) {
			zeraFlag(casaAux->listaMosquito);
		}
	}
}*/