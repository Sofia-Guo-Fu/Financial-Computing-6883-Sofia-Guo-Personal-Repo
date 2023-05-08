#include "BinomialTreeModel02.h"
#include "Option06.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace fre; 

int main()
{
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K = 100.00;
    
    // create an object of BinomialTreeModel
    BinomialTreeModel Model(S0,U,D,R); 
    
    // create object of Call class
    Call call(N,K); 
    OptionCalculation callCalculation(&call); 
    cout<<"European Call option price: "<<fixed<<setprecision(2)<<callCalculation.PriceByCRR(Model)<<endl; 
    cout<<"American Call option price: "<<fixed<<setprecision(2)<<callCalculation.PriceBySnell(Model)<<endl; 
    
    // create object of Put class
    Put put(N,K);
    OptionCalculation putCalculation(&put);
    cout<<"European Put option price: "<<fixed<<setprecision(2)<<putCalculation.PriceByCRR(Model)<<endl; 
    cout<<"American Put option price: "<<fixed<<setprecision(2)<<putCalculation.PriceBySnell(Model)<<endl; 
    
    return 0; 
}


/*

European Call option price: 21.68
American Call option price: 21.68
European Put option price: 11.43
American Put option price: 11.72

*/