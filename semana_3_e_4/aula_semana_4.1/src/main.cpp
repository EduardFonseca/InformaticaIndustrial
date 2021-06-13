#include <iostream>
#include <horario.h>

using namespace std;

int main(){
    Horario h1(12),h2(23,10);
    const Horario h3(10,00,23);
    cout<<"horario 1: ";
    h1.print();
    cout<<"horario 2: ";
    h2.print();
    cout<<"horario 3: ";
    h3.print();
}