#pragma once

namespace fre{
    // compute risk-neutral probabilty
    double RiskNeutProb(double U, double D, double R); 
    
    // compute stock price at node n,i
    double CalculateAssetPrice(double S0, double U, double D, int n, int i); 

    // Get input data
    int GetInputData(double &S0, double &U, double &D, double &R); 
}