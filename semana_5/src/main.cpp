#include <iostream>
#include <vector>
#include <string>
#include <banco.h>

using namespace std;

int main(){

    Banco b1("joselia",1234,"D:\\arquivos\\Arquivos\\GitHub\\InformaticaIndustrial\\semana_5\\dados\\contas.csv");

    b1.nova_conta(b1.login_gerente());

    return 0;
}
