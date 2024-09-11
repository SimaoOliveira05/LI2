#ifndef Guiao4
#define Guiao4

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>
#include "Guiao1.h"
#include "Guiao2.h"
#include "Guiao3.h"

typedef struct linked {
    Carta* mao;
    int size;
    struct linked* prox;
} *LCarta;

typedef struct answer_cases {
    LCarta normal_cases;
    LCarta king_cases; 
} Answer;

int verificaAllEqual (Carta card[] , int N);

int verificaCombinacoes(Carta card[], int N);

void generate_combinations(Carta* cards, int n, int t, int start, Carta* data, int index, LCarta* head, LCarta* tail, Carta given_card, int combination_type);

Answer generate_all_combinations(Carta* cards, int tamanhoMao, int tamanhoJogada, int nReis, Carta given_card, int tipoCombinacao);

void printJogadas (LCarta jogadas);




#endif