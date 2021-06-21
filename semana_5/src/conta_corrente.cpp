#include "conta_corrente.h"
#include "contas.h"
#include <iostream>

ContaCorrente::ContaCorrente(int senha, int conta, double saldo, std::string titular, std::string tipo, int num_cartao){
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
    this->conta = conta;
    this->tipo = tipo;
    this->num_cartao = num_cartao;
}

int ContaCorrente::dadoExclusivo(){
    return this->num_cartao;
}

ContaCorrente::~ContaCorrente(){

}

