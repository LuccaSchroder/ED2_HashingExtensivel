#include "Diretorio.h"
#include <iomanip>
#include <math.h>

bool static chavesAleatorias(Diretorio *diretorio, int tamChave, int qntChaves);
bool static chavesAleatoriasPadronizada(Diretorio *diretorio, int tamChave, int qntChaves, int tamPadrao);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int m;
    int b;
    int c;
    int p;
    cout << "Digite o tamanho dos baldes: " << endl;
    cin >> m;
    cout << "Digite o numero de bits a ser usado para as pseudo-chaves: " << endl;
    cin >> b;
    cout << "Digite a quantidade de chaves para serem testadas: " << endl;
    cin >> c;
    cout << "Digite o tamanho do padrao inicial para chaves: " << endl;
    cin >> p;

    Diretorio *diretorio = new Diretorio(m, b);
    // diretorio->inserir("1100");
    // diretorio->imprimeDiretorio();
    // diretorio->inserir("1101");
    // diretorio->imprimeDiretorio();
    // diretorio->inserir("0000");
    // diretorio->imprimeDiretorio();
    // diretorio->inserir("0001");
    // diretorio->imprimeDiretorio();
    // diretorio->inserir("1111");
    // diretorio->imprimeDiretorio();
    // diretorio->inserir("1110");
    // diretorio->imprimeDiretorio();
    if(chavesAleatorias(diretorio, b, c))
    {
        diretorio->imprimeDiretorio();   
    }
    delete diretorio;
    diretorio = new Diretorio(m, b);
    if(chavesAleatoriasPadronizada(diretorio, b, c, p))
    {
        diretorio->imprimeDiretorio();
    }

    delete diretorio;

    cout << "Finalizando programa" << endl;

    return 0;
}

bool static chavesAleatorias(Diretorio *diretorio, int tamChave, int qntChaves)
{
    if(pow(2, tamChave) < qntChaves)
    {
        cout << "Erro: Quantidade de chaves maior que o permitido!" << endl;
        return false;
    }
    for(int i = 0; i < qntChaves; i++)
    {
        string aux = "";

        for(int j = 0; j < tamChave; j++)
        {
            if(rand() % 2 == 0)
            {
                aux = aux + '0';
            }
            else 
            {
                aux = aux + '1';
            }
        }
        if(!diretorio->inserir(aux))
        {
            i--;
        }
    }
    return true;
}


bool static chavesAleatoriasPadronizada(Diretorio *diretorio, int tamChave, int qntChaves, int tamPadrao)
{
    int tam = tamPadrao;
    string padrao = ""; 
    if(pow(2, (tamChave - tam)) < qntChaves)
    {
        cout << "Erro: Quantidade de chaves maior que o permitido!" << endl;
        return false;
    }
    for(int j = 0; j < tam; j++)
    {
        if(rand() % 2 == 0)
        {
            padrao = padrao + '0';
        }
        else 
        {
            padrao = padrao + '1';
        }
    }

    for(int i = 0; i < qntChaves; i++)
    {
        string aux;
        aux = padrao;

        for(int j = tam; j < tamChave; j++)
        {
            if(rand() % 2 == 0)
            {
                aux = aux + '0';
            }
            else 
            {
                aux = aux + '1';
            }
        }
        if(!diretorio->inserir(aux))
        {
            i--;
        }
    }
    return true;
}

