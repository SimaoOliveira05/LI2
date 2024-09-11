#ifndef Guiao3
#define Guiao3

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>
#include "Guiao1.h"
#include "Guiao2.h"
#include <string.h>



int contarReis(Carta cartas[], int tamanho);

int comparaUltimasCartas(Carta ultimaJogada[], int tamanho1, Carta tentativaDeJogada[], int tamanho2);

Carta* removerCartasDoArray(Carta* cartasParaRemover, int tamanhoParaRemover, Carta* array, int *tamanhoArray);

void imprimirCarta(Carta paraImprimir[],int tamanhoparaImprimir, int nTeste,int *contadorP);

void processaJogada (int *contadorP, int numeroReis,int tipoTentativaJogada, int tipoUltimaJogada,int jogadaMaior,int tamanhoHand, Carta* mao,int t,int nJogadas,Carta* hand,int aux,int tamanhoJogada,int tamanhoUltimaJogada);

void processaJogadasAnteriores(int nJogadas, wchar_t* notOrganized, int* contadorP, int* tamanhoUltimaJogada, Carta** ultimaJogada);


#endif