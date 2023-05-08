#include "BinomialTreeModel.h"
#include "Option02.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std; 
using namespace fre; 

int main()
{
    // variable initialization
    double S0=0.0, U=0.0, D=0.0, R=0.0; 
    if (GetInputData(S0,U,D,R) != 0) return -1; 
    double K = 0.0;
    int N = 0;
    
    // Get option data
    cout<<"Enter option data: "<<endl;
    
    GetInputData(N,K); //前面不要带int！！
    
    double *optionPrice = NULL;
    
    // optionPrice calculation, function pointer as parameter, pass function name as argument
    // call option price
    optionPrice = PriceByCRR(S0,U,D,R,N,K,CallPayoff);
    cout<<"European call option price = "<<fixed<<setprecision(2)<<optionPrice[0]<<endl; 
    delete [] optionPrice;
    
    // put option Price
    optionPrice = PriceByCRR(S0,U,D,R,N,K,PutPayoff);
    cout<<"European put option price = "<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete [] optionPrice;
    
    //digital call option price
    optionPrice = PriceByCRR(S0,U,D,R,N,K, DigitalCallPayoff); 
    cout<<"European digital call option price = "<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete [] optionPrice;
    
    // digital put option price
    optionPrice = PriceByCRR(S0,U,D,R,N,K,DigitalPutPayoff); 
    cout<<"European digital put option price = "<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete [] optionPrice;
    
    optionPrice = NULL; 
    return 0; 
    
    
}




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