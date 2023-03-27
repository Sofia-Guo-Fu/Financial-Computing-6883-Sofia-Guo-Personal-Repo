#include "BlackScholes.h"
#include <iostream>
#include <cmath>

using namespace std; 

namespace fre{
    
    double BlackScholes::cal_U()
    {
        return exp(sigma * sqrt(T/N)); 
    }
    
    double BlackScholes::cal_D()
    {
        return 1 / (exp(sigma * sqrt(T/N))); 
    }
    
    double BlackScholes::cal_R()
    {
        return exp(r*T/N); 
    }
    
    BinomialTreeModel BlackScholes::BinomialTree()
    {
        return BinomialTreeModel(S0, cal_U(), cal_D(), cal_R()); 
    }
    
}