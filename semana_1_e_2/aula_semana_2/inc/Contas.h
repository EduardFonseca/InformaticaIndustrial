#ifndef CONTA_H
#define CONTA_H

#include <string>

class Contas
{
private:
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
    double getSaldo(int senha);
    void deposito(double valor, int senha);
    void saque(double valor, int senha);
    void transferencia(int conta, int senha, double valor,Contas* pc[]);
};


#endif