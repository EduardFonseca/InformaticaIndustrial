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
    Contas(int senha, double saldo, std::string titular);
    std::string titular;
    int conta;
    void exibeDados();
    double getSaldo(int senha);
    void deposito(double valor, int senha);
    void saque(double valor, int senha);
};


#endif