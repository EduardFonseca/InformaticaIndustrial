#include "sensorindustrial.h"
#include "medicao.h"
#include "sensorcomajuste.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

SensorComAjuste::SensorComAjuste(const string& indentificador, const string& un)
: SensorIndustrial::SensorIndustrial(indentificador,un), dadosAjustados(nullptr){
    this->coefs=new double[2];
    this->coefs[0] = 0;
    this->coefs[1] = 1.0;
    this->numCoefs = 2;
}

SensorComAjuste::~SensorComAjuste(){
    this->limpaCoefs();
    this->limpaDados();
    std::cout<<"Destrutor da classe SensorComAjuste invocado."<<endl;
}

void SensorComAjuste::setCoefs(const double* c,const int& nCoef){
    this->limpaCoefs();
    this->numCoefs =nCoef;
    this->coefs= new double[this->numCoefs];

    for(int i=0; i<this->numCoefs;i++){
        this->coefs[i]=c[i];
    }
    this->ajustardados();
}

void SensorComAjuste::getCoefs(int& nCoefs, double* c){
    nCoefs = this->numCoefs;
    coefs = this->coefs;
}

void SensorComAjuste::lerDados(const Medicao* m, const int& ndados){
    this->limpaDados();
    SensorIndustrial::lerDados(m,ndados);
    this->dadosAjustados=new Medicao[ndados];
    this->ajustardados();
}

void SensorComAjuste::limpaDados(){
    SensorIndustrial::limpaDados();
    if(this->dadosAjustados != nullptr){
        delete[] this->dadosAjustados;
        this->dadosAjustados = nullptr;
    }
}

void SensorComAjuste::limpaCoefs(){
    if(this->coefs != nullptr){
        delete[] this->coefs;
        this->coefs = nullptr;
        this->numCoefs=0;
    }
}

void SensorComAjuste::print(){
    std::cout<<"dados ajustados do sensor "<<this->getId()<<" : "<<endl;
    for(int i=0 ; i<this->getNumMed();i++){
        cout<<"Horario: " << this->dadosAjustados[i].horario<<" h | Medicao: "<<this->dadosAjustados[i].valor<<" "<<this->getUnidade()<<endl;
    }
}

void SensorComAjuste::ajustardados(){
    if(this->dadosAjustados!= nullptr){
        memset(this->dadosAjustados,0,this->getNumMed()*sizeof(Medicao));
        for(int i=0;i<this->getNumMed();i++){
            this->dadosAjustados[i].horario = this->dados[i].horario;
            for(int j=0;j<this->numCoefs;j++){
                this->dadosAjustados[i].valor += this->coefs[j]*pow(this->dados[i].valor,j);
            }
        }
    }
}