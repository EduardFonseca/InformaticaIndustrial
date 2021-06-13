#ifndef HORARIO_H
#define HORARIO_H

class Horario
{
private:
    int hora;
    int minuto;
    int segundo;
public:
    Horario(int h =0, int m=0, int s=0);
    ~Horario();

    //funcoes set
    void SetHorario(int h,int m,int s);
    void SetHora(int h);
    void SetMinunto(int m);
    void SetSegundo(int s);

    //funcoes get
    int GetHora()  const;
    int GetMinuto() const;
    int GetSegundo() const;

    void print() const;
};


#endif
