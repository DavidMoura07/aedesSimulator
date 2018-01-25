/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   casa.h
 * Author: David
 *
 * Created on June 3, 2017, 8:43 PM
 */

#ifndef CASA_H
#define CASA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "TADmosquito.h"
#include "TADvizinho.h"

    /* Define um tipo casa
     * casa possui nome, prox, ant, lista de vizinhos e de mosquitos
     */
    typedef struct casa Casa;
    
    /* Define uma sentinela para o tipo cas
     * possui ponteiros para primeira e ultima casa da lista
     */
    typedef struct listacasa ListaCasa;

    /* Cria um tipo casa
     * inputs: nome da casa a ser criada
     * output: casa criada
     * pre-condicao: nome valido
     * pos-condicao: casa criada com parametros enviados e demais parametros = NULL
     */
    Casa* criaCasa(char* nome);
    
    /* Cria sentinela para casa
     * inputs: nenhum
     * output: sentinela criada
     * pre-condicao: nenhum
     * pos-condicao: nenhum
     */
    ListaCasa* criaListaCasa();
    
    /* insere casa na lista
     * inputs: casa a ser inserida e lista a recebe-la
     * output: lista de casa
     * pre-condicao: casa e lista existem
     * pos-condicao:  lista com a casa incluida
     */
    ListaCasa* insereCasa(Casa* casa, ListaCasa* lista);
    
    /* retira uma casa da lista
     * inputs: nome da casa a ser retirada e a lista
     * output: casa 
     * pre-condicao: casa e lista existem
     * pos-condicao: casa retirada da lista
     */
    Casa* retiraCasa(ListaCasa* lista, char* nome);
    
    /* libera memoria alocada para lista de casas
     * inputs: lista de casa
     * output: nenhum
     * pre-condicao: lista de casa existe
     * pos-condicao: lista totalmente liberada
     */
    void liberaListaCasa(ListaCasa* lista);
    
    /* retorna o nome da ca
     * inputs: casa
     * output: nome da casa
     * pre-condicao: casa existe
     * pos-condicao: casa inalterada
     */
    char* retornaNomeCasa(Casa* casa);
    
    /* retorna a lista de mosquitos 
     * inputs: casa
     * output: lista de mosquito 
     * pre-condicao: casa e lista existem
     * pos-condicao: casa e lista inalterados
     */
    ListaMosquito* retornaListaMosquito(Casa* casa);
    
    /* imprime a lista de casas para saida padrão
     * inputs: lista de casas
     * output: print da lista na saida padrao
     * pre-condicao: lista existe
     * pos-condicao: lista inalterada
     */
    void imprimeListaCasa(ListaCasa* lista);
    
    /* imprime uma casa na saida padrão
     * inputs: casa
     * output: print da casa 
     * pre-condicao: casa existe
     * pos-condicao: casa inalterada
     */
    void imprimeCasa(Casa* casa);
    
    /* busca uma casa pelo nome na lista
     * inputs: nome da casa a ser buscada e a lista
     * output: casa 
     * pre-condicao: casa e lista existem
     * pos-condicao: casa permanece na lista
     */
    Casa* buscaCasa(char* nome, ListaCasa* lista);
    
    /* retorna a lista de vizinhos
     * inputs: casa
     * output: lista de vizinhos
     * pre-condicao: casa e lista existem
     * pos-condicao: casa e lista inalterados
     */
    ListaVizinho* retornaListaVizinho(Casa* casa);
    
    /* retorna a quantidade de casas existentes na lista
     * inputs: lista de casas
     * output: quantidade de casas da lista 
     * pre-condicao: lista existe
     * pos-condicao: casas e lista inalterados
     */
    int tamListaCasa(ListaCasa* lista);
    
    /* retorna a primeira casa de uma lista
     * inputs: lista de casas
     * output: primeira casa da lista
     * pre-condicao: lista existe
     * pos-condicao: casa e lista inalterados
     */
    Casa* retornaListaPrim(ListaCasa* lista);
    
    /* retorna a ultima casa de uma lista
     * inputs: lista de casas
     * output: ultima casa da lista
     * pre-condicao: lista existe
     * pos-condicao: casa e lista inalterados
     */
    Casa* retornaListaUlt(ListaCasa* lista);
    
    /* retorna a proxima casa de uma lista
     * inputs: casa
     * output: proxima casa da lista
     * pre-condicao: casa existe
     * pos-condicao: casa inalterada
     */
    Casa* retornaProxCasa(Casa* casa);
    
    /* retorna a casa correspondente a posicao enviada
     * inputs: posição da casa desejada e a lista de casas
     * output: casa buscada
     * pre-condicao: lista existe e  0 < posição < qtdCasas
     * pos-condicao: casa e lista inalterados
     */
    Casa* pegaCasa(int posicao, ListaCasa* lista);
    
    /* imprime uma lista de casas em um arquivo externo
     * inputs: lista de casas
     * output: lista impressa em arquivo externo
     * pre-condicao: lista existente
     * pos-condicao: arquivo externo implementado
     */
    void imprimeListaCasaArquivo(char* arq, ListaCasa* lista);
    
    /* imprime uma casa em um arquivo externo
     * inputs: casa
     * output: casa impressa em arquivo externo
     * pre-condicao: casa existente
     * pos-condicao: arquivo externo implementado
     */
    void imprimeCasaArquivo(char* arq, Casa* casa);


#ifdef __cplusplus
}
#endif

#endif /* CASA_H */

