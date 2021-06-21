#include "conta_corrente.h"
#include "contas.h"
#include <iostream>
#include <string>

ContaCorrente::ContaCorrente(int senha, int conta, double saldo, std::string titular, std::string tipo, int num_cartao){
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
    this->conta = conta;
    this->tipo = tipo;
    this->num_cartao = num_cartao;
}

using namespace std;
std::string ContaCorrente::getDadoExclusivo(){
    std::string Dados =to_string(this->num_cartao);
    return Dados;
}

ContaCorrente::~ContaCorrente(){

}

