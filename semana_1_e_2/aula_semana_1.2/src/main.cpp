#include <iostream>
#include "mylib.h"

using namespace std;

int main(){
    cout<<y(3,5)<<endl;
    cout<<y(fac(3),5)<<endl;
    double pow=power(2,3);
    cout<<y(pow,5)<<endl;
    return 0;
}