#include "myTorneio.h"


void printFirstJogada(LCarta jogadas){
    if (jogadas != NULL){
        for (int i = 0; i < jogadas->size; i++){
            wchar_t unicode = (127137 + jogadas->mao[i].valor) + (16 * (jogadas->mao[i].naipe));
            if (i != jogadas->size-1) wprintf(L"%lc ",unicode);
            else wprintf(L"%lc",unicode);
        }
        wprintf(L"\n");
    }
}

void printJogada(Answer jogadaPossivel) {
    if (jogadaPossivel.normal_cases == NULL && jogadaPossivel.king_cases == NULL)
        wprintf(L"PASSO\n");
    else if (jogadaPossivel.normal_cases == NULL)
        printFirstJogada(jogadaPossivel.king_cases);
    else
        printFirstJogada(jogadaPossivel.normal_cases);
}

int main(){

    int nJogadas, tamanhoMao, tamanhoUltimaJogada ,contadorP = 0,tipoUltimaJogada;

    setlocale(LC_CTYPE, "C.UTF-8");


    // lê o número de jogadas
    assert(wscanf(L"%d\n", &nJogadas) == 1);

    // Processa cartas da mão
    wchar_t* notOrganized = calloc(60 , sizeof(wchar_t));
    assert(fgetws(notOrganized, 60, stdin) != NULL); 
    tamanhoMao = wcslen(notOrganized) - 1;
    Carta* minhaMao = organiza(notOrganized,tamanhoMao); // A nossa Mão inicial

    // TODAS AS JOGADAS ATÉ A NOSSA
    Carta* ultimaJogada;
    //Processa todas as jogadas anteriores, contando o nº de passos e armazenando a ultima jogada e o seu tamanho para futuras comparações
    processaJogadasAnteriores(nJogadas, notOrganized, &contadorP, &tamanhoUltimaJogada, &ultimaJogada);
    
    tipoUltimaJogada = verificaCombinacoes(ultimaJogada, tamanhoUltimaJogada);

    // Se formos nós a escolher a jogada, o bot está programado para jogar o maior numero de cartas, de menor valor.
    if (contadorP == 3 || nJogadas == 0){
        Answer jogadaPossivel,  jogadaPossivelConjunto,  jogadaPossivelSeq, jogadaPossivelDSeq;
        
        //A fakeCard é apenas uma carta para dar de input na generate_all_combinations , como é inicializada com valores -1 todas as cartas da nossa mão são maiores que ela
        Carta fakeCard;
        fakeCard.valor = fakeCard.naipe = -1;
        int count = tamanhoMao;
        
        /*
        Tentamos primeiro gerar para o tamanho total da mão antes de entrar no loop,
        Fazemos isto pois a generate_all_combinations coloca a jogadaPossivel a NULL se não encontrar
        nenhuma combinação, se não fizessemos isto a primeira interação do loop ia aceder a "lixo" da memória.
        */
        jogadaPossivelConjunto = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,1),
        jogadaPossivelSeq = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,2),
        jogadaPossivelDSeq = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,3);
        count--;
        
        while (jogadaPossivelConjunto.normal_cases == NULL && jogadaPossivelSeq.normal_cases == NULL && jogadaPossivelDSeq.normal_cases == NULL && count > 0){
            jogadaPossivelConjunto = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,1),
            jogadaPossivelSeq = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,2),
            jogadaPossivelDSeq = generate_all_combinations(minhaMao,tamanhoMao,count,0,fakeCard,3);
            count--;
        }
        
        // Saiu do loop, foi encontrada uma jogadaPossivel ou não existe nenhuma jogada possivel.
        if (jogadaPossivelConjunto.normal_cases)
            jogadaPossivel = jogadaPossivelConjunto;
        
        else if (jogadaPossivelSeq.normal_cases)
            jogadaPossivel = jogadaPossivelSeq;
        
        else
            jogadaPossivel = jogadaPossivelDSeq;

        printFirstJogada(jogadaPossivel.normal_cases);
    }
    
    // Temos que jogar em função do jogador anterior.
    else{
        int nReis = contarReis(ultimaJogada,tamanhoUltimaJogada);
        Answer jogadaPossivel = generate_all_combinations(minhaMao,tamanhoMao,tamanhoUltimaJogada,nReis,ultimaJogada[tamanhoUltimaJogada-1],tipoUltimaJogada);
        
        printJogada(jogadaPossivel);
    }
    return 0;
}
