#include "pilha.hpp"
#include <iostream>
#include <fila.hpp>

using namespace std;

int main(){
    Pilha<int> p1(10);
    Fila<int> f1(10);

//teste commit
    cout<<"valores inseridos"<<endl;
    for(int i = 0;i<p1.getTam();i++){
        cout<<"pilha: "<<i+1<<" | fila: "<<i+1<<endl;
        p1.insere(i+1);
        f1.insere(i+1);
    }

    cout<<"\nvalores retirados : "<<endl;
    for(int i = 0;i<2;i++){
        int valorPilha,valorFila;
        p1.remove(valorPilha);
        f1.remove(valorFila);
        cout<<"pilha: "<<valorPilha<<" | fila: "<<valorFila<<endl;
    }
    p1.insere(11);
    p1.insere(12);
    f1.insere(11);
    f1.insere(12);

    cout<<"\nvalores retirados : "<<endl;
    for(int i = 0;i<p1.getTam();i++){
        int valorPilha,valorFila;
        p1.remove(valorPilha);
        f1.remove(valorFila);
        cout<<"pilha: "<<valorPilha<<" | fila: "<<valorFila<<endl;
    }

}
