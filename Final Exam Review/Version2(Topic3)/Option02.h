#pragma once

namespace fre{
    // Get input data
    int GetInputData(int &N, double &K);
    
    //PriceByCRR
    double *PriceByCRR(double S0, double U, double D, double R, int N, double K, double (*Payoff)(double z, double K)); 
    
    // Payoff functions
    double CallPayoff(double z, double K);
    double PutPayoff(double z, double K); 
    double DigitalCallPayoff(double z, double K);
    double DigitalPutPayoff(double z, double K);
    
}