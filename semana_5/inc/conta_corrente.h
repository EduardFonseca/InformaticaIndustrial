#ifndef CONTA_CORRENTE_H
#define CONTA_CORRENTE_H

#include "Contas.h"
class ContaCorrente : public Contas
{
private:
    int num_cartao;
public:
    ContaCorrente();
    ~ContaCorrente();
};




#endif
