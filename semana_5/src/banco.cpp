#include "banco.h"
#include "contas.h"
#include "conta_corrente.h"
#include "conta_poupanca.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

Banco::Banco(string nome, int senha, string path)
{
    this->gerente.nome = nome;
    this->gerente.senha = senha;
    this->path=path;
    this->leitura_dados(this->path);
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
        Contas *newContas = new Contas[this->num_contas + 1]; //criacao do espaco de memoria novo para as novas contas

        //alocacao das novas contas no espaco de memoria temporaria
        for (int i = 0; i < this->num_contas; i++)
        {
            newContas[i] = this->pcontas[i];
        }
        newContas[num_contas] = this->cria_conta(); //funcao q adiciona a conta pelo terminal
        this->num_contas += 1;

        delete[] this->pcontas;
        this->pcontas = new Contas[num_contas];

        //retorno das contas para o ponterio de contas da classe Banco
        for (int i = 0; i < this->num_contas; i++)
        {
            this->pcontas[i] = newContas[i];
        }
        delete[] newContas;
        this->salva_arquivo();
        return true;
    }
    return false;
}

Contas Banco::cria_conta(int senha,int conta,double saldo, string titular, string tipo_de_conta,int dado_extra)
{
    if (tipo_de_conta == "Corrente")
    {
        ContaCorrente newConta(senha, conta, saldo, titular, tipo_de_conta, dado_extra);
        return newConta;
    }
    else if (tipo_de_conta == "Poupanca")
    {
        ContaPoupanca newConta(senha, conta, saldo, titular, tipo_de_conta, dado_extra);
        return newConta;
    }
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
    conta=this->num_contas+1;
    cout<<"Numero da conta: "<< conta <<endl;
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
        ContaCorrente newConta(senha, conta, saldo, titular, tipo_de_conta, num_cartao);
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

int Banco::get_num_contas()
{
    cout << "Atualmente o banco tem " << this->num_contas << " cadastradas" << endl;
    return this->num_contas;
}

bool Banco::salva_arquivo()
{
    try
    {
        ofstream ofile;
        ofile.open(this->path, ios_base::out | ios_base::trunc);
        if (ofile.is_open())
        {
            ofile << "%Contas banco" << endl;
            ofile << "Contas cadastradas: "<< this->num_contas<<endl;
        }
        for (int i = 0;i<this->num_contas;i++){

            ofile << this->pcontas[i].getSenha()<< "," << this->pcontas[i].conta<< "," << this->pcontas[i].titular<< "," << this->pcontas[i].tipo<< "," << this->pcontas[i].getSaldo(this->pcontas[i].getSenha()) << "," << this->pcontas[i].getDadoExclusivo()<<endl;

        }
    }
    catch (const std::exception &e)
    {
        cout << e.what() << '\n';
    }
}

bool Banco::leitura_dados(const string path){

    ifstream ifile;
    ifile.open(path);
    try
    {
        if(ifile.is_open()){
            string line;
            getline(ifile,line);
            int n=0;
            int idx;
            getline(ifile,line);
            idx=line.find(":");
            this->num_contas=stod(line.substr(idx + 2, line.size() - idx));

            this->pcontas = new Contas[this->num_contas];

            for(int i=0; i<this->num_contas;i++){
                getline(ifile,line);
                idx=line.find_first_of(",");
                int senha = stod(line.substr(0,idx));
                line=line.substr(idx+1,line.size()-idx);

                idx=line.find_first_of(",");
                int conta = stod(line.substr(0,idx));
                line=line.substr(idx+1,line.size()-idx);

                idx=line.find_first_of(",");
                string titular = line.substr(0,idx);
                line=line.substr(idx+1,line.size()-idx);

                idx=line.find_first_of(",");
                string tipo = line.substr(0,idx);
                line=line.substr(idx+1,line.size()-idx);

                idx=line.find_first_of(",");
                double saldo = stod(line.substr(0,idx));
                int dadoextra = stod(line.substr(idx+1,line.size()-idx));

                this->pcontas[i] = this->cria_conta(senha,conta,saldo,titular,tipo,dadoextra);
            }
        }else {
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
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
