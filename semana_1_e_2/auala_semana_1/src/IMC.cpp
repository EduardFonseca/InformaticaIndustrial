#include <iostream>

using namespace std;

int main()
{
    float peso, altura,IMC;
    
    cout << "Digite seu peso:";
    cin >> peso;
    cout << "digite sua altura:";
    cin >> altura;
    
    IMC = peso/(altura*altura);
    
    if (IMC <= 18.5){
        cout << "O seu IMC e: " << IMC <<"\nVoce esta abaixo do peso." << endl;
    }
    else if(IMC>18.5 && IMC<=24.9){
        cout << "O seu IMC e: " << IMC <<"\nVoce esta com o peso normal." << endl;
    }
    else if(IMC>24.9 && IMC<=30){
        cout << "O seu IMC e: " << IMC <<"\nVoce esta acima do peso." << endl;
    }
    else {
        cout << "O seu IMC e: " << IMC <<"\nVoce esta obeso." << endl;
    }

    return 0;
}