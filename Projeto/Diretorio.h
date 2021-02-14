#ifndef DIRETORIO_H
#define DIRETORIO_H
#include "Balde.h"
#include <unordered_map>
using namespace std; 

class Diretorio {
    private:
    unordered_map<string, Balde*> *mapaDir;
    int profDir; // profundidade diretorio
    int tamBalde; // tamanho balde
    int tamPChave; // tamanho pseudo-chave

    public:
    Diretorio(int tamBalde, int tamPChave);
    ~Diretorio();
    bool inserir(string pchave);
    bool buscar(string pchave);
    void dividirBalde(string chav);
    void duplicarDiretorio();
    void imprimeDiretorio();

};
#endif