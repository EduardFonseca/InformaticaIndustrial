#include <iostream>
#include <sensorvazao.h>
#include <vector>

using namespace std;

int main()
{
    vector<string> h = {"id", "unidade", "Numero de amostras", "Periodo de amostragem (s)"};
    SensorVazao sensor("D:\\arquivos\\Arquivos\\GitHub\\InformaticaIndustrial\\semana_3_e_4\\aula_semana_3.3\\dados\\dados.csv", h);
    sensor.lerDados();
    sensor.print();
    string horaf = "07:33:28", horai = "07:17:00";
    int resp = sensor.salvarDados("D:\\arquivos\\Arquivos\\GitHub\\InformaticaIndustrial\\semana_3_e_4\\aula_semana_3.3\\dados\\dadosSalvos.csv", horai, horaf);
    if (resp == 0)
    {
        cout << "Dados salvos com sucesso" << endl;
    }
    else
    {
        cout << "Erro: " << resp;
    }

    return 0;
}