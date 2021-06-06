#include <iostream>
#include "RoboTerrestre.h"
#include "MobileRobot.h"

using namespace std;

RoboTerrestre::RoboTerrestre():MobileRobot::MobileRobot(){
}

RoboTerrestre::RoboTerrestre(double X, double Y): MobileRobot::MobileRobot(X,Y,0){
}

RoboTerrestre::~RoboTerrestre(){
    cout<<"Destrutor da classe robo terrestre invocado"<<endl;
}

void RoboTerrestre::setPosicaoAtual(double X, double Y){
    this->PosicaoAtual[0] = X;
    this->PosicaoAtual[1] = Y;
    this->PosicaoAtual[2] = 0;
}

void RoboTerrestre::mover(double Xvel, double Yvel, double Zvel, double tempo){
    cout<<"Acionando motores das rodas....."<<endl;
    cout<<"Posicao antes de se mover:"<<endl;
    cout<<"X: "<<this->PosicaoAtual[0]<<" | Y: "<<this->PosicaoAtual[1]<<" | Z: "<<this->PosicaoAtual[2]<<endl;
    this->PosicaoAtual[0] += Xvel*tempo;
    this->PosicaoAtual[1] += Yvel*tempo;
    this->PosicaoAtual[2] = 0;
    cout<<"Posicao depois de se mover:"<<endl;
    cout<<"X: "<<this->PosicaoAtual[0]<<" | Y: "<<this->PosicaoAtual[1]<<" | Z: "<<this->PosicaoAtual[2]<<"\n"<<endl;
}

