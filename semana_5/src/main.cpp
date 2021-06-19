#include <iostream>
#include <vector>
#include "Contas.h"

using namespace std;

int main(){
    vector<Contas> c;
    c.push_back({1234,03,20000,"jodinei","corrente"});
    c.push_back({0000,02,2000,"debora","corrente"});
    c.push_back({4321,01,1000,"aparecida","corrente"});
    Contas* pcontas[10];
    for(int i=0; i<c.size();i++){
        pcontas[i]=&c[i];
    }

    c[0].transferencia(1,pcontas,c.size());
    c[2].getSaldo(4321);

    return 0;
}
