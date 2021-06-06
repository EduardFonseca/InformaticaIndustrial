#ifndef SENSOR_INDUSTRIAL_H
#define SENSOR_INDUSTRIAL_H

#include <string>
#include "medicao.h"

using namespace std;

class SensorIndustrial
{
private:
    string id;
    string unidade;
    int numMed;
protected:
    Medicao* dados;
public:
    SensorIndustrial(const string& identificador,const string& un);
    ~SensorIndustrial();

    //funcoes set
    void setId(const string& id);
    void setUnidade(const string& un);
    virtual void lerDados(const Medicao* dadosNovos,const int& numdados);
    virtual void limpaDados();

    //funcoes get

    string getId();
    string getUnidade();
    int getNumMed();
    int getDados(Medicao* d);
    bool getDado(const string& h, Medicao& med);
    virtual void print();
};

#endif
