
double fac(double num){
    double result=1;
    for(int i=1; i <= num;i++){
        result=result*i;
    }
    return result;
}

double power(double num, int ex){
    float result=1;
    for(int i=0; i<ex ; i++){
        result*=num;
    }
    return result;
}

double y(double x,int grau){
    float result=0;
    for (int i=grau; i>=2 ; i--){
         result+=fac(i)*power(x,i-2);
         
    }
    return result;

}
