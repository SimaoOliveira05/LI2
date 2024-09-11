#ifndef Guiao1
#define Guiao1       

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

typedef struct carta {
  int valor; // 0 Será o Ás , 13 será o Rei
  int naipe; // 0 -> Espadas   1 -> Copas   2 -> Ouros   3 -> Paus
} Carta;

Carta atribui_valor (wchar_t ncarta);

int comparaCartas(const void* a, const void* b);

void ordenaCartas(Carta* cartas, size_t numCartas);

int verificaConjunto (Carta card[] , int N);

int verificaSequencia (Carta card[] , int N);

int verificaDSequencia (Carta card[] , int N);

#endif