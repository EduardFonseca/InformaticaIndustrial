#include <iostream>
#include "Quadrotor.h"
#include "MobileRobot.h"

using namespace std;

//criacao dos construtores e destrutores
Quadrotor::Quadrotor() : MobileRobot::MobileRobot(){

}

Quadrotor::Quadrotor(double X,double Y,double Z) : MobileRobot::MobileRobot(X,Y,Z){

}

Quadrotor::~Quadrotor(){
    cout<<"Destrutor da classe Quadrotor invocado."<<endl;
}

void Quadrotor::mover(double Xvel, double Yvel, double Zvel, double tempo){
    cout<<"Acionando helices...."<<endl;
    cout<<"Posicao antes de se mover:"<<endl;
    cout<<"X: "<<this->PosicaoAtual[0]<<" | Y: "<<this->PosicaoAtual[1]<<" | Z: "<<this->PosicaoAtual[2]<<endl;
    this->PosicaoAtual[0] += Xvel*tempo;
    this->PosicaoAtual[1] += Yvel*tempo;
    this->PosicaoAtual[2] += Zvel*tempo;
    cout<<"Posicao depois de se mover:"<<endl;
    cout<<"X: "<<this->PosicaoAtual[0]<<" | Y: "<<this->PosicaoAtual[1]<<" | Z: "<<this->PosicaoAtual[2]<<"\n"<<endl;
}