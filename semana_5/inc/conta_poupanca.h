#ifndef CONTA_POUPANCA_H
#define CONTA_POUPANCA_H

#include <contas.h>
#include <string>

class ContaPoupanca : public Contas
{
private:
    double taxa;
public:
    ContaPoupanca(int senha, int conta, double saldo, std::string titular, std::string tipo, double taxa);
    ~ContaPoupanca();
    void SimulaRendimento(int num_meses);
};



#endif