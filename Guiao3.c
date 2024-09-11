#include "Guiao3.h"

int contarReis(Carta cartas[], int tamanho) {
    int contadorReis = 0;

    for (int i = 0; i < tamanho; i++) {
        if (cartas[i].valor == 13) {
            contadorReis++;
        }
        else return 0;
    }
  return contadorReis;
}




int comparaUltimasCartas(Carta ultimaJogada[], int tamanho1, Carta tentativaDeJogada[], int tamanho2) {
    // deve dar a última carta dos dois arrays
    Carta ultimaJogadaCarta = ultimaJogada[tamanho1 - 1];
    Carta maiorCarta = tentativaDeJogada[tamanho2 - 1];

    // Compara as cartas
    if ((maiorCarta.valor > ultimaJogadaCarta.valor) || (maiorCarta.valor == ultimaJogadaCarta.valor && maiorCarta.naipe > ultimaJogadaCarta.naipe)) {
        return 1; // A carta da tentativa de jogada é maior!!!
    } else {
        return 0; // A carta da tentativa de jogada é menor!!!
    }
}

// Remover as cartas da mão (tentar!!)

Carta* removerCartasDoArray(Carta* cartasParaRemover, int tamanhoParaRemover, Carta* array, int *tamanhoArray) {
    Carta *mao = calloc(60,sizeof (Carta));
    int iArray = 0 , iRemoved = 0, iCount = 0;


    while (iArray != *tamanhoArray){
        if (cartasParaRemover[iRemoved].valor != array[iArray].valor || cartasParaRemover[iRemoved].naipe != array[iArray].naipe){
            mao[iCount].valor = array[iArray].valor;
            mao[iCount].naipe = array[iArray].naipe;  // corrected line
            iCount++;
            iArray++;
        }
        else {
            iRemoved++;
            iArray++;
        }
    }
    *tamanhoArray = *tamanhoArray - tamanhoParaRemover;
    if (*tamanhoArray != iCount)
        *tamanhoArray = -1;   // CASO A NOSSA MÃO NÃO TIVER TODAS AS CARTAS DA JOGADA QUE PRETENDEOS O TAMANHO FICA -1
    return mao;                 
}



// IMPRIMIR AS CARTAS

void imprimirCarta(Carta paraImprimir[],int tamanhoparaImprimir,int nTeste, int *contadorP) {
    wprintf(L"Teste %d\n",nTeste);
    for(int i = 0; i < tamanhoparaImprimir; i++ ){
        wchar_t unicode = (127137 + paraImprimir[i].valor) + (16 * (paraImprimir[i].naipe));
        if (i != tamanhoparaImprimir - 1) wprintf(L"%lc ", unicode);
        else wprintf(L"%lc", unicode);
    }
    wprintf(L"\n");
    *contadorP = 0; //temos que resetar o contador de passos para o próximo teste
}

    
int verificaRei0 (int tipoTentativaJogada, int tipoUltimaJogada,int jogadaMaior,int tamanhoJogada,int tamanhoUltimaJogada){

    if ((tipoTentativaJogada == tipoUltimaJogada && jogadaMaior && tamanhoJogada == tamanhoUltimaJogada))
        return 1;

    return 0;
}

int verificaRei1 (int tipoTentativaJogada,int jogadaMaior,int tamanhoJogada){

    if ((tipoTentativaJogada == 1 && tamanhoJogada == 4) || (tipoTentativaJogada == 3 && tamanhoJogada == 6) || (tipoTentativaJogada == 1 && jogadaMaior && tamanhoJogada == 1))
        return 1;

    return 0;
}

int verificaRei2 (int tipoTentativaJogada,int jogadaMaior,int tamanhoJogada){

    if ((tipoTentativaJogada == 3 && tamanhoJogada == 8) || (tipoTentativaJogada == 1 && jogadaMaior && tamanhoJogada == 1))
        return 1;

    return 0;
}

//Dado toda a informação necessária, processa a jogada, tendo em conta todas as situações
void processaJogada (int *contadorP, int numeroReis,int tipoTentativaJogada, int tipoUltimaJogada,int jogadaMaior,int tamanhoHand, Carta* mao,int t,int nJogadas,Carta* hand,int aux,int tamanhoJogada, int tamanhoUltimaJogada){
    Carta* cartaParaImprimir;
    int tamanho;

    if (*contadorP < 3){
        if((numeroReis == 0 && verificaRei0(tipoTentativaJogada,tipoUltimaJogada,jogadaMaior,tamanhoJogada,tamanhoUltimaJogada)) ||
           (numeroReis == 1 && verificaRei1(tipoTentativaJogada,jogadaMaior,tamanhoJogada)) ||
           (numeroReis == 2 && verificaRei1(tipoTentativaJogada,jogadaMaior,tamanhoJogada)) ||
           (numeroReis == 3 && tipoTentativaJogada == 3 && tamanhoJogada == 10) ||
           (nJogadas == 0 && tipoTentativaJogada != 0)) {
            cartaParaImprimir = mao;
            tamanho = tamanhoHand;
        } else {
            cartaParaImprimir = hand;
            tamanho = aux;
        }
    } else {
        if (tipoTentativaJogada != 0) {
            cartaParaImprimir = mao;
            tamanho = tamanhoHand;
        } else {
            cartaParaImprimir = hand;
            tamanho = aux;
        }
    }

    imprimirCarta(cartaParaImprimir, tamanho, t, contadorP);
}


// Apenas começa a ter em conta as ultimas 3 jogadas

void processaJogadasAnteriores(int nJogadas, wchar_t* notOrganized, int* contadorP, int* tamanhoUltimaJogada, Carta** ultimaJogada) {
    for (int i = 1; i <= nJogadas; i++) {
        if (i <= nJogadas - 3) {
            notOrganized = calloc(60, sizeof(wchar_t));
            assert(fgetws(notOrganized, 60, stdin) != NULL);
            free(notOrganized);
        } 
        else {
            notOrganized = calloc(60, sizeof(wchar_t));
            assert(fgetws(notOrganized, 60, stdin) != NULL);
    
            if (notOrganized[0] == 'P') {
                (*contadorP) += 1;
            }   
            else {
                *tamanhoUltimaJogada = wcscspn(notOrganized, L"\n");
                *ultimaJogada = organiza(notOrganized, *tamanhoUltimaJogada); 
            }
        }
    }
}

/*int main () {
    int nTestes, nJogadas, tamanhoHand, tamanhoUltimaJogada, tamanhoJogada ,contadorP = 0,tipoTentativaJogada = 0,tipoUltimaJogada,numeroReis = 0,jogadaMaior = 0,aux;

    setlocale(LC_CTYPE, "C.UTF-8");

    // lê o número de testes
    assert(wscanf(L"%d\n",&nTestes) == 1);

    for (int t = 1; t <= nTestes; t++){

        // lê o número de jogadas
        assert(wscanf(L"%d\n", &nJogadas) == 1);

        
        
        // CARTAS DA TUA MÃO
        wchar_t* notOrganized = calloc(60 , sizeof(wchar_t));
        assert(fgetws(notOrganized, 60, stdin) != NULL); 
        tamanhoHand = aux = wcslen(notOrganized) - 1; // Numero de cartas na mão (aux é para futuras operações)
        Carta* hand = organiza(notOrganized,tamanhoHand); // A nossa Mão inicial
  
        // TODAS AS JOGADAS ATÉ A NOSSA
        Carta* ultimaJogada;
        //Processa todas as jogadas anteriores, contando o nº de passos e armazenando a ultima jogada e o seu tamanho para futuras comparações
        processJogadasAnteriores(nJogadas, notOrganized, &contadorP, &tamanhoUltimaJogada, &ultimaJogada);

        
        
        //A JOGADA QUE TU VAIS QUERER FAZER
        notOrganized = calloc(60 , sizeof(wchar_t));
        assert(fgetws(notOrganized, 60, stdin) != NULL);
        Carta* tentativaJogada;    

        // se a nossa jogada for Passo, imprimimos logo a mão novamente a passamos para o próximo teste
        if (notOrganized[0] == 'P') { 
            imprimirCarta(hand,tamanhoHand,t,&contadorP);
            continue;
        }
        
        // TAMANHO DA JOGADA QUE PRETENDEMOS FAZER
        tamanhoJogada = wcscspn(notOrganized, L"\n"); 
        // CRIA UM ARRAY DA STRUCT CARTA COM A NOSSA TENTATIVA DE JOGADA
        tentativaJogada = organiza(notOrganized,tamanhoJogada);
    
        tipoTentativaJogada = verificaCombinacoes(tentativaJogada, tamanhoJogada); // 1 para conjunto, 2 para Sequencia e 3 para Dupla Sequencia  //


  
        // LOGICA FINAL PARA SABER SE É VALIDO E DAR O DEVIDO PRINT 

        if (nJogadas > 0 && contadorP != 3) {
            tipoUltimaJogada = verificaCombinacoes(ultimaJogada, tamanhoUltimaJogada), // 1 para conjunto, 2 para Sequencia e 3 para Dupla Sequencia 
            numeroReis = contarReis(ultimaJogada, tamanhoUltimaJogada),
            jogadaMaior = comparaUltimasCartas(ultimaJogada,tamanhoUltimaJogada, tentativaJogada , tamanhoJogada);
        }
        else 
            tipoUltimaJogada = -1;


        // REMOVEMOS AS CARTAS QUE QUEREMOS JOGAR DA NOSSA MÃO
        // KEEP IN MIND A REMOVER CARTAS DO ARRAY COLOCA O tamanhoHand A -1 CASO NÃO TIVERMOS TODAS AS CARTAS!!
        Carta* mao = removerCartasDoArray(tentativaJogada, tamanhoJogada, hand, &tamanhoHand);

        if (tamanhoHand == -1)
            imprimirCarta(hand,aux,t,&contadorP);
        
        else
            processaJogada (&contadorP,numeroReis,tipoTentativaJogada,tipoUltimaJogada,jogadaMaior,tamanhoHand,mao,t,nJogadas,hand,aux,tamanhoJogada,tamanhoUltimaJogada);

    }
    return 0;
}
*/

