#include "Contas.h"
#include <iostream>

Contas::Contas(){
    this->titular = "";
    this->saldo = 0;
    this->senha = 0000;
    this->conta=0;
    this->tipo = "";
}

Contas::Contas(int senha, int conta,double saldo , std::string titular, std::string tipo){
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
    this->conta = conta;
    this->tipo = tipo;
}

void Contas::exibeDados(){
    std::cout<<"Titular :"<<this->titular<<"\nConta: "<<this->conta<<"\nTipo: "<<this->tipo<<std::endl;
}

double Contas::getSaldo(int senha){

    if (senha== this->senha){
        std::cout<<"Seu saldo atual e de R$: "<<this->saldo<<std::endl;
        return this->saldo;
    }else{
        std::cout<<"Senha invalida"<<std::endl;
    }
}

void Contas::deposito(double valor, int senha){
    if (senha== this->senha){
        if (valor>0){
            this->saldo+=valor;
            std::cout<<"deposito de R$"<<valor<<" realizado com sucesso."<<std::endl;
        }else{
            std::cout<<"valor invalido"<<std::endl;
        }
    }else{
        std::cout<<"senha invalida"<<std::endl;
    }
}

void Contas::saque(double valor, int senha){
    if (senha== this->senha){
        if (this->saldo>valor){
            this->saldo-=valor;
            std::cout<<"saque de R$"<<valor<<" realizado com sucesso."<<std::endl;
        }else{
            std::cout<<"valor invalido"<<std::endl;
        }
    }else{
        std::cout<<"senha invalida"<<std::endl;
    }
}

void Contas::transferencia(int conta, int senha, double valor, Contas* pc[]){
    if(senha==this->senha){
        if(valor > 0 && valor < this->saldo){
            pc[conta-1]->saldo+=valor;
            this->saldo-=valor;
            std::cout<<"Transferencia de R$:"<<valor<<" realizada com sucesso apra a conta: "<<conta<<std::endl;
            this->getSaldo(senha);
        }else{
            std::cout<<"valor invalido"<<std::endl;
        }
    }else{
        std::cout<<"senha invalida"<<std::endl;
    }
}

Contas::~Contas(){
    // std::cout << "destrutor da conta de: "<< this->titular<<"foi utilizado"<< std::endl;
}