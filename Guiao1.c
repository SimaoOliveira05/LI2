#include "Guiao1.h"

Carta atribui_valor (wchar_t ncarta){ 
    Carta carta;

    carta.valor = ((ncarta % 16) - 1);     // com esta conta o valor da carta fica de 0 a 13
 
    carta.naipe = ((ncarta / 16) - 2) % 4; // com esta o valor do naipe fica de 0 a 3
 
    return carta; // se fizermos assim, depois para passar a carta de volta para o valor inicial é so fazer 
                //  (127137 + valor) + (16 * naipe)
}               // 127137 = primeira carta


// Acho que é bem mais fácil se as nossas funçoes receberem um array de cartas já ordenado

int comparaCartas(const void* a, const void* b) {
    Carta* cartaA = (Carta*) a;
    Carta* cartaB = (Carta*) b; 

    // Primeiro, compara os valores
    if (cartaA->valor < cartaB->valor) return -1;
    if (cartaA->valor > cartaB->valor) return 1;

    // Se os valores forem iguais, compara os naipes
    if (cartaA->naipe < cartaB->naipe) return -1;
    if (cartaA->naipe > cartaB->naipe) return 1;

    // Se tanto o valor quanto o naipe forem iguais, as cartas são iguais
    return 0;
}

//Ordena as Cartas por valor, e se o valor for igual por naipe

void ordenaCartas(Carta* cartas, size_t numCartas) {
    qsort(cartas, numCartas, sizeof(Carta), comparaCartas);
}


// As funções que verificam retornam 0 se a combinação nao for a certa


int verificaConjunto (Carta card[] , int N){
    int nCartas = 1;
    
    for (int i = 1 ; i < N ; i++){
      if (card[i].valor != card[i-1].valor) 
        return 0;
      else 
        nCartas++;
    }
    
    if (nCartas > 0 && nCartas <= 4) return nCartas;
    else return 0;
}



int verificaSequencia (Carta card[] , int N){
  int nCartas = 1;
  
  for (int i = 1 ; i < N ; i++){
    if (card[i].valor != card[i-1].valor + 1) return 0;
    else  nCartas++;
  }
  if (nCartas >= 3) return nCartas;
  else return 0;
}



int verificaDSequencia (Carta card[] , int N){
    int limite = 1, nSequencias = 1 ;
    
    for (int i = 1 ; i < N ; i++){
      if (card[i].valor == card[i-1].valor){
        limite++;
      }
      
      if (limite > 2) 
        return 0;
      
      if (card[i].valor != card[i-1].valor && limite == 2){
        limite = 1;
        nSequencias++;
      }
      else if (card[i].valor != card[i-1].valor && limite != 2)
        return 0;
    }
      
    if (limite == 2 && nSequencias > 2) return nSequencias;
      
    else return 0;
}


/*int main () {
  int loops , tamanho , nlinhas;
  setlocale(LC_CTYPE, "C.UTF-8");
  
  // lê o número de linhas
  assert(wscanf(L"%d\n",&nlinhas) == 1);

  for (loops = 0 ; loops < nlinhas ; loops++){
    // o máximo de cartas que pode ser recebido são as da mão
    wchar_t* notOrganized = calloc( 60, sizeof(wchar_t));
    
    // lê as cartas e mete no array "notOrganized"
    assert(fgetws(notOrganized, 60, stdin) != NULL); 
    
    // determina quantas cartas foram recebidas
    tamanho = wcslen(notOrganized) - 1; 

    //inicializa um array que vai conter as cartas já com o respetivo valor e naipe
    Carta cards[tamanho];                                           
    
    // determina o valor e o naipe de cada carta do array 
    for (int i = 0 ; i < tamanho ; i++){ 
      cards[i] = atribui_valor(notOrganized[i]); 
    }
    
    // ordena o array de cartas
    ordenaCartas (cards , tamanho); 

    // como o array está organizado a ultima carta é obviamente a maior ,é so fazer a conta
    wchar_t lastcard = (127137 + cards[tamanho-1].valor) + (16 * cards[tamanho-1].naipe);

    if (verificaConjunto (cards,tamanho))
      printf ("conjunto com %d cartas onde a carta mais alta é %lc\n",verificaConjunto (cards,tamanho),lastcard);
    else if (verificaSequencia (cards,tamanho))
      printf ("sequência com %d cartas onde a carta mais alta é %lc\n" ,verificaSequencia(cards,tamanho),lastcard);
    else if (verificaDSequencia (cards,tamanho))
      printf ("dupla sequência com %d cartas onde a carta mais alta é %lc\n" , verificaDSequencia(cards,tamanho),lastcard);
    else 
      printf ("Nada!\n");

    free (notOrganized);
  }
    return 0;
}*/