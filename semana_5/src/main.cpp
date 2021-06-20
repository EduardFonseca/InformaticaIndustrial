#include <iostream>
#include <vector>
#include <banco.h>

using namespace std;

int main(){
    Banco b1("joselia",1234);
    b1.nova_conta(b1.login_gerente());
    b1.nova_conta(b1.login_gerente());
    return 0;
}
