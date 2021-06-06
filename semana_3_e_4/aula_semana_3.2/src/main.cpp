#include <iostream>
#include <random>
#include <iomanip>
#include <MobileRobot.h>
#include <Quadrotor.h>
#include <RoboTerrestre.h>

using namespace std;

double RandomDouble(int min, int max){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(min, max);
    return distr(eng);
}

void ExecutaMovimento(MobileRobot *ptr){
    double vel[3];
    for(int i = 0;i<3;i++){
        vel[i]=RandomDouble((rand() % -10),(rand() % 10 + 0));
    }
    double time = RandomDouble(0,rand() % 100);
    cout<<"\n\nvelocidades sorteadas"<<endl;
    cout<<"Xvel: "<<vel[0]<<" | Yvel: "<<vel[1]<<" | Zvel: "<<vel[2]<<endl;
    cout<<"o tempo do movmento foi: "<<time<<" segundos.\n"<<endl;
    ptr->mover(vel[0],vel[1],vel[2],time);
}

int main(){
    Quadrotor q;
    RoboTerrestre r;
    MobileRobot* m[] = {&q,&r};

    for(int i = 0;i < sizeof(m)/sizeof(m[0]); i++){
        ExecutaMovimento(m[i]);
    }

    return 0;
}