#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <contas.h>
#include "conta_corrente.h"
#include "conta_poupanca.h"

struct Gerente
{
    std::string nome;
    int senha;
};

class Banco
{
private:
    Gerente gerente;
    Contas *pcontas;
    int num_contas;
    std::string path;
    Contas cria_conta();


public:
    Banco(std::string nome, int senha, std::string path);
    ~Banco();
    bool gera_arquivo();
    int login_gerente();
    bool nova_conta(int senha_gerente);
    int get_num_contas();


    //opcional
    bool troca_gerente(int senha_gerente);
};


#endif