#include "TERMOGame/multiplayer.cpp"

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