/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: David
 *
 * Created on June 3, 2017, 1:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TADcasa.h"
#include "TADmosquito.h"
#include "TADvizinho.h"

//TAMANHO MAXIMO PARA UMA FRASE LIDA NO ARQUIVO DE ENTRADA
#define TAMFRASE 100
//TAMANHO MAXIMO DE UM COMANDO
#define TAMCOMANDO 30
//TAMANHO MAXIMO DE UM ARGUMENTO
#define TAMARG 20
//QUANTIDADE DE MOSQUITOS QUE SERÃO REPRODUZIDOS POR VEZ
#define DESCENDENTES 2
//NOME DOS ARQUIVOS DE SAIDA
#define LISTA "lista.txt"
#define LOG "log.txt"

/* conta quantas palavras existem em uma frase
 * inputs: frase
 * output: quantidade de palavras encontradas
 * pre-condicao: nenhuma
 * pos-condicao: nenhuma
 */
int total_palavra(char* frase);

/* gera um numero aleatorio entre zero e 'a'
 * inputs: 'a': limite para o numero aleatório
 * output: numero aleatorio
 * pre-condicao: 'a' ser do tipo int
 * pos-condicao: nenhuma
 */
int aleatorio(int a);

//AS FUNCOES NOMEADAS COMO main_* FORAM CRIADAS APENAS PARA ORGANIZAÇÃO, NAO PRECISAM EXISTIR POIS PODERIA SER FEITO TUDO NA MAIN
ListaCasa* main_insereCasa(char* nome, ListaCasa* lista);
void main_insereMosquito(char* nome, ListaCasa* lista);
void main_ligaCasas(char* nome1, char* nome2, ListaCasa* lista);
void main_iniciaSimulacao(int totalMovimentos, ListaCasa* lista);

/* conta quantos mosquitos existem no total
 * inputs: lista de casas
 * output: total de mosquitos existentes
 * pre-condicao: lista de casas existe
 * pos-condicao: nenhuma
 */
int totalMosquitos(ListaCasa* lista);

/* conta o total de movimento de todos os mosquitos da lista
 * inputs: lista de casas
 * output: somatorio do movimento dos mosquitos
 * pre-condicao: lista existe
 * pos-condicao: nenhuma
 */
int totalMovimentoMosquitos(ListaCasa* lista);

/* sorteia uma casa da lista e elimina os mosquitos
 * inputs: lista de casas
 * output: retorna um boleano indicando se encontrou mosquitos na casa ou nao
 * pre-condicao: lisa com casas existentes
 * pos-condicao: lista de mosquitos das casas sorteadas vazia
 */
int agente_atua(ListaCasa* lista);

/* reproduz o mosquito casp o intervalo de voos seja atingido
 * inputs: lista de casas, intervalo de voos entre as reproduções
 * output: nenhum
 * pre-condicao: lista de casas existente
 * pos-condicao: mosquitos multiplicados nas casas onde o intervalo foi alcançado
 */
void mosquito_bota(ListaCasa* lista, int intervalo);

/* move os mosquitos de casa, supervisiona parametros para mosquito_bota, agente_atua, inicia_simulação
 * inputs: lista de casas, intervalo do mosquito_bota, intervalo para agente_atua, duração da simulação, acertos dos agentes, tentativas e total de movimentos realizados
 * output: vizinho impresso em arquivo externo
 * pre-condicao: vizinho existente
 * pos-condicao: arquivo externo implementado
 */
int mosquito_move(ListaCasa* lista, int mosquitoBota, int agenteAtua, int iniciaSimulacao, int* acertos, int* tentativas, int* totalMovimentos);

int main(int argc, char *argv[])
{
	//VARIAVEIS PARA LER O ARQUIVO DE ENTRADA
	FILE* arq_comandos_fgets = fopen(argv[1], "r");
	FILE* arq_comandos_fscanf = fopen(argv[1], "r");
	//VARIAVEIS PARA ESCREVER O ARQUIVO DE SAIDA
	FILE* lista;
	FILE* log;
	//ARMAZENA FRASES DO ARQUIVO DE ENTRADA
	char frase[TAMFRASE];
	//ARMAZENA QTD PALAVRAS NA FRASE
	int qtd_palavra = 0;
	//RESERVA VARIAVEIS PARA RECEBER OS PARAMETROS DO ARQUIVO
	char comando[TAMCOMANDO], arg1[TAMARG], arg2[TAMARG], arg3[TAMARG];

	//parametros do programa:
	int agenteAtua = 0;
	int mosquitoBota = 0;
	int iniciaSimulacao = 0;
	ListaCasa* listaCasa = criaListaCasa();

	//variaveis do agente_atua
	int acertos = 0;
	int tentativas = 0;
	int totalMov = 0;

	//FUNÇÃO PARA GERAR NUMEROS ALEATORIOS
	srand((unsigned) time(NULL));

	if (!arq_comandos_fgets || !arq_comandos_fscanf) {
		printf("Ocorreu um erro ao abrir o arquivo %s\n", argv[1]);
		exit(-1);
	}

	//percorre linha por linha do arquivo de entrada
	do {
		//capturo uma linha do arquivo e armazeno em <frase>
		fgets(frase, TAMFRASE, arq_comandos_fgets);

		//conto quantas palavras tem na linha capturada
		qtd_palavra = total_palavra(frase);

		//esta sequencia verifica quantas palavras tem e captura cada palavra individualmente
		switch (qtd_palavra) {
		case 1://se a linha contiver apenas uma palavra
			fscanf(arq_comandos_fscanf, "%s\n", comando); //armazene esta palavra na variavel comando
			//#################### FIM ######################
			if (!strcmp(comando, "FIM")) {//se o comando for FIM chama a funcao fim()
				//finaliza o arquivo lista.txt
				lista = fopen(LISTA, "a");
				fprintf(lista, "Final:\n");
				fclose(lista);
				imprimeListaCasaArquivo(LISTA, listaCasa);
				//fim da impressao no aquivo

				//Inplementa arquivo log.txt
				log = fopen(LOG, "a");
				fprintf(log, "Numero de mosquitos finais:\t\t\t%d\n", totalMosquitos(listaCasa));
				fprintf(log, "Numero de movimentos totais dos mosquitos:\t%d\n", totalMov);
				fprintf(log, "Numero de erros dos agentes:\t\t\t%d\n", (tentativas - acertos));
				fprintf(log, "Numero de acertos dos agentes:\t\t\t%d\n", acertos);
				fclose(log);
				//fim do aquivo log.txt

				//função que libera a memória
				liberaListaCasa(listaCasa);

			} else {
				printf("O comando %s nao eh reconhecido como um comando interno.\n", comando);
			}
			break;

			//daqui em diante o raciocinio eh analogo ao anterior
		case 2:
			fscanf(arq_comandos_fscanf, "%s %s\n", comando, arg1);
			//#################### AGENTE ATUA ######################
			if (!strcmp(comando, "AGENTE_ATUA")) {
				agenteAtua = atoi(arg1);
				//#################### MOSQUITO BOTA ######################
			} else if (!strcmp(comando, "MOSQUITO_BOTA")) {
				mosquitoBota = atoi(arg1);
				//#################### INSERE CASA ######################
			} else if (!strcmp(comando, "inserecasa")) {
				listaCasa = main_insereCasa(arg1, listaCasa);
				//#################### INSERE MOSQUITO ######################
			} else if (!strcmp(comando, "inseremosquito")) {
				main_insereMosquito(arg1, listaCasa);
				//#################### INICIA SIMULACAO ######################
			} else if (!strcmp(comando, "iniciasimulacao")) {
				iniciaSimulacao = atoi(arg1);

				//Gera o arquivo lista.txt
				lista = fopen(LISTA, "w");
				fprintf(lista, "Inicial:\n");
				fclose(lista);
				imprimeListaCasaArquivo(LISTA, listaCasa);
				//fim da primeira parte do aquivo lista.txt

				//Gera o arquivo log.txt
				log = fopen(LOG, "w");
				fprintf(log, "Numero de mosquitos iniciais:\t\t\t%d\n", totalMosquitos(listaCasa));
				fclose(log);
				//fim da primeira parte do aquivo log.txt

				//movendo os mosquitos
				mosquito_move(listaCasa, mosquitoBota, agenteAtua, iniciaSimulacao, &acertos, &tentativas, &totalMov);
				//agente_atua(listaCasa);
				//VERIFICANDO SE PRECISA REPRODUZIR O MOSQUITO
				//mosquito_bota(listaCasa, mosquitoBota); //desta forma funcionaria tambem porém não está em "tempo real"
				//imprimeListaCasa(listaCasa);
			} else {
				printf("O comando %s nao eh reconhecido como um comando interno.\n", comando);
			}
			break;

		case 3:
			fscanf(arq_comandos_fscanf, "%s %s %s\n", comando, arg1, arg2);
			//#################### LIGA CASAS ######################
			if (!strcmp(comando, "ligacasas")) {
				main_ligaCasas(arg1, arg2, listaCasa);
			} else {
				printf("O comando %s nao eh reconhecido como um comando interno.\n", comando);
			}
			break;

		default:
			printf("Quantidade de parametros inválida! Abortando operacao!\n");
			exit(-2);
			break;
		}
	} while (strcmp(frase, "FIM") && strcmp(frase, "FIM\n"));

	fclose(arq_comandos_fscanf);
	fclose(arq_comandos_fgets);
}

int total_palavra(char* frase)
{
	int tam_frase = strlen(frase);
	int qtd_palavra = 0;
	int i;

	if (strcmp(frase, "")) {
		qtd_palavra++;
	}
	//conta quantas palavras tem na frase
	for (i = 0; i < tam_frase; i++) {
		if (frase[i] == ' ') {
			qtd_palavra++;
		}
	}
	return(qtd_palavra);
}

int aleatorio(int a)
{
	if (a != 0)
		return((rand() % a));
	else
		return 0;
}

ListaCasa* main_insereCasa(char* nome, ListaCasa* lista)
{
	Casa* casa = criaCasa(nome);
	lista = insereCasa(casa, lista);
	return lista;
}

void main_insereMosquito(char* nome, ListaCasa* lista)
{
	Mosquito* mosquito = criaMosquito();
	Casa* casa = buscaCasa(nome, lista);

	if (casa != NULL) {
		insereMosquito(mosquito, retornaListaMosquito(casa));
	} else {
		printf("INSERE MOSQUITO: A casa %s não existe!\n", nome);
	}
}

void main_ligaCasas(char* nome1, char* nome2, ListaCasa* lista)
{
	Casa* c1 = buscaCasa(nome1, lista);
	Casa* c2 = buscaCasa(nome2, lista);

	if (c1 != NULL && c2 != NULL) {
		Vizinho* v1 = criaVizinho(c1);
		Vizinho* v2 = criaVizinho(c2);

		//verifica se já nao eh vizinho e se não esta tentando vinvular-se a si mesmo
		if (!buscaVizinho(retornaNomeCasa(c2), retornaListaVizinho(c1)) && strcmp(retornaNomeVizinho(v2), retornaNomeCasa(c1)))
			insereVizinho(v2, retornaListaVizinho(c1));
		if (!buscaVizinho(retornaNomeCasa(c1), retornaListaVizinho(c2)) && strcmp(retornaNomeVizinho(v2), retornaNomeCasa(c1)))
			insereVizinho(v1, retornaListaVizinho(c2));
	} else {
		printf("LIGA CASAS: A casa %s ou a casa %s nao existe!\n", nome1, nome2);
	}
}

int agente_atua(ListaCasa* lista)
{
	int qtdCasas;
	int sorteada;
	Casa* casa;
	ListaMosquito* listaMosquito;

	qtdCasas = tamListaCasa(lista);
	//printf("qtdCasa: %d\n", qtdCasas);
	sorteada = aleatorio(qtdCasas);
	casa = pegaCasa(sorteada, lista);
	//imprimeCasa(casa);
	listaMosquito = retornaListaMosquito(casa);
	if (tamListaMosquito(listaMosquito)) {
		liberaListaMosquito(retornaListaMosquito(casa));
		return 1;
	} else {
		return 0;
	}
}

//VERSÃO QUE VERIFICA SE REALMENTE DEVE REPRODUZIR OS MOSQUITOS

void mosquito_bota(ListaCasa* lista, int intervalo)
{
	Casa* aux;
	int i;

	if (retornaListaPrim(lista) != NULL) {
		for (aux = retornaListaPrim(lista); aux != NULL; aux = retornaProxCasa(aux)) {
			if (tamListaMosquito(retornaListaMosquito(aux)) > 0) {
				Mosquito* mosquito;
				for (mosquito = retornaListaPrimMosquito(retornaListaMosquito(aux)); mosquito != NULL; mosquito = retornaProxMosquito(mosquito)) {
					int movimentos = retornaMovimentos(mosquito);
					if ((movimentos / intervalo) > 0 && (movimentos % intervalo) == 0) {
						for (i = 0; i < DESCENDENTES; i++) {
							Mosquito* mosquito = criaMosquito();
							ListaMosquito* listaMosquito = retornaListaMosquito(aux);
							listaMosquito = insereMosquito(mosquito, listaMosquito);
						}
					}
				}
			}
		}
	}

}

int mosquito_move(ListaCasa* lista, int mosquitoBota, int agenteAtua, int iniciaSimulacao, int* acertos, int* tentativas, int* totalMovimentos)
{
	Casa* casaAux;
	Casa* casaNova;
	Mosquito* mosquito;
	int qtdMosquito = 0;
	int qtdVizinhos = 0;
	int aleat;

	//usado para repordução do mosquito
	int i;
	//usado para o agente_atua
	int j = 0;
	int t = 0; //tentativas
	int a = 0; //acertos
	//conta o total de movimentos realizado pelos mosquitos
	int totalMov = 0;

	while (t < iniciaSimulacao) {
		if (retornaListaPrim(lista) != NULL) {
			for (casaAux = retornaListaPrim(lista); casaAux != NULL; casaAux = retornaProxCasa(casaAux)) {
				qtdMosquito = tamListaMosquito(retornaListaMosquito(casaAux));
				qtdVizinhos = tamListaVizinho(retornaListaVizinho(casaAux));
				if (qtdMosquito > 0 && qtdVizinhos > 0) {
					//percorre todos os mosquitos da lista
					mosquito = retornaListaPrimMosquito(retornaListaMosquito(casaAux));
					while (mosquito != NULL) {
						//printf("%s ",retornaNomeCasa(casaAux));
						if (retornaFlag(mosquito) == 0) {//se o mosquito ainda nao se moveu nesta chamada da função (flag == 0)
							alteraFlag(1, mosquito);
							incrementaMovimento(1, mosquito);
							incrementaQtdMovAtual(1, mosquito);
							totalMov++;

							//BUSCANDO CASA NOVA ALEATORIAMENTE
							aleat = aleatorio(qtdVizinhos);
							if (aleat >= qtdVizinhos)
								aleat = qtdVizinhos - 1; // SUBTRAIO 1 POIS A CONTAGEM DE VIZINHOS COMEÇA POR ZERO
							casaNova = buscaCasa(retornaNomeVizinho(pegaVizinho(aleat, retornaListaVizinho(casaAux))), lista);

							//TROCANDO O MOSQUITO DE CASA
							retiraMosquito(mosquito, retornaListaMosquito(casaAux));
							insereMosquito(mosquito, retornaListaMosquito(casaNova));

							//reproduzindo mosquito
							if (retornaQtdMovAtual(mosquito) == mosquitoBota) {
								for (i = 0; i < DESCENDENTES; i++) {
									Mosquito* mosquitoNovo = criaMosquito();
									insereMosquito(mosquitoNovo, retornaListaMosquito(casaNova));
								}
								alteraQtdMovAtual(0, mosquito);
							}

							//executando agente_atua
							j++;
							if (j == agenteAtua) {
								a += agente_atua(lista);
								t++;
								j = 0;
							}

							if (totalMov == iniciaSimulacao || totalMosquitos(lista) == 0) {
								*tentativas = t;
								*acertos = a;
								*totalMovimentos = totalMov;
								return 0;
							}

							if (retornaListaPrimMosquito(retornaListaMosquito(casaAux)) != NULL) {
								//verificando a lista novamente
								mosquito = retornaListaPrimMosquito(retornaListaMosquito(casaAux));
							} else {
								break;
							}

						} else {
							//avançando para o proximo mosquito
							mosquito = retornaProxMosquito(mosquito);
						}
					}
				}
			}
			//zerando as flags para que possam voar na proxima rodada
			for (casaAux = retornaListaPrim(lista); casaAux != NULL; casaAux = retornaProxCasa(casaAux)) {
				zeraFlag(retornaListaMosquito(casaAux));
			}
		}
	}
}

int totalMosquitos(ListaCasa* lista)
{
	int i = 0;
	Casa* casa;

	if (lista != NULL) {
		if (retornaListaPrim(lista) != NULL) {
			for (casa = retornaListaPrim(lista); casa != NULL; casa = retornaProxCasa(casa)) {
				i += tamListaMosquito(retornaListaMosquito(casa));
			}
		}
	}

	return i;

}

int totalMovimentoMosquitos(ListaCasa* lista)
{
	int i = 0;
	Casa* casa;

	if (lista != NULL) {
		if (retornaListaPrim(lista) != NULL) {
			for (casa = retornaListaPrim(lista); casa != NULL; casa = retornaProxCasa(casa)) {
				i += movimentoListaMosquito(retornaListaMosquito(casa));
			}
		}
	}

	return i;

}
