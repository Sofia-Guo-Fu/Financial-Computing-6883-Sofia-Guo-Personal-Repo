#pragma once
#include "BinomialTreeModel02.h"

namespace fre{
    // normal independnt functions
    int GetInputData(int N, double K); 
    
    // PriceByCRR, here we pass Model instead of S0,U,D,R parameters like before
    double *PriceByCRR(const BinomialTreeModel &Model,int N, double K, double(*Payoff)(double z, double K)); 
    
    // Payoff functions 
    double CallPayoff(double z, double K);
    double PutPayoff(double z, double K); 
    
}