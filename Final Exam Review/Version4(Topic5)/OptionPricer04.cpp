#include "BinomialTreeModel02.h"
#include "Option04.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std; 
using namespace fre; 

int main()
{
    // initialize parameters
    int N = 8; 
    double U = 1.15125, D= 0.86862, R = 1.00545;
    double S0 = 106.00, K = 100.00;
    
    // create an object of the BinomialTreeModel class
    BinomialTreeModel BinModel(S0,U,D,R); 
    
    // create a pointer to a Call class object
    Call *pCall = new Call(N,K); 
    
    // create an object of the OptionCalculation class called "callOptionCalculation"
    // so inside the parameter list, we can pass our newly created "pCall" pointer!
    OptionCaculation callOptionCalculation(pCall); 
    
    cout<<"European Call option Price = "<<fixed<<setprecision(2)<<callOptionCalculation.PriceByCRR(BinModel)<<endl; 
    
    // free memory of pCall
    delete pCall; 
    pCall = NULL; 
    
    return 0; 
}

/*
European Call option Price = 21.68
*/