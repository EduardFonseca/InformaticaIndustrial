#ifndef QUADROTOR_H
#define QUADROTOR_H

#include "MobileRobot.h"

class Quadrotor : public MobileRobot
{
private:

public:
    Quadrotor();
    Quadrotor(double X,double Y,double Z);
    ~Quadrotor();

    void mover(double Xvel, double Yvel, double Zvel, double tempo);
};

#endif