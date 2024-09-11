#include "Guiao4.h"

/*
A função generate_combinations é uma função recursiva que gera todas as combinações possíveis (e válidas) de cartas de um conjunto de cartas
*/

int verificaAllEqual (Carta card[] , int N){
  if (N == 4 && card[0].valor == card[1].valor && card[1].valor == card[2].valor && card[2].valor == card[3].valor)
    return 1;
  else return 0;
} 


int verificaCombinacoes(Carta card[], int N) {
    int resultado = 0;
    if (verificaConjunto(card, N) != 0)
        resultado = 1; 
    if (verificaSequencia(card, N) != 0)
        resultado = 2; 
    if (verificaDSequencia(card, N) != 0)
        resultado = 3;
    if (verificaAllEqual(card, N) != 0)
        resultado = 4;    
    return resultado;
}

void generate_combinations(Carta* cards, int n, int t, int start, Carta* data, int index, LCarta* head, LCarta* tail, Carta given_card, int combination_type) {
    if (index == t) {
        int condition = given_card.valor == -1 || (data[t-1].valor > given_card.valor || (data[t-1].valor == given_card.valor && data[t-1].naipe > given_card.naipe));
        if (condition) {
            // Verificar o tipo da combinação
            if (verificaCombinacoes(data, t) == combination_type) { // só armazena se for do mesmo tipo
                LCarta newNode = malloc(sizeof(struct linked));
                newNode->mao = malloc(t * sizeof(Carta));
                for (int i = 0; i < t; i++) {
                    newNode->mao[i] = data[i];
                    newNode->size = t;
                }
                newNode->prox = NULL;
                if (*head == NULL) {
                    *head = newNode;
                } else {
                    (*tail)->prox = newNode;
                }
                *tail = newNode;
            }
        }
        return;
    }

    for (int i = start; i <= n - 1; i++) {
        if (index == 0 || cards[i].valor == data[index - 1].valor || cards[i].valor == data[index - 1].valor + 1) {
            data[index] = cards[i];
            generate_combinations(cards, n, t, i + 1, data, index + 1, head, tail, given_card, combination_type);
        }
    }
}

/*
generate_all_combinations, recebe:

-as cartas da nossa mão,
-o tamanho da nossa mão,
-o tamanho da combinação jogada anterior,
-e a maior carta da jogada anterior
-o tipo de combinação da jogada anterior

E retorna a cabeça da lista ligada de combinações possiveis, independentemente se é conjunto sequencia ou dSequencia

*/ 

Answer generate_all_combinations(Carta* cards, int tamanhoMao, int tamanhoJogada, int nReis, Carta given_card, int tipoCombinacao) {
    Answer ans;
    ans.normal_cases = NULL;
    ans.king_cases = NULL;
    LCarta tail = NULL;
    Carta* data = (Carta*)malloc(tamanhoJogada * sizeof(Carta));
    Carta null_card; null_card.valor = -1;
    
    // Gerar combinações possíveis para a jogada normal
     generate_combinations(cards, tamanhoMao, tamanhoJogada, 0, data, 0, &ans.normal_cases, &tail, given_card,tipoCombinacao);

    // Se houver reis, então temos de gerar as combinações possíveis com reis
    tail = NULL;
    switch (nReis) {
    case 1:
        if (tamanhoMao >= 4) {
            data = realloc(data,4*sizeof(Carta));
            Carta* data1 = (Carta*)malloc(6 * sizeof(Carta));
            generate_combinations(cards, tamanhoMao, 4, 0, data, 0, &ans.king_cases, &tail, null_card,4);
            generate_combinations(cards, tamanhoMao, 6, 0, data1, 0, &ans.king_cases, &tail, null_card,3);
            free(data1);
        }
        break;
    case 2:
        if (tamanhoMao >= 8){
            data = realloc(data,8*sizeof(Carta));
            generate_combinations(cards, tamanhoMao, 8, 0, data, 0, &ans.king_cases, &tail, null_card,3);
        }
        break;
    case 3:
        if (tamanhoMao >= 10){
            data = realloc(data,10*sizeof(Carta));
            generate_combinations(cards, tamanhoMao, 10, 0, data, 0, &ans.king_cases, &tail, null_card,3);
        }
        break;
    }

    free(data);
    return ans;
}

/*
Função para dar print às combinações válidas de uma lista ligada
recebe a cabeça da lista e o tamanho de cada combinação (que vai ser igual)
*/

void printJogadas (LCarta jogadas){


    while (jogadas != NULL){
        for (int i = 0; i < jogadas->size; i++){
            wchar_t unicode = (127137 + jogadas->mao[i].valor) + (16 * (jogadas->mao[i].naipe));
            if (i != jogadas->size-1) wprintf(L"%lc ",unicode);
            else wprintf(L"%lc",unicode);
        }
        wprintf(L"\n");
        jogadas=jogadas->prox;
    }
}




/*int main() {
  
  int tamanhoJogada , tamanhoMao,  ntestes;

  setlocale(LC_CTYPE, "C.UTF-8");

  assert(wscanf(L"%d\n",&ntestes) == 1);  // lê o número de testes

  for(int i=1;i<=ntestes;i++) {
    wprintf(L"Teste %d\n",i);

    wchar_t* ultimaJogada = calloc( 60, sizeof(wchar_t)); 
    wchar_t* minhaMao = calloc( 60, sizeof(wchar_t)); 
    
    assert(fgetws(ultimaJogada,60, stdin) != NULL);  
    assert(fgetws(minhaMao,60, stdin) != NULL);  

    tamanhoJogada = wcslen(ultimaJogada) - 1; 
    
    if (!(minhaMao[wcslen(minhaMao)-1] == '\n')) minhaMao[wcslen(minhaMao)] = '\n';
    tamanhoMao = wcslen(minhaMao) - 1;

    Carta* cartasJogadas = organiza(ultimaJogada,tamanhoJogada);
    Carta* minhasCartas = organiza(minhaMao,tamanhoMao);

    Carta lastcard = cartasJogadas[tamanhoJogada-1];

    int nReis = contarReis(cartasJogadas,tamanhoJogada);
    int tipoJogada = verificaCombinacoes(cartasJogadas,tamanhoJogada);

    
    Answer all_combinations = generate_all_combinations(minhasCartas,tamanhoMao,tamanhoJogada,nReis, lastcard,tipoJogada);
    
    if (all_combinations.normal_cases) // Se houver jogadas normais válidas
        printJogadas (all_combinations.normal_cases);
    if (all_combinations.king_cases) // Se houver jogadas especiais para o caso de reis
        printJogadas (all_combinations.king_cases);
    
    if (!all_combinations.normal_cases && !all_combinations.king_cases) // Se não houver nem jogadas normais válidas nem de reis, dá print a PASSO
        wprintf(L"PASSO\n");
  }

  return 0;
} */