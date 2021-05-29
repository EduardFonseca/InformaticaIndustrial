#include "Contas.h"
#include <iostream>

Contas::Contas(){
    this->titular = "";
    this->saldo = 0;
    this->senha = 0000;
}

Contas::Contas(int senha, double saldo , std::string titular){
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
}

void Contas::exibeDados(){
    std::cout<<"Titular :"<<this->titular<<"\nConta: "<<this->conta<<std::endl;
}

double Contas::getSaldo(int senha){

    if (senha== this->senha){
        return this->saldo;
    }else{
        std::cout<<"senha invalida"<<std::endl;
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