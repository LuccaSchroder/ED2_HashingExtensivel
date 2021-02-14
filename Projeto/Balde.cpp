#include "Balde.h"
#include <algorithm>
#include <math.h>

Balde::Balde(int tam)
{
    this->tam = tam;
    this->profundidade = 0;
    this->vetor = new vector<string>();
}

Balde::~Balde()
{
    delete vetor;
}

bool Balde::inserir(string pchave)
{
    if(tam > vetor->size() && std::find(vetor->begin(), vetor->end(), pchave) == vetor->end())
    {
        vetor->push_back(pchave);
        return true;
    }
    else
    {
        // cout << "Erro ao inserir pseudochave!" << endl;
        return false;
    }
}

bool Balde::buscar(string pchave)
{
    if(std::find(vetor->begin(), vetor->end(), pchave) == vetor->end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Balde::getProfundidade() 
{
    return profundidade;
}

void Balde::setProfundidade(int prof)
{
    profundidade = prof;
}

void Balde::redistribuirChaves(string referencia, Balde *baldeRecebe)
{
    vector<string> vetorAux;
    for(auto ptr = vetor->begin(); ptr < vetor->end(); ptr++) 
    {
        if((*ptr).substr(0, profundidade) == referencia)
        {
            vetorAux.push_back(*ptr);
            baldeRecebe->inserir(*ptr);
        }
    }
    for(auto ptr = vetorAux.begin(); ptr < vetorAux.end(); ptr++) 
    {
        vetor->erase(std::find(vetor->begin(), vetor->end(), *ptr));
    }

}

int Balde::imprime()
{
    int cont = 0;
    cout << "Profundidade: " << profundidade << " | ";
    for(auto ptr = vetor->begin(); ptr < vetor->end(); ptr++)
    {
        cout << *ptr << " "; 
        cont++;
    }
    return cont;
}
