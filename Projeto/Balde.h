#ifndef BALDE_H
#define BALDE_H 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Balde {

    private:
    int profundidade;
    int tam; // tamanho do balde
    vector<string> *vetor;

    public:
    Balde(int tam);
    ~Balde();
    int getProfundidade();
    void setProfundidade(int prof);
    bool inserir(string pchave);
    bool buscar(string pchave);
    void redistribuirChaves(string referencia, Balde *baldeRecebe);
    int imprime();

};

#endif