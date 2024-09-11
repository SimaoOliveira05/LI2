#ifndef Guiao2
#define Guiao2

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>
#include "Guiao1.h"

/*
Esta estrutura serve para guardar as informações de cada teste
*/
typedef struct ArrayCombinacoes {
  wchar_t *s;
  int valor; //o valor da maior carta 
  int naipe; // o naipe da maior carta
} ArrayCombinacoes;

void devolve_wchar_string_ordenada (wchar_t * string, Carta cards[], int tamanho);

void print_output(ArrayCombinacoes comb[], int nlinhas, int breaked);

int verificaCombinacao (int tipo_combinacao, Carta cards[], int tamanho);

void insere (ArrayCombinacoes comb[], int valor, int naipevalor, int iteracoes, int tamanho);

void iSort (ArrayCombinacoes comb[], int valor, int naipe, int iteracoes);

int processa_informacoes_ArrayCombinacoes (Carta cards[], int tamanho, int nCartas, int tipoCombinacao, int loops, ArrayCombinacoes comb[]);

int processa_informacoes_ArrayCombinacoes_para_0 (Carta cards[], int tamanho, int loops, ArrayCombinacoes comb[]);

Carta* organiza (wchar_t * notOrganized,int tamanho);

void teste();



#endif