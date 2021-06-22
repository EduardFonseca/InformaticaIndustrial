#ifndef BANCO_H
#define BANCO_H

#include <string>
#include <vector>
#include <contas.h>
#include "conta_corrente.h"
#include "conta_poupanca.h"

using namespace std;

struct Gerente
{
    std::string nome;
    int senha;
};

class Banco
{
private:
    Gerente gerente;
    vector<Contas*> pcontas;
    int num_contas;
    vector<ContaCorrente> CC;
    vector<ContaPoupanca> CP;
    std::string path;
    Contas cria_conta();
    Contas cria_conta(int senha,int conta,double saldo, std::string titular, std::string tipo_de_conta,int dado_extra);
    bool salva_arquivo();
    bool leitura_dados(const std::string path);
    int get_num_contas();
public:
    Banco(std::string nome, int senha, std::string path);
    ~Banco();

    int login_gerente();
    bool nova_conta(int senha_gerente);
    //opcional
    bool troca_gerente(int senha_gerente);
};


#endif