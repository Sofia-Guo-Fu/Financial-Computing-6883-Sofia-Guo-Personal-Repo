#include "BinomialTreeModel02.h"
#include "Option03.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std; 
using namespace fre; 

int main()
{
    // initialize the parameters
    int N=8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K=100.00;
    
    // create an object BinModel of the class BinomialTreeModel
    BinomialTreeModel BinModel(S0,U,D,R);
    
    // initialize a NULL array 
    double * optionPrice = NULL; 
    // pass the value to optionPrice to whatever the PriceByCRR function gives us
    optionPrice = PriceByCRR(BinModel, N, K, CallPayoff); 
    cout<<"European call option price is: "<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete [] optionPrice;
    
    // pass it agin to putpayoff
    optionPrice = PriceByCRR(BinModel,N,K,PutPayoff);
    cout<<"European put option price is: "<<fixed<<setprecision(2)<<optionPrice[0]<<endl;
    delete [] optionPrice;
    
    optionPrice = NULL; 
    return 0.0; 
}

/*

European call option price is: 21.68
European put option price is: 11.43

*/