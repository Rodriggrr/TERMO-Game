#include "averageFunc.cpp"

int repPalGame(string p1[11], string p2[11]) { //Função para analisar se a palavra atual tem letras repetidas ou não.
    int tg = 0, rept = 1;
    
    //Laço para a letra que vai ser comparada com as letras posteriores.
    for (int i = 0; i < 5; i++) {
    	//Laço para fazer um ciclo entre as letras posteriores.
        for (int j = i + 1; j < 5; j++) {
        	//Condição para armazenar as letras repetidas no array global 'rep'.
            if (p1[palAtual][i] == p2[palAtual][j] && p1[palAtual][i] != rep[rept - 1][0]) {
                ::rep[rept] = p1[palAtual][i];
                tg = 1;
                rept++;
            }
        }
    }
    //Retornará 'o' caso a palavra tiver letras repetidas, e 's' caso não tenha.
    if (tg == 1)
        return 'o';
    return 's';
}

int palAnalise(string word[2], string game[11], string palRep[6], int rept) { //Analisa e imprime os caracteres da palavra com as cores de acordo.
    //String que armazena as letras que ficaram verdes;
    string verde[5];
    int v = 0, tg1 = 0, tg6 = 0;
    int lit2 = lit;
    
    //Laço para a letra que vai ser comparada.
    for (int i = 0; i < 5; i++) {    	
        //Variáveis de estilo "triggers".
        int tg2 = 0, tg3 = 0;
        
        //Laço para comparar as letras da palavra atual com a letra sendo comparada.
        for (int j = 0; j < 5; j++) {
        	//Laço que vai analisar se as letras colocadas são iguais a alguma letra já colocada antes, para imprimir na lista de letras colocadas da forma correta.
            for (int li = 0; li < lit; li = li + 2) {
                if (word[0][i] == letras[li][0] && letras[li + 1][0] != 'v') {
                    lit2 = li;
                    tg6 = 1;
                    break;
                } else if (word[0][i] == letras[li][0]) {
                    tg1 = 1;
                }
            }
            
            //Condicional para analisar se a letra da palavra atual é igual à letra sendo comparada.
            if (word[0][i] == game[palAtual][j]) {
            	//Agora, analisa se está no mesmo caractere. Se tiver, imprime em verde.
                if (word[0][i] == game[palAtual][i]) {
                    cout << "\033[30m\033[42m" << word[0][i]; //Verde

                    tg2 = 1;
                    verde[v] = word[0][i]; 
                    v++;
                    
                    if (tg1 == 0) {
                        letras[lit2] = word[0][i];
                        letras[lit2 + 1] = "v";
                        
                        if (tg6 != 1)
                            lit = lit + 2;
                    }
                    break;
                  //Se não tiver, imprime em azul dependendo da circunstância.
                } else {
                    int tg = 0;
                    
                    //Laços de comparação de letras.
                    for (int k = i, a = 0; a < 5; k++, a++) {
                        for (int r = 0; r < 5; r++) {
                            if (word[0][i] == rep[a][0] && rept == 1){ //Condicionais para caso tiver letra repetida. Se tiver e a letra atual for repetida, pula as condicionais abaixo.
                                tg3 = 1;
                            }
                        }
                        
                        if (tg3 == 0 && ((word[0][k + 1] == game[palAtual][k + 1] && word[0][k + 1] == word[0][i]) || word[0][i] == word[0][k + 1] || word[0][i] == verde[a][0])){ //Condicionais para ver se imprime azul ou vermelho.
                            tg = 1;
                        }
                    }
                    
                    if (tg == 0) {
                        cout << "\033[30m\033[103m" << word[0][i]; //azul
                        tg2 = 1;
                        
                        if (tg1 == 0) {
                            letras[lit2] = word[0][i];
                            letras[lit2 + 1] = "a";
                            if (tg6 != 1)
                                lit = lit + 2;
                        }
                        break;
                    }
                }
            }
        }
        //Condicional que analisa o gatilho "tg2".
        if (tg2 == 0) {
            cout << "\033[0m\033[41m" << word[0][i]; //Vermelho

            if (tg1 == 0) {
                letras[lit2] = word[0][i];
                letras[lit2 + 1] = "r";
                if (tg6 != 1)
                    lit = lit + 2;
            }
        }
        //Reset dos gatilhos e contadores.
        tg6 = 0;
        lit2 = lit;
        tg1 = 0;
    }
    //Retorna 'v', que é a quantidade de verdes (pontos acertados).
    return v;
}