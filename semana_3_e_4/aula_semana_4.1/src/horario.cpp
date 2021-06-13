#include <iostream>
#include <iomanip>
#include "horario.h"


Horario::Horario(int h,int m,int s){
    this->SetHorario(h,m,s);
}

Horario::~Horario(){
    std::cout<<"destrutor da classe Horario invocado"<<std::endl;
}

void Horario::SetHorario(int h, int m,int s){
    this->SetHora(h);
    this->SetMinunto(m);
    this->SetSegundo(s);
}

void Horario::SetHora(int h){
    this->hora = (h>=0 && h<24) ? h : 0;
}

void Horario::SetMinunto(int m){
    this->minuto = (m>=0 && m<60) ? m : 0;
}

void Horario::SetSegundo(int s){
    this->segundo = (s>=0 && s<60) ? s : 0;
}

int Horario::GetHora() const{
    return this->hora;
}

int Horario::GetMinuto() const {
    return this->minuto;
}

int Horario::GetSegundo() const {
    return this->segundo;
}

void Horario::print() const{
    std::cout<<std::setfill('0')<<std::setw(2)<<this->GetHora()<<":"<<std::setfill('0')<<std::setw(2)<<this->GetMinuto()<<":"<<std::setfill('0')<<std::setw(2)<<this->GetSegundo()<<std::endl;
}