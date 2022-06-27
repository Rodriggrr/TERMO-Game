#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <limits>
#include <ctime>
using namespace std;

int palAtual, stg = 0, aleat[10], lit = 0;
//Array que armazena as letras repetidas da palavra atual.
string rep[5];
//Array que armazena todas as letras que já foram, para melhor compreensão visual.
string letras[52];

int random(int tent) {//Funcao que pega uma palavra aleatória cada vez.
   //Seed para número aleatório muda a cada palavra.
    srand(time(NULL));
    //Variável 'palAtual' recebe um número aleatório.
    palAtual = rand() % 10;
    //Laço para descobrir se a palavra atual é repetida.
    for (int i = 0; i < tent; i++) {
        if (palAtual == aleat[i]) {
            palAtual = rand() % 10;
            i = -1;
        }
    }
    //Array 'aleat' vai receber as palavras que já foram.
    aleat[tent] = palAtual;
    return 0;
}

int error() { //Funcao para limpar quando vier numeros oi letras erradas, impedindo bugs e loops.
    cout << "Insira uma palavra válida!                    \n";
    cin.clear();
    cin.ignore(numeric_limits < std::streamsize > ::max(), '\n');
    return 0;
}

int tutorial() { //Tutorial kk
    cout << "REGRAS:\n\nSEMPRE digite palavras EXISTENTES de\napenas CINCO caracteres.\nDigite SEMPRE em letra MINÚSCULA.\nA qualquer momento, digite \"s\" para sair do jogo, \"m\" para voltar ao menu\nou \"d\" para desistir da palavra atual.\n\nINSTRUÇÕES:\nEm termo, seu objetivo é descobrir a palavra-alvo.\nPara isso, você digitará qualquer palavra existente; quando é digitada, cada caractere recebe uma cor:\n\n\033[41mVERMELHO:\033[0m O caractere não existe na palavra-alvo.\n\n\033[42mVERDE:\033[0m O caractere existe na palavra-alvo,\ne está na posição correta.\n\n\033[44mAZUL:\033[0m O caractere existe na palavra-alvo,\nmas em uma posição diferente.\n\nToda vez que ganhar, você passará\npara a próxima palavra.\nToda vez que perder, repetirá a palavra atual.\nSeu objetivo é chegar no final do jogo com a maior proporção ganho / perca possível.\nSão 10 palavras.\nBom jogo!\n\nPressione ENTER para continuar.";
    cin.get();
    cin.ignore(1);
    write(1, "\E[H\E[2J", 7);
    return 0;
}

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
//Função para o modo "Contra".
int multiplayer(string word[2], string game[2]) {
    write(1, "\E[H\E[2J", 7);
    
    cout << "Escolha a palavra que\nseu amigo irá descobrir:\n";
    cin >> game[0];
    
    //Condicional para que so seja aceito palavras de cinco caracteres.
    if (game[0].length() != 5) {
        error();
        cout << "\nPressione ENTER.";
        cin.get();
        cin.ignore(0);
        multiplayer(word, game);
        return 0;
    }
    //Como apenas uma palavra está sendo usada, 'palAtual' recebe 0.
    palAtual = 0;
    write(1, "\E[H\E[2J", 7);
    
    cout << "Adivinhe a palavra que seu amigo colocou.\n";
    int pont = 0;
    //Laço de tentativas.
    for (int i = 1; i < 7; i++) {
        int count = 0;
        pont = 0;
        
        cout << "Tentativa " << i << " de 6.                    \n\n";
        //Laço para imprimir as letras já colocadas.
        for (int li = 0; li < lit; li = li + 2) {
            if (li % 5 == 0 && li < 0) {
                cout << "\n";
                count++;
            }
            if (letras[li + 1] == "v") {
                cout << "\033[30m\033[42m" << letras[li] << "\033[0m" << ", ";
            } else if (letras[li + 1] == "a") {
                cout << "\033[30m\033[103m" << letras[li] << "\033[0m" << ", ";
            } else {
                cout << "\033[41m" << letras[li] << "\033[0m" << ", ";
            }

        }
        
        cout << "\b\b ";
        //Laço para formatação, sobe uma linha no terminal cada vez que houver quebra de linha.
        for (int uau = 0; uau < count + 1; uau++) {
            cout << "\x1b[A\r";
        }
        
        cin >> word[0];
        
        if (word[0].length() != 5 && word[0] != "s") {
            error();
            cout << "\nPressione ENTER.";
            cin.get();
            cin.ignore(0);
            cout << "\x1b[A                         \x1b[A\x1b[A\x1b[A                                                     \x1b[A\n";
            i--;
            continue;
            return 0;
        }
        //Condicional que analisará se o jogador quer sair do jogo.
        if (word[0] == "s") {
            cout << "\nFim de jogo.\n";
            return 0;
        }
        cout << "\x1b[A";
        //char "trigger" para saber se a palavra contém letras repetidas ou não.
        char rep1;
        rep1 = repPalGame(game, game);
        
        if (rep1 != 's') { 
            //Se for com letra repetida, rept recebe um.
            int rept = 1;
            
            //'pont' recebe 'v', a quantidade de verdes da palavra.
            pont = palAnalise(word, game, ::rep, rept);
        } else { 
            //Se nao for, nada acontece.
            int rept = 0;
            
            pont = palAnalise(word, game, ::rep, rept);
        }
        
        //Reset das cores do terminal.
        cout << "\033[0m" << endl;
        
        //Se a quantidade de verdes for 5, sair do loop de tentativas.
        if (pont == 5) {
            break;
        }
    }
    //Condição para ganhar.
    if (pont == 5) {
        cout << "Parabéns, você ganhou!                      \b\b \n\nPressione ENTER para continuar.";
        
    } else {
        cout << "Que pena, você perdeu!                       \b\b \nA palavra era: " << game[0] << "." << "\n\nPressione ENTER para continuar.";
        
    }
    cin.get();
    cin.ignore(1);
    lit = 0;
    return 0;
}

int main() {
	//Palavras do jogo solo.
    string game[10] = {
        "dogma",
        "aorta",
        "ginga",
        "corte",
        "magma",
        "junta",
        "arara",
        "carma",
        "humus",
        "horta"
    };
    //Palavra-chute.
    string word[2];
    //Variáveis de triggers.
    int pont = 0;
    int win = 0, lose = 0, trial;
    
    write(1, "\E[H\E[2J", 7);
    cout << "Bem-vindo ao jogo de TERMO!\nEscolha:\n1 - Jogar Solo;\n2 - Jogar Contra;\n3 - Regras e Tutorial;\n4 - Encerrar;\n5 - Créditos.\n"; //"menu" do jogo.
    
    int choice;
    cin >> choice;
    if (choice == 2) {
        multiplayer(word, game);
        main();
        return 0;
    }

    if (choice == 3) {
        write(1, "\E[H\E[2J", 7);
        tutorial();
        main();
        return 0;
    }
    
    if (choice == 5) {
        write(1, "\E[H\E[2J", 7);
        cout << "Feito por Rodrigo e idealizado pelo Rodrigo(o outro Rodrigo kk).\nApoio moral por:\nCoala.\n\nPressione ENTER para continuar.";
        cin.get();
        cin.ignore(1);
        main();
        return 0;
    }
    
    if (choice == 4) {
        cout << "\nFim do jogo.\n";
        return 0;
    }
    
    //Laço que cicla através das palavras.
    for (int p = 0; p < 10; p++)
    {
        int tgl = 0;
        lit = 0;
        
        //Condicional para mudar a palavra quando necessário.
        if (stg == 0) {
            random(p);
        }
        
        stg = 0;
        write(1, "\E[H\E[2J", 7);
        
        cout << "Palavra " << p + 1 << " de 10." << endl;
        
        //Laço das tentativas.
        for (int t = 0; t < 6; t++)
        {

            cout << t + 1 << "° tentativa de 6.                        \n" << endl;
            
            trial = t;
            int v = 0;
            int count = 0;
            
            //Laço para imprimir as letras já utilizadas.
            for (int li = 0; li < lit; li = li + 2) {
                if (li % 5 == 0 && li < 0) {
                    cout << "\n";
                    count++;
                }
                if (letras[li + 1] == "v") {
                    cout << "\033[30m\033[42m" << letras[li] << "\033[0m" << ", ";
                } else if (letras[li + 1] == "a") {
                    cout << "\033[30m\033[103m" << letras[li] << "\033[0m" << ", ";
                } else {
                    cout << "\033[41m" << letras[li] << "\033[0m" << ", ";
                }

            }
            cout << "\b\b ";

            for (int uau = 0; uau < count + 1; uau++) {
                cout << "\x1b[A\r";
            }

            cin >> word[0];
            if (word[0].length() != 5 && word[0] != "s" && word[0] != "m" && word[0] != "d") {
                error();
                cout << "\nPressione ENTER.";
                cin.get();
                cin.ignore(0);
                cout << "\x1b[A                          \x1b[A\x1b[A\x1b[A                                                     \x1b[A\x1b[A\n";
                t--;
                continue;
                return 0;
            }
            
            //Condicionais para analisar a opção que o jogador colocou.
            if (word[0] == "s") {
                cout << "\nGame Over. Obrigado por jogar!\n";
                return 0;
            }
            if (word[0] == "m") {
                write(1, "\E[H\E[2J", 7);
                main();
                return 0;
            }
            if (word[0] == "d") {
                lose++;
                cout << "Que pena, você desistiu e perdeu!\nA palavra era: \"\033[30m\033[42m" << game[palAtual] << "\033[0m\".\nAté agora, você:\n\nGanhou " << win;
                (win == 1) ? cout << " vez;": cout << " vezes;";
                cout << "\nPerdeu " << lose;
                (lose == 1) ? cout << " vez.": cout << " vezes.";
                cout << "\nSua proporção G/P é: ";
                (lose == 0) ? cout << fixed << setprecision(2) << (float) win: cout << fixed << setprecision(2) << (float) win / lose;
                cout << "\n\nAvance para a próxima palavra!\n\nPressione ENTER para continuar.";
                cin.get();
                cin.ignore(1);
                write(1, "\E[H\E[2J", 7);
                tgl = 1;
                break;
            }
            
            cout << "\x1b[A";
            char rep1;
            rep1 = repPalGame(game, game);
            
            if (rep1 != 's') { //se for com letra repetida, rept recebe um.
                int rept = 1;
                pont = palAnalise(word, game, rep, rept);
                
            } else { //se nao for, nada acontece
                int rept = 0;
                pont = palAnalise(word, game, rep, rept);
                
            }
            cout << "\033[0m" << endl;
            
            if (pont == 5) {
                break;
            }
        }
        if (pont == 5) //se todas as letras sao verdes, ganha.
        {
          win++;
            cout << "Parabéns, você ganhou na sua " << trial + 1 << "° tentativa!" << "\nAté agora, você:\n\nGanhou " << win;
            (win == 1) ? cout << " vez;": cout << " vezes;";
            cout << "\nPerdeu " << lose;
            (lose == 1) ? cout << " vez.": cout << " vezes.";
            cout << "\nSua proporção G/P é: ";
            (lose == 0) ? cout << fixed << setprecision(2) << (float) win: cout << fixed << setprecision(2) << (float) win / lose;
            if (p == 10)
                cout << "\n\nAvance para a próxima palavra!\n\nPressione ENTER para continuar.";
            else
                cout << "\n\nPressione ENTER para continuar.";
            cin.get();
            cin.ignore(1);
            write(1, "\E[H\E[2J", 7);
            
        } else if (tgl == 0) //se ficou sem tentativas e as letras nao ficaram todas verdes, perde.
        {
            write(1, "\E[H\E[2J", 7);
            lose++;
            cout << "Que pena, você perdeu!\nAté agora, você:\n\nGanhou " << win;
            (win == 1) ? cout << " vez;": cout << " vezes;";
            cout << "\nPerdeu " << lose;
            (lose == 1) ? cout << " vez.": cout << " vezes.";
            cout << "\nSua proporção G/P é: ";
            (lose == 0) ? cout << fixed << setprecision(2) << (float) win: cout << fixed << setprecision(2) << (float) win / lose;
            cout << "\n\nJogue novamente!\n\nPressione ENTER para continuar.";
            cin.get();
            cin.ignore(1);
            write(1, "\E[H\E[2J", 7);
            p--;
            stg = 1;
            
        }
    }
    write(1, "\E[H\E[2J", 7);
    cout << "Parabéns por ter ganhado o jogo!\n Espero que tenha gostado!\n";
}
