#include "BinomialTreeModel02.h"
#include "Option05.h"
#include <iostream>
#include <cmath>
#include <string.h> // for memset

using namespace std; 

namespace fre{
    // EurOption destructor outside??? 
    EurOption:: ~EurOption(){}
    
    // Call Payoff function
    double Call::Payoff(double z) const 
    {
        if (z>K) return (z-K);
        return 0.0;
    }
    
    // Put Payoff function
    double Put::Payoff(double z) const 
    {
        if (z<K) return (K-z); 
        return 0.0; 
    }
    
    // BullSpread payoff function
    double BullSpread::Payoff(double z) const 
    {
        if (z>=K2) return (K2-K1); 
        if (z>K1 && z<K2) return (z-K1); 
        return 0.0;
    }
    
    // BearSpread payoff function
    double BearSpread::Payoff(double z) const 
    {
        if (z<=K1) return (K2-K1); 
        if (z>K1 && z<K2) return (K2-z);
        return 0.0; 
    }
    
    double OptionCalculation::PriceByCRR(BinomialTreeModel & Model)
    {
        // initlize a variable to store result
        double optionPrice = 0.0; 
        
        // decalre q
        double q = Model.RiskNeutProb(); 
        
        // GetN()
        int N = pOption->GetN();
        
        // create empty price array
        double *Price = new double[N+1]; 
        memset(Price,0,N+1); 
        
        // populate nodes at expiration
        for (int i=0; i<=N; i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        
        // populate the rest of the nodes
        for (int n=N-1; n>=0;n--)
        {
            for (int i=0;i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
            }
        }
        
        optionPrice = Price[0];
        
        // free memory 
        delete Price;
        Price = NULL; 
        return optionPrice; 
        
    }
}