#include "sensorindustrial.h"
#include <iostream>

using namespace std;

SensorIndustrial::SensorIndustrial(const string& identificador,const string& un) : id(identificador),unidade(un),
dados(nullptr), numMed(0){

}

SensorIndustrial::~SensorIndustrial(){

    this->limpaDados();
    cout<< "Destrutor da calsse SesnsorIndustrial invocado."<<endl;
}

void SensorIndustrial::setId(const string& id){
    this->id=id;
}

void SensorIndustrial::setUnidade(const string& un){
    this->unidade= un;
}

void SensorIndustrial::lerDados(const Medicao* dadosNovos, const int& numdados){
    this->limpaDados();
    this->numMed = numdados;
    this->dados = new Medicao[this->numMed];

    for(int i = 0; i< this->numMed;i++){
        this->dados[i] = dadosNovos[i];
    }
}

void SensorIndustrial::limpaDados(){
    if(this->dados != nullptr){
        delete[] this->dados;
        this->dados = nullptr;
        this->numMed=0;
    }
}

string SensorIndustrial::getId(){
    return this->id;
}

string SensorIndustrial::getUnidade(){
    return this->unidade;
}

int SensorIndustrial::getNumMed(){
    return this->numMed;
}

int SensorIndustrial::getDados(Medicao* d){
    d = this->dados;
    return this->getNumMed();
}

bool SensorIndustrial::getDado(const string& h, Medicao& med){
    for(int i=0 ; i<this->numMed;i++){
        if(this->dados[i].horario == h){
            med = this->dados[i];
            return true;
        }
    }
    return false;
}

void SensorIndustrial::print(){
    cout<<"Dados do sensor"<<this->getId()<<" :"<<endl;
    for(int i=0 ; i<this->numMed;i++){
        cout<<"Horario: " << this->dados[i].horario<<" h | Medicao: "<<this->dados[i].valor<<" "<<this->unidade<<endl;
    }
}