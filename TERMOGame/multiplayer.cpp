#include "analisisword.cpp"

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
