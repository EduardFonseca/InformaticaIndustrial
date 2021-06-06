#include "MobileRobot.h"
#include <iostream>

using namespace std;

MobileRobot::MobileRobot(){
    this->setPosicaoAtual(0,0,0);
}

MobileRobot::MobileRobot(double X,double Y,double Z){
    this->setPosicaoAtual(X,Y,Z);
}

MobileRobot::~MobileRobot(){
    cout<<"Destrutor da classe MobileRobot invocado."<<endl;
}

void MobileRobot::getPosicaoAtual(double* coordenada){
    coordenada[0] = this->PosicaoAtual[0];
    coordenada[1] = this->PosicaoAtual[1];
    coordenada[2] = this->PosicaoAtual[2];
}

void MobileRobot::setPosicaoAtual(double X,double Y, double Z){
    this->PosicaoAtual[0] = X;
    this->PosicaoAtual[1] = Y;
    this->PosicaoAtual[2] = Z;
}

void MobileRobot::print(){
    cout<<"X: "<<this->PosicaoAtual[0]<<" | Y: "<<this->PosicaoAtual[1]<<" | Z: "<<this->PosicaoAtual[2]<<endl;
}