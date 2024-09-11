#include "Guiao2.h"

/*
A função devolve_wchar_string_ordenada, dado um pointer para uma string de wchart_t vazia, um array de cartas e o tamanho desse 
array, concatena todos os símbolos das cartas que pertencem ao array, alterando diretamente o endereço de memória desta wstring.
*/
void devolve_wchar_string_ordenada (wchar_t * string, Carta cards[], int tamanho) {
    string[0] = L'\0';
    for (int i = 0; i < tamanho; i++) {
        wchar_t buffer[2];
        swprintf(buffer, 2, L"%lc", (127137 + cards[i].valor) + (16 * cards[i].naipe));
        wcscat(string, buffer);
    }
}

/*
A função print_output, dado um ArrayCombinacoes, o número total de linhas lidas durante o loop de cada teste e um bool que indica
se o programa foi interrompido ou não (devido às condições de pertença ao mesmo tipo de combinações), faz o print na tela do resultado
final.
*/
void print_output(ArrayCombinacoes comb[], int nlinhas, int breaked) {
    if (breaked) {
        printf("Combinações não iguais!\n");
    } else {
        for (int i = 0; i < nlinhas; i++) {
            int tamanho = wcslen(comb[i].s);
            for (int j = 0; j < tamanho-1; j++) {
                printf("%lc ", comb[i].s[j]);
            }
            printf("%lc\n", comb[i].s[tamanho-1]);
        }
    }
}

/*
A função verificaCombinação, verifica se a combinação do input de cartas a ser lido neste loop é igual ao tipo de combinação
lido nos inputs anteriores, returnando 0 caso não o seja e 1 em caso afirmativo.
*/
int verificaCombinacao (int tipo_combinacao, Carta cards[], int tamanho) {
    if (((tipo_combinacao == 0) && (verificaConjunto(cards, tamanho))) || 
        ((tipo_combinacao == 1) && (verificaSequencia(cards, tamanho))) ||
        ((tipo_combinacao == 2) && (verificaDSequencia(cards, tamanho)))) return 1;
    else return 0;
}

/*
A função insere é a função auxiliar da iSort que move todos os elementos do array de modo a colocar a carta da vez no lugar
correto de forma ordenada. 
*/
void insere (ArrayCombinacoes comb[], int valor, int naipevalor, int iteracoes, int tamanho) {
    ArrayCombinacoes temp = comb[tamanho];

    for (int i = tamanho; i > iteracoes; i--) {
        comb[i] = comb[i-1]; 
    }

    comb[iteracoes] = temp;
    comb[iteracoes].valor = valor;
    comb[iteracoes].naipe = naipevalor;
}

/*
A função iSort, insere um elemento ordenadamente (relativamente ao atributo tamanho_relativo de uma array de ArrayCombinacoes).
*/
void iSort (ArrayCombinacoes comb[], int valor, int naipe, int iteracoes) {
    for (int i = 0; i < iteracoes; i++) {
        if (valor < comb[i].valor || (valor == comb[i].valor && naipe < comb[i].naipe)) {
            insere(comb, valor, naipe, i, iteracoes);
            return;
        }
    }
    insere(comb, valor, naipe, iteracoes, iteracoes);
}


/*
A função processa_informacoes_ArrayCombinacoes, dado a informação necessária a criar um ArrayCombinacoes com a carta atual, cria
essa estrutura e insere-a num array ordenado de ArrayCombinacoes
*/
int processa_informacoes_ArrayCombinacoes (Carta cards[], int tamanho, int nCartas, int tipoCombinacao, int loops, ArrayCombinacoes comb[]) {
    int tamanho_relativo = (cards[tamanho-1].valor);
    int naipe_relativo = (cards[tamanho-1].naipe);
    int tamanhoAtual = tamanho;
    //verifica se a combinação é do mesmo tipo que as anteriores
    if (verificaCombinacao(tipoCombinacao, cards, tamanho) && (tamanhoAtual == nCartas));
    else { 
        return 1;
    }
    //insere ordenadamente (por tamanho_relativo ou naipe_relativo), a ArrayCombinacoes no array dessa estrutura
    iSort(comb, tamanho_relativo, naipe_relativo, loops);
    return 0;
}

/*
A função processa_informacoes_ArrayCombinacoes_para_0, dado a informação necessária a criar um ArrayCombinacoes com a carta inicial, 
cria essa estrutura e insere-a num array ordenado de ArrayCombinacoes
*/
int processa_informacoes_ArrayCombinacoes_para_0 (Carta cards[], int tamanho, int loops, ArrayCombinacoes comb[]) {
    //copia a informação de s[loops].s para comb[0].s
    wcsncpy(comb[0].s, comb[loops].s, tamanho*3);
    //terminação nula da wstring
    comb[0].s[tamanho*2] = L'\0';
    //guarda as informações de tamanho relativo e tipo de combinação
    comb[0].valor = (cards[tamanho-1].valor);
    comb[0].naipe = (cards[tamanho-1].naipe);
    if (verificaConjunto(cards, tamanho)) return 0; else
    if (verificaSequencia(cards, tamanho)) return 1; else
    if (verificaDSequencia(cards, tamanho)) return 2; 
    return -1;
}


Carta* organiza (wchar_t * notOrganized,int tamanho){

    //inicializa um array que vai conter as cartas já com o respetivo valor e naipe
    Carta* cards = malloc(tamanho * sizeof(Carta));                                          
        
    //determina o valor e o naipe de cada carta do array 
    for (int i = 0 ; i < tamanho ; i++){ 
        cards[i] = atribui_valor(notOrganized[i]); 
        }

    //dealoca memória de notOrganized
    free(notOrganized); 

    //ordena o array de cartas
    ordenaCartas (cards , tamanho);

    return cards;
}


/*
A função teste é a função executada n vezes, dependendo do input inicial do utilizador.
Esta função tem o objetivo de ler os inputs de wchar_t strings, processá-las e ordená-las e fazer o seu tratamento no sentido
de as colocar em estruturas do tipo ArrayCombinacoes e ordenar estas estruturas, para posteriormente, dar um output de uma forma
simples.
*/

void teste() {
    int nlinhas, tamanho, breaked = 0, nCartas = 0, tipoCombinacao = 0;
    assert(wscanf(L"%d ", &nlinhas) == 1);
    ArrayCombinacoes comb[nlinhas];

    for (int loops = 0; loops < nlinhas; loops++) {

        //aloca a memória da wstring notOrganized
        wchar_t* notOrganized = calloc(60 , sizeof(wchar_t));
        assert(notOrganized != NULL);
    
        //lê as cartas e mete no array "notOrganized"
        assert(fgetws(notOrganized, 16, stdin) != NULL); 
        
        //determina quantas cartas foram recebidas
        tamanho = wcslen(notOrganized) - 1; 

        //inicializa um array que vai conter as cartas já com o respetivo valor e naipe
        Carta* cards = organiza(notOrganized,tamanho);                                          
        
        //aloca memória para a wstring de comb[loops]
        comb[loops].s = calloc((60), sizeof(wchar_t));
        assert(comb[loops].s != NULL); 

        //cria a wstring com as cartas ordenadas
        devolve_wchar_string_ordenada(comb[loops].s, cards, tamanho);


        if (loops != 0) {
            if (breaked == 0) breaked = processa_informacoes_ArrayCombinacoes (cards, tamanho, nCartas, tipoCombinacao, loops, comb);
        } 
        else {
            tipoCombinacao = processa_informacoes_ArrayCombinacoes_para_0 (cards, tamanho, loops, comb);
            nCartas = tamanho; //define o tamanho as próximas combinações poderão ter
        } 
    
    }
        
    print_output(comb, nlinhas, breaked);

    for (int i = 0; i < nlinhas; i++) {
        free(comb[i].s);
    }
}

/*int main() {
    int nlinhas;
    setlocale(LC_CTYPE, "C.UTF-8");

    assert (wscanf(L"%d ", &nlinhas) == 1);
    for (int i = 0; i < nlinhas; i++) {
        printf("Teste %d\n", i+1);
        teste();
    }
}*/