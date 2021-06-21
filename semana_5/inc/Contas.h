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
    Contas(int senha,int conta, double saldo, std::string titular,std::string tipo);
    ~Contas();
    std::string titular;
    std::string tipo;
    int conta;
    void exibeDados();
    int getSaldo(int senha);
    bool deposito();
    bool saque();
    bool transferencia(int conta,Contas* pc[], int tam);

    int getSenha();

    virtual std::string getDadoExclusivo();
    // verificacao de conta
    int verificacaoConta(int conta,Contas* pc[], int tam);
    // criacao defuncoes para interacao de usuario
    int pedeSenha();
    double pedeValor();

};


#endif