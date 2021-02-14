#include "Diretorio.h"
#include <algorithm>
#include <iostream>

Diretorio::Diretorio(int tamBalde, int tamPChave)
{
    this->tamBalde = tamBalde;
    this->tamPChave = tamPChave;
    this->profDir = 1; // profundidade do diretorio sempre inicializada com 1
    this->mapaDir = new unordered_map<string, Balde*>;
    Balde *baldeAux = new Balde(this->tamBalde);
    mapaDir->insert(pair<string, Balde*>("0", baldeAux));
    mapaDir->insert(pair<string, Balde*>("1", baldeAux));
}

Diretorio::~Diretorio()
{
    delete mapaDir;
    // Excluir baldes
}

bool Diretorio::inserir(string pchave)
{
    // prof global > prof balde -> dividir balde
    // == duplicar diretorio 
    string posMapa = pchave.substr(0, profDir);
    if(mapaDir->find(posMapa)->second->buscar(pchave))
    {
        return false;
    }
    else if(mapaDir->find(posMapa)->second->inserir(pchave))
    {
        return true;
    }
    if(mapaDir->find(posMapa)->second->getProfundidade() < profDir) 
    {
        dividirBalde(pchave); 
        return inserir(pchave);  
    }
    else if(profDir == mapaDir->find(posMapa)->second->getProfundidade())
    {
        duplicarDiretorio();
        return inserir(pchave); 
    }

}

bool Diretorio::buscar(string pchave)
{
    string posMapa = pchave.substr(0, profDir);
    if(mapaDir->find(posMapa)->second->buscar(pchave))
    {
        return true;
    }
    else
    {
        cout << "Chave não encontrada" << endl;
        return false;
    }

}

void Diretorio::dividirBalde(string chav)
{
    // se balde cheio, divide com outro balde as chaves e associar o balde ao mapa. D local = d global
    // slide 29
    string aux1;
    string aux2;
    string posMapa = chav.substr(0, profDir);
    Balde *baldeAux1 = mapaDir->find(posMapa)->second; // Balde a ser duplicado
    Balde *baldeAux2 = new Balde(this->tamBalde); // criacao de novo balde
    int final = baldeAux1->getProfundidade() + 1;
    baldeAux1->setProfundidade(final); // ajusta profundidade local
    baldeAux2->setProfundidade(final);
    // mapaDir->insert(pair<string, Balde*>("0", baldeAux2)); // ajustando ponteiros
    aux1 = chav.substr(0, final);
    aux2 = chav.substr(0, final - 1);
    if(*aux1.end()=='0') // vendo se o final termina com 0
    {
        aux2 = aux2 + '1';
    }
    else
    {
        aux2 = aux2 + '0';
    }
    for (auto local_it = mapaDir->begin(); local_it!= mapaDir->end(); ++local_it ) // percorrer todo mapa e verificar chaves 
    {
      // std::cout << " " << local_it->first << ":" << local_it->second;
      if(local_it->first.substr(0, final) == aux2)
      {
          local_it->second=baldeAux2;
      }
    }
    baldeAux1->redistribuirChaves(aux2, baldeAux2); // redistribuir as chaves

}

void Diretorio::duplicarDiretorio()
{
    if(profDir == tamPChave)
    {
        cout << "Erro! Diretorio nao cabe mais chaves." << endl;
        exit(0);
    }
    profDir++; // ajustando profundidade do diretorio
    unordered_map<string, Balde*> *mapaAux = new unordered_map<string, Balde*>; // criando novo diretorio 
    for (auto local_it = mapaDir->begin(); local_it!= mapaDir->end(); ++local_it)
    {
        mapaAux->insert(pair<string, Balde*>(local_it->first + "0", local_it->second)); // ajustando ponteiros
        mapaAux->insert(pair<string, Balde*>(local_it->first + "1", local_it->second));
    }

    
    delete mapaDir;
    mapaDir = mapaAux; 
}

void Diretorio::imprimeDiretorio()
{
    int cont = 0;
    vector <Balde*> vetAux;
    
    for (auto local_it = mapaDir->begin(); local_it!= mapaDir->end(); ++local_it)
    {
        if(std::find(vetAux.begin(), vetAux.end(), local_it->second) == vetAux.end())
        {
            vetAux.push_back(local_it->second);
            cout << local_it->first << " | ";
            cont = cont + local_it->second->imprime();
            cout << endl;
        }
    }

    // for(auto ptr = vetAux.begin(); ptr < vetAux.end(); ptr++)
    cout << "Fator de carga: " << (float) cont / (vetAux.size() * tamBalde) * 100 << endl;
    // cout << "Fator de carga: " << cont << " " << vetAux.size() << " " << tamBalde << endl;
    cout << endl;
    cout << endl;
}