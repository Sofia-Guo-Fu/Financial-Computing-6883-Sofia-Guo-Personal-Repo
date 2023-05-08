#include <iostream>
#include <iomanip>
#include <cmath>
#include "Option05.h"
#include "BinomialTreeModel02.h"

using namespace std;
using namespace fre;

int main()
{
    // initialize the parameters
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K = 100.0;
    double K1 = 100, K2 = 110;
    // create an BinomialTreeModel object
    BinomialTreeModel Model(S0,U,D,R); 
    
    // create object for Call class and OptionCaclulation Class
    Call call(N,K); 
    OptionCalculation callCalculation(&call); // EurOption *pOption = &call, base class pointer associate with derived class objct's address
    cout<<"European call option price is: "<<fixed<<setprecision(2)<<callCalculation.PriceByCRR(Model)<<endl; 
    
    // Put
    Put put(N,K);
    OptionCalculation putCalculation(&put);
    cout<<"European put option price is: "<<fixed<<setprecision(2)<<putCalculation.PriceByCRR(Model)<<endl; 
    
    // Bull spread
    BullSpread bullspread(N,K1,K2);
    OptionCalculation bullspreadCalculation(&bullspread);
    cout<<"European bull spread price is: "<<fixed<<setprecision(2)<<bullspreadCalculation.PriceByCRR(Model)<<endl;
    
    //Bear spread
    BearSpread bearspread(N,K1,K2);
    OptionCalculation bearspreadCalculation(&bearspread);
    cout<<"European bear spread price is: "<<fixed<<setprecision(2)<<bearspreadCalculation.PriceByCRR(Model)<<endl; 
    
    return 0; 
    
}

/*

European call option price is: 21.68
European put option price is: 11.43
European bull spread price is: 4.72
European bear spread price is: 4.86

*/