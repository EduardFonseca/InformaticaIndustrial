#ifndef MOBILEROBOT_H
#define MOBILEROBOT_H

class MobileRobot
{
private:

protected:
    double PosicaoAtual[3];
public:
    MobileRobot();
    MobileRobot(double X,double Y,double Z);
    ~MobileRobot();

    void getPosicaoAtual(double* coordenada);
    void setPosicaoAtual(double X,double Y, double Z);
    void print();
    virtual void mover(double Xvel, double Yvel, double Zvel, double tempo) = 0;
};


#endif