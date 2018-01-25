/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vizinho.h
 * Author: David
 *
 * Created on June 6, 2017, 1:13 PM
 */

#ifndef VIZINHO_H
#define VIZINHO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "TADcasa.h"
#include "TADmosquito.h"
    
    /* Define um tipo vizinho
     * vizinho possui uma casa, prox e ant
     */
    typedef struct vizinho Vizinho;
    
    /* Define uma sentinela para tipo vizinho
     * aponta para o primeiro e ultimo vizinho da lista
     */
    typedef struct listavizinho ListaVizinho;

    /* Cria um tipo vizinho
     * inputs: casa que referenciará o viznho
     * output: vizinho criado
     * pre-condicao: casa existente
     * pos-condicao: vizinho criado com casa inserida
     */
    Vizinho* criaVizinho(void* nome);
    
    /* Cria uma sentinela para vizinho
     * inputs: nenhum
     * output: sentinela criado
     * pre-condicao: nenhuma
     * pos-condicao: sentinela criado com prim e ult apontando para NULL
     */
    ListaVizinho* criaListaVizinho();
    
    /* Insere um vizinho em uma lista
     * inputs: vizinho e lista criados
     * output: lista com o vizinho inserido
     * pre-condicao: vizinho e lista já criados
     * pos-condicao: lista com o vizinho encadeado
     */
    ListaVizinho* insereVizinho(Vizinho* vizinho, ListaVizinho* lista);
    
    /* libera memoria alocada para lista
     * inputs: lista
     * output: nenhum
     * pre-condicao: lista existente
     * pos-condicao: lista liberada
     */
    void liberaListaVizinho(ListaVizinho* lista);
    
    /* retorna o nome do vizinho
     * inputs: vizinho
     * output: nome do vizinho
     * pre-condicao: vizinho existente
     * pos-condicao: vizinho inalterado
     */
    char* retornaNomeVizinho(Vizinho* vizinho);
    
    /* imprime a lista de vizinhos
     * inputs: lista
     * output: print da lista na saida padrao
     * pre-condicao: lista existente
     * pos-condicao: lista inalterada
     */
    void imprimeListaVizinho(ListaVizinho* lista);
    
    /* imprime vizinho para saida padrao
     * inputs: vizinho
     * output: print do vizinho na saida padrão
     * pre-condicao: vizinho existente
     * pos-condicao: vizinho inalterado
     */
    void imprimeVizinho(Vizinho* vizinho);
    
    /* busca um vizinho na lista de vizinhos 
     * inputs: nome do vizinho e a lista de vizinhos
     * output: vizinho encontrado
     * pre-condicao: vizinho existente na lista 
     * pos-condicao: lista e vizinho inalterados
     */
    Vizinho* buscaVizinho(char* nome, ListaVizinho* lista);
    
    /* retorna a quantidade de vizinhos presentes em uma lista
     * inputs: lista
     * output: quantidade de vizinhos encontrados 
     * pre-condicao: lista existente
     * pos-condicao: lista inalterada
     */
    int tamListaVizinho(ListaVizinho* lista);
    
    /* retorna o primeiro vizinho de uma lista 
     * inputs: lista
     * output: primeiro vizinho da lista
     * pre-condicao: lista existente
     * pos-condicao: vizinho existente
     */
    Vizinho* retornaListaPrimVizinho(ListaVizinho* lista);
    
    /* retorna proximo vizinho da lista
     * inputs: vizinho
     * output: proximo vizinho
     * pre-condicao: vizinho atual e proximo existentes
     * pos-condicao: proximo vizinho retornado sem alteração
     */
    Vizinho* retornaProxVizinho(Vizinho* vizinho);
    
    /* encontra um vizinho na lista de vizinhos de acordo com sua posição
     * inputs: posição do vizinho desejado e a lista de vizinhos
     * output: vizinho solicitado
     * pre-condicao: lista existente e posição menor que a quantidade de vizinhos
     * pos-condicao: lista inalterada
     */
    Vizinho* pegaVizinho(int posicao, ListaVizinho* lista);
    
    /* imprime um vizinho em um arquivo externo
     * inputs: vizinho
     * output: vizinho impresso em arquivo externo
     * pre-condicao: vizinho existente
     * pos-condicao: arquivo externo implementado
     */
    void imprimeVizinhoArquivo(char* arq, Vizinho* vizinho);
    
    /* imprime uma lista de vizinhos em um arquivo externo
     * inputs: lista de vizinhos
     * output: lista impressa em arquivo externo
     * pre-condicao: lista existente
     * pos-condicao: arquivo externo implementado
     */
    void imprimeListaVizinhoArquivo(char* arq, ListaVizinho* lista);
    
#ifdef __cplusplus
}
#endif

#endif /* VIZINHO_H */

