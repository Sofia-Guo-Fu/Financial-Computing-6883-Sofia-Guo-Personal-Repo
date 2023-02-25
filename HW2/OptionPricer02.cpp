#include "BinomialTreeModel.h"
#include "Option02.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace fre;
int main()
{
    double S0 = 0.0,U=0.0,D=0.0,R=0.0;
    if (GetInputData(S0,U,D,R)!=0) return -1;
    double K= 0.0;
    int N=0; //steps to expiry
    
    
    cout<<"Enter call option data:"<<endl;
    GetInputData(N,K);
    double * optionPrice = NULL;
    
    // European call option 
    optionPrice = PriceByCRR(S0,U,D,R,N,K,CallPayoff);
    cout<<"European Call Option Price="<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete[] optionPrice;
    
    // European put option
    optionPrice = PriceByCRR(S0,U,D,R,N,K,PutPayoff);
    cout<<"European Put Option price="<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete[] optionPrice;
    
    //Digital call option
    optionPrice= PriceByCRR(S0,U,D,R,N,K,DigitalCallPayoff);
    cout<<"Digital Call Option Price="<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete[] optionPrice;
    
    //Digital put option 
    optionPrice= PriceByCRR(S0,U,D,R,N,K,DigitalPutPayoff);
    cout<<"Digital Put Option Price="<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete[] optionPrice;
    
    optionPrice = NULL;
    return 0;
    
    
}


// I've got the correct answer:
/* 

Enter S0: 106
Enter U:  1.15125
Enter D:  0.86862
Enter R:  1.00545

Input data checked
There is no arbitrage

Enter call option data:
Enter steps to expiry N: 8
Enter strike price K: 100

European Call Option Price=21.68
European Put Option price=11.43
Digital Call Option Price=0.58
Digital Put Option Price=0.38

*/