#pragma once

namespace fre{
    // get option data 
    int GetInputData(int &N, double &K); 
    
    // Pricing European option PriceByCRR
    double PriceByCRR(double S0, double U, double D, double R, double K, int N); 
    
    // Call Pay off funciton 
    double CallPayOff(double z, double K); 
}