#ifndef CONTA_POUPANCA_H
#define CONTA_POUPANCA_H

#include "Contas.h"

class ContaPoupanca :public Conta
{
private:
    double taxa;
public:
    ContaPoupanca();
    ~ContaPoupanca();
    void SimulaRendimento(int num_meses);
};



#endif