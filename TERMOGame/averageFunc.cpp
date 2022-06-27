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