#include <iostream>
#include "Contas.h"

using namespace std;

int main(){
    Contas c[10]={{1234,01,20000,"jodinei","corrente"},{0000,02,2000,"debora","corrente"},{4321,01,1000,"aparecida","corrente"}};
    Contas* pcontas[10];

    for( int i=0; i< sizeof(c)/sizeof(c[0]);i++){
        pcontas[i]=&c[i];
    }

    pcontas[0]->transferencia(02,pcontas);
    pcontas[1]->getSaldo(0000);

    return 0;
}