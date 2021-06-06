#ifndef SENSOR_COM_AJUSTE_H
#define SENSOR_COM_AJUSTE_H
#include "sensorindustrial.h"
#include "medicao.h"
#include <string>


class SensorComAjuste : public SensorIndustrial
{
private:
    double* coefs;
    int numCoefs;
    Medicao* dadosAjustados;
    void ajustardados();
public:
    SensorComAjuste (const string& identificador,const string& un);
    ~SensorComAjuste ();

    void setCoefs(const double* c, const int& nCoefs);
    void getCoefs(int& nCoefs,double* c);

    void lerDados(const Medicao* c, const int& ndados);
    void limpaDados();
    void limpaCoefs();
    void print();

};


#endif