#ifndef CONTA_CORRENTE_H
#define CONTA_CORRENTE_H

#include "contas.h"
#include <string>
class ContaCorrente : public Contas
{
private:
    int num_cartao;
public:
    ContaCorrente(int senha, int conta, double saldo, std::string titular, std::string tipo, int num_cartao);
    ~ContaCorrente();

    virtual std::string getDadoExclusivo();
};




#endif
