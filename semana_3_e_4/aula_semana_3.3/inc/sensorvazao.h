#ifndef SENSOR_VAZAO_H
#define SENSOR_VAZAO_H

#include <vector>    //utilizacao de vetores de maneira mais eficas
#include <fstream>   // trabalho com leitira e edicao de arquivos
#include <medicao.h> // inclusao do Struct medicao

using namespace std;

class SensorVazao
{
private:
    vector<Medicao> dados;
    vector<string> headers;
    string id;
    string unidade;
    int numMed;
    int Ts; // periodo de amostragem
    ifstream file;

public:
    SensorVazao(const string &path, const vector<string> &h);
    ~SensorVazao();
    bool abrirArquivo(const string &path);
    bool lerDados();
    string getId();
    string getUnidade();
    int getPeriodoDeAmostragem();
    int getNumMed();
    bool getDado(const string &horario, double &dado);
    int salvarDados(const string &path, const string &horai, const string &horaf);
    void print();
};

#endif