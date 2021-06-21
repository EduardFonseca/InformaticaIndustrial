#include <conta_poupanca.h>
#include <contas.h>

#include <math.h>
#include <iostream>
#include <string>

ContaPoupanca::ContaPoupanca(int senha, int conta, double saldo, std::string titular, std::string tipo,int taxa){
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
    this->conta = conta;
    this->tipo = tipo;
    this->taxa = taxa;
}

ContaPoupanca::~ContaPoupanca(){

}

int ContaPoupanca::dadoExclusivo(){
    return this->taxa;
}

void ContaPoupanca::SimulaRendimento(int num_meses){
    double rendimentos;
    //como poupanca e um juros composto temos a formula: rendimento=C(1+i)^t
    rendimentos=this->saldo*pow(1+(this->taxa*0.01),num_meses);

    std::cout<<"rendimento em "<<num_meses<<" meses foi de: R$"<<rendimentos<<std::endl;

}

