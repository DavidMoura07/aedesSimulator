/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mosquito.h
 * Author: David
 *
 * Created on June 5, 2017, 9:47 AM
 */

#ifndef MOSQUITO_H
#define MOSQUITO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "TADcasa.h"
#include "TADvizinho.h"
    
    /* Define um tipo mosquito
     * mosquito possui movimentos, flag e qtdMovAtual como int e ponteiros para prox e ant
     */
    typedef struct mosquito Mosquito;
    
    /* Define uma sentinela para tipo mosquito
     * aponta para o primeiro e ultimo mosquito da lista
     */
    typedef struct listamosquito ListaMosquito;

    /* Cria um tipo mosquito
     * inputs: nenhum
     * output: mosquito criado
     * pre-condicao: nenhuma
     * pos-condicao: movimentos, flag e qtdMovAtual zerados. Prox e ant apontam pra NULL
     */
    Mosquito* criaMosquito();
    
    /* Cria uma sentinela para mosquito
     * inputs: nenhum
     * output: sentinela criado
     * pre-condicao: nenhuma
     * pos-condicao: sentinela criado com prim e ult apontando para NULL
     */
    ListaMosquito* criaListaMosquito();
    
    /* Insere um mosquito em uma lista
     * inputs: mosquito criado e lista criada
     * output: lista com o mosquito inserido
     * pre-condicao: mosquito e lista já criados
     * pos-condicao: lista com o mosquito encadeado ao final da mesma
     */
    ListaMosquito* insereMosquito(Mosquito* mosquito, ListaMosquito* lista);
    
    /* retira um mosquito de uma lista
     * inputs: mosquito e a lista
     * output: mosquito sem ligação com a lista
     * pre-condicao: mosquito existente na lista
     * pos-condicao: mosquito->prox e mosquito->ant apontam pra NULL; a lista permanece encadeada
     */
    Mosquito* retiraMosquito(Mosquito* mosquito, ListaMosquito* lista);
    
    /* retira o primeiro mosquito da lista (não chegou a ser usada para este projeto)
     * inputs: lista de mosquito
     * output: nenhum
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista reduzida do primeiro elemento
     */
    void retiraPrimMosquito(ListaMosquito* lista);
    
    /* libera memoria alocada para lista de mosquitos
     * inputs: lista de mosquito
     * output: nenhum
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista liberada
     */
    void liberaListaMosquito(ListaMosquito* lista);
    
    /* retorna os movimentos do mosquito
     * inputs: mosquito
     * output: movimentos do mosquito
     * pre-condicao: mosquito existente
     * pos-condicao: mosquito inalterado
     */
    int retornaMovimentos(Mosquito* mosquito);
    
    /* conta a quantidade de mosquitos existentes na lista
     * inputs: lista de mosquito
     * output: tamanho da lista de mosquitos
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista inalterada
     */
    int tamListaMosquito(ListaMosquito* lista);
    
    /* imprime os dados do mosquito na saida padrão
     * inputs: mosquito
     * output: dados do mosquito printados na saida padrao
     * pre-condicao: mosquito existente
     * pos-condicao: mosquito inalterado
     */
    void imprimeMosquito(Mosquito* mosquito);
    
    /* imprime uma lista de mosqutos na saida padrao
     * inputs: lista de mosquito
     * output: print da lista na saida padrao
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista inalterada
     */
    void imprimeListaMosquito(ListaMosquito* lista);
    
    /* soma um valor a variavel movimento do mosquito
     * inputs: valor a ser incrementado e mosquito que ira receber a alteração
     * output: mosquito
     * pre-condicao: valor do tipo inteiro e mosquito existente
     * pos-condicao: mosquito com valor alterado
     */
    Mosquito* incrementaMovimento(int valor, Mosquito* mosquito);
    
    /* retorna o primeiro mosquito da lista
     * inputs: lista de mosquito
     * output: primeito mosquito da lista
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista inalterada, mosquito inalterado
     */
    Mosquito* retornaListaPrimMosquito(ListaMosquito* lista);
    
    /* retorna o proximo mosquito da lista
     * inputs: mosquito
     * output: proximo mosquito
     * pre-condicao: mosquito existente e com proximo != NULL
     * pos-condicao: mosquitos inalterados
     */
    Mosquito* retornaProxMosquito(Mosquito* mosquito);
    
    //Para este projeto adotamos: se flag == 0 mosquito não se moveu, se flag != 0 mosquito já se moveu.
    /* retorna valor da flag do mosquito
     * inputs: mosquito
     * output: valor correspondente a flag do mosquito
     * pre-condicao: mosquito existente
     * pos-condicao: mosquito e flag inalterados
     */
    int retornaFlag(Mosquito* mosquito);
    
    /* altera o valor da flag para outro enviado via parametro
     * inputs: valor a ser atualizado e mosquito a receber a modificação
     * output: nenhum
     * pre-condicao: valor do tipo inteiro, mosquito existente
     * pos-condicao: valor da flag do mosquto alterada
     */
    void alteraFlag(int a, Mosquito* mosquito);
    
    /* zera o valor das flags de todos os mosquitos da lista
     * inputs: lista de mosquito
     * output: nenhum
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista inalterada mosquitos com a flag=0
     */
    void zeraFlag(ListaMosquito* lista);
    
    /* libera memoria alocada para um mosquito
     * inputs: mosquito
     * output: nenhum
     * pre-condicao: mosquito existente
     * pos-condicao: memoria liberada
     */
    void liberaMosquito(Mosquito* mosquito);
    
    /* imprime a lista de mosquitos para um arquivo externo
     * inputs: nome do arquivo e a lista de mosquitos
     * output: nenhum
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: arquivo externo implementado com a lista de mosquitos
     */
    void imprimeListaMosquitoArquivo(char* arq, ListaMosquito* lista);
    
    
    //não utilizamos esta função pois a contagem foi feita em tempo real pois o agente poderia eliminar os mosquitos e perderiamos estes dados
    /* retorna o total de movimentos de todos os mosquitos da lista
     * inputs: lista de mosquito
     * output: total de movimentos dos mosquitos
     * pre-condicao: lista de mosquito existente e com mosquitos
     * pos-condicao: lista e mosquitos inalterados
     */
    int movimentoListaMosquito(ListaMosquito* lista);
    
    /* soma um valor a variavel qtdMovAtual do mosquito
     * inputs: valor a ser incrementado e mosquito que ira receber a alteração
     * output: mosquito
     * pre-condicao: valor do tipo inteiro e mosquito existente
     * pos-condicao: mosquito com valor alterado
     */
    Mosquito* incrementaQtdMovAtual(int valor, Mosquito* mosquito);
    
    /* retorna qtdMovAtual do mosquito
     * inputs: mosquito
     * output: valor correspondente a qtdMovAtual do mosquito
     * pre-condicao: mosquito existente
     * pos-condicao: mosquito e qtdMovAtual inalterados
     */
    int retornaQtdMovAtual(Mosquito* mosquito);
    
    /* altera a qtdMovAtual do mosquito para outro enviado via parametro
     * inputs: valor a ser atualizado e mosquito a receber a modificação
     * output: mosquito
     * pre-condicao: valor do tipo inteiro, mosquito existente
     * pos-condicao: qtdMovAtual do mosquto alterada
     */
    Mosquito* alteraQtdMovAtual(int valor, Mosquito* mosquito);

#ifdef __cplusplus
}
#endif

#endif /* MOSQUITO_H */

