#include "Contas.h"
#include <iostream>
#include <vector>
#include <algorithm>

Contas::Contas()
{
    this->titular = "";
    this->saldo = 0;
    this->senha = 0000;
    this->conta = 0;
    this->tipo = "";
}

Contas::Contas(int senha, int conta, double saldo, std::string titular, std::string tipo)
{
    this->titular = titular;
    this->saldo = saldo;
    this->senha = senha;
    this->conta = conta;
    this->tipo = tipo;
}

void Contas::exibeDados()
{
    std::cout << "Titular :" << this->titular << "\nConta: " << this->conta << "\nTipo: " << this->tipo << std::endl;
}

void Contas::getSaldo(int senha)
{
    if (senha == this->senha)
    {
        std::cout << "O saldo da conta " << this->conta << " atual e de R$: " << this->saldo << std::endl;
    }
    else
    {
        std::cout << "Senha invalida" << std::endl;
    }
}

void Contas::deposito()
{
    int senha = this->pedeSenha();
    double valor = this->pedeValor();
    if (senha == this->senha)
    {
        this->saldo += valor;
        std::cout << "deposito de R$" << valor << " realizado com sucesso." << std::endl;
    }
    else
    {
        std::cout << "senha invalida" << std::endl;
    }
}

void Contas::saque()
{
    int senha = this->pedeSenha();
    double valor = this->pedeValor();
    if (senha == this->senha)
    {
        this->saldo -= valor;
        std::cout << "saque de R$" << valor << " realizado com sucesso." << std::endl;
    }
    else
    {
        std::cout << "senha invalida" << std::endl;
    }
}

void Contas::transferencia(int conta, Contas *pc[], int tam)
{
    double valor;
    int senha = this->pedeSenha();
    if (senha == this->senha)
    {
        valor = this->pedeValor();
        //  TODO:
        //  fazer validacao da conta de destino
        int pos = this->verificacaoConta(conta, pc, tam);
        if (pos >= 0 && pos != this->conta)
        {
            pc[pos]->saldo += valor;
            this->saldo -= valor;
            std::cout << "Transferencia de R$" << valor << " realizada com sucesso apra a conta: " << conta << std::endl;
            this->getSaldo(senha);
        }
    }
    else
    {
        std::cout << "senha invalida" << std::endl;
    }
}

using namespace std;
int Contas::verificacaoConta(int conta, Contas *pc[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (pc[i]->conta == conta)
        {
            return i;
        };
    }
    cout << "conta inexixtente" << endl;
    return -1;
}

int Contas::pedeSenha()
{
    int senha;
    cout << "digite a senha: " << endl;
    cin >> senha;

    return senha;
}

double Contas::pedeValor()
{
    double valor;
    cout << "digite o valor desejado: " << endl;
    cin >> valor;
    if (valor > 0)
    {
        return valor;
    }
    else
    {
        cout << "valor invalido." << endl;
        return 0;
    }
}

Contas::~Contas()
{
    //std::cout << "destrutor da conta de: "<< this->titular<<"foi utilizado"<< std::endl;
}