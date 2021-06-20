#include "banco.h"
#include "contas.h"
#include "conta_corrente.h"
#include "conta_poupanca.h"
#include <iostream>
#include <string>

using namespace std;

Banco::Banco(string nome, int senha)
{
    this->gerente.nome = nome;
    this->gerente.senha = senha;
    this->num_contas = 0;
    this->pcontas = new Contas[num_contas];
}

Banco::~Banco()
{
    delete[] this->pcontas;
}

int Banco::login_gerente()
{
    int senha;
    cout << this->gerente.nome << " digite a senha: ";
    cin >> senha;
    if (senha == this->gerente.senha)
    {
        return senha;
    }
    else
    {
        cout << "Senha invalida." << endl;
        return -1;
    }
}

bool Banco::nova_conta(int senha_gerente)
{
    if (senha_gerente != -1)
    {
        Contas* newContas = new Contas[this->num_contas + 1]; //criacao do espaco de memoria novo para as novas contas

        //alocacao das novas contas no espaco de memoria temporaria
        for (int i = 0; i < this->num_contas; i++)
        {
            newContas[i] = this->pcontas[i];
        }
        newContas[num_contas] = this->cria_conta(); //funcao q adiciona a conta pelo terminal
        this->num_contas += 1;

        delete[] this->pcontas;
        this->pcontas=new Contas[num_contas];

        //retorno das contas para o ponterio de contas da classe Banco
        for (int i = 0; i < this->num_contas; i++)
        {
            this->pcontas[i] = newContas[i];
        }
        delete[] newContas;
        cout << "contas criadas com sucesso"<<endl;
        return true;
    }
    return false;
}

Contas Banco::cria_conta()
{
    string titular, tipo_de_conta;
    int senha, conta;
    double saldo;
    cout << "Digite o nome do titular da conta: ";
    cin >> titular;
    cout << "Digite o tipo de conta:";
    cin >> tipo_de_conta;
    cout << "Digite o numero da conta: ";
    cin >> conta;
    cout << "Digite a senha da conta: ";
    cin >> senha;
    cout << "Digite o saldo da conta: ";
    cin >> saldo;
    if (saldo < 0)
    {
        saldo = 0;
    }
     //criacao da conta no na devida categoria
    if (tipo_de_conta == "Corrente")
    {
        int num_cartao;
        cout << "Digite o numero do cartao: ";
        cin >> num_cartao;
        ContaCorrente newConta(senha, conta, saldo, titular,tipo_de_conta, num_cartao);
        return newConta;
    }
    else if (tipo_de_conta == "Poupanca")
    {
        double taxa;
        cout << "Digite taxa mensal da conta: ";
        cin >> taxa;
        ContaPoupanca newConta(senha, conta, saldo, titular, tipo_de_conta, taxa);
        return newConta;
    }
}

bool Banco::troca_gerente(int senha_gerente)
{
    if (senha_gerente != -1)
    {
        cout << "digite o nome do novo gerente: ";
        cin >> this->gerente.nome;
        cout << "digite a nova senha: ";
        cin >> this->gerente.senha;
        cout << this->gerente.nome << " cadastrado como gerente com sucesso." << endl;
        return true;
    }
    return false;
}
