#ifndef CONTA_H
#define CONTA_H

#include <string>

class Contas
{
private:

protected:
    double saldo;
    int senha;
public:
    Contas();
    //TODO:
    //fazer geracao de numero de conta
    Contas(int senha,int conta, double saldo, std::string titular,std::string tipo);
    ~Contas();
    std::string titular;
    std::string tipo;
    int conta;
    void exibeDados();
    void getSaldo(int senha);
    bool deposito();
    bool saque();
    bool transferencia(int conta,Contas* pc[], int tam);

    // verificacao de conta
    int verificacaoConta(int conta,Contas* pc[], int tam);
    // criacao defuncoes para interacao de usuario
    int pedeSenha();
    double pedeValor();

};


#endif