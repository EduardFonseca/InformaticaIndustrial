#ifndef ROBOTERRESTRE_H
#define ROBOTERRESTRE_H

#include <MobileRobot.h>

class RoboTerrestre : public MobileRobot
{
private:

public:
    RoboTerrestre();
    RoboTerrestre(double X, double Y);
    ~RoboTerrestre();

    void setPosicaoAtual(double X,double Y);
    void mover(double Xvel, double Yvel, double Zvel, double tempo);
};

#endif