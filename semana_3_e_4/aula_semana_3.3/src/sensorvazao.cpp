#include <sensorvazao.h>
#include <iostream>

using namespace std;

SensorVazao::SensorVazao(const string &path, const vector<string> &h) : id("desconhecido"), unidade("desconhecida"), numMed(0)
{
    this->headers.assign(h.begin(), h.end());
    this->abrirArquivo(path);
}

SensorVazao::~SensorVazao()
{
    this->file.close();
}

bool SensorVazao::abrirArquivo(const string &path)
{

    try
    {
        this->file.open(path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
    return false;
}

bool SensorVazao::lerDados()
{
    try
    {
        if (this->file.is_open())
        {
            string d;
            getline(this->file, d);
            int n = 0;
            int idx;
            vector<string> dadosHeader(this->headers.size());
            while (n < this->headers.size())
            {
                getline(this->file, d);
                idx = d.find(":");
                if (d.substr(0, idx) == this->headers[n])
                {
                    dadosHeader[n] = d.substr(idx + 1, d.size() - idx);
                    n++;
                }
                else
                {
                    return false;
                }
            }
            this->id = dadosHeader[0];
            this->unidade = dadosHeader[1];
            this->numMed = stod(dadosHeader[2]);
            this->Ts = stod(dadosHeader[3]);

            Medicao m;
            getline(this->file, d);

            for (int i = 0; i < this->numMed; i++)
            {
                getline(this->file, d);
                idx = d.find(",");
                m.horario = d.substr(0, idx);
                m.valor = stod(d.substr(idx + 1, d.size() - idx));
                this->dados.push_back(m);
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "arquivo corrompido" << e.what() << '\n';
    }
}

string SensorVazao::getId()
{
    return this->id;
}

string SensorVazao::getUnidade()
{
    return this->unidade;
}

int SensorVazao::getPeriodoDeAmostragem()
{
    return this->Ts;
}

int SensorVazao::getNumMed()
{
    return this->numMed;
}

bool SensorVazao::getDado(const string &horario, double &dado)
{

    for (auto it = this->dados.begin(); it != this->dados.end(); it++)
    { //it e um iterador que funciona como pintiro dos dados assim sera feita a leitura de todas as medicoes
        if (it->horario == horario)
        {
            dado = it->valor;
            return true;
        }
    }
    return false;
}

int SensorVazao::salvarDados(const string &path, const string &horai, const string &horaf)
{
    bool flags[2] = {false, false}; // serve para fazer a busca do horai e horaf e retornar se eles foram achados ou nao
    try
    {
        ofstream ofile;                                              //arquivo de output
        ofile.open(path, std::ios_base::out | std::ios_base::trunc); //std::ios_base::out | std::ios_base::trunc -> estou falando q e um aquivo do tipo de saida e estou apagando todos os valores nele existentes caso existam
        if (ofile.is_open())
        {
            ofile << "Dados sensor de vazao" << endl;
            ofile << "ID: " << this->id << endl;
            ofile << "unidade: " << this->unidade << endl;
            ofile << "Numero de amostras: " << this->numMed << endl;
            ofile << "Periodo de amostragem " << this->Ts << endl;
            ofile << "Horario,dado" << endl;
        }

        for (auto it = this->dados.begin(); it != this->dados.end(); it++)
        {
            if (it->horario == horai)
            {
                flags[0] = true;
            }
            if (flags[0] && ~flags[1]) //verifica se o vetor inicial existe e se nao envontrou o vetor final
            {
                ofile << it->horario << "," << it->valor << endl;
            }
            if (it->horario == horaf)
            {
                flags[1] = true;
                return 0;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
    if (flags[0] && ~flags[1])
    {
        return 1; //apenas horario inicial encontrado
    }
    else
    {
        return 2; //horario inicial nao encontrado ou apenas o horario final encontrado
    }
}

void SensorVazao::print()
{
    cout << "SensorVazao " << endl;
    cout << "ID: " << this->id << endl;
    cout << "Numero de amostras: " << this->numMed << endl;
    cout << "Periodo de amostragem " << this->Ts << endl;

    for (auto it = this->dados.begin(); it != this->dados.end(); it++)
    { //it e um iterador que funciona como pintiro dos dados assim sera feita a leitura de todas as medicoes
        cout << "Horario: " << it->horario << " h | Valor: " << it->valor << " " << this->unidade << endl;
    }
}