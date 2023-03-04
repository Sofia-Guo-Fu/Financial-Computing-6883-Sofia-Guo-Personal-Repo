#include <iostream>
#include <cmath>
#include "Option05.h"
#include "BinomialTreeModel02.h"

using namespace std;
namespace fre
{   
    //destructor of EurOption outside
    EurOption::~EurOption(){}
    
    // define Payoff member function of Call class
    double Call::Payoff(double z) const
    {
        if (z>K) return z-K;
        return 0.0;
    }
    //define Payoff memeber function of Put class
    double Put::Payoff(double z) const
    {
        if (K>z) return K-z;
        return 0.0;
    }
    
    // define Payoff memeber function of BullSpread class
    double BullSpread::Payoff(double z) const
    {
        if (z<=K1) return 0.0;
        else if (K1<z && z<K2) return (z-K1);
        else if (z>=K2) return (K2-K1);
        return 0.0; 
    }
    
    // define Payoff member function of BearSpread class
    double BearSpread::Payoff(double z) const
    {
        if (z<=K1) return (K2-K1);
        else if (K1<z && z<K2) return (K2-z);
        else if (z>=K2) return 0.0; 
        return 0.0; 
    }
    
    // define member function PriceByCRR of OptionCalculation class
    double OptionCalculation::PriceByCRR(const BinomialTreeModel & Model)
    {   
        // initialize optionPrice = 0.0 first 
        double optionPrice = 0.0;
        double q = Model.RiskNeutProb();
        //pOption belongs to EurOption class
        int N = pOption -> GetN();
        // dynamic memeory allocation of pPrice array 
        double *pPrice = new double[N+1];
        
        for (int i=0;i<=N;i++)
        {
            pPrice[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i));
        }
        
        for (int n=N-1; n>=0;n--)
        {
            for (int i=0; i<=n;i++)
            {
                pPrice[i] = (q * pPrice[i+1] + (1-q) * pPrice[i]) / Model.GetR();
            }
        }
        
        optionPrice = pPrice[0];
        delete [] pPrice;
        pPrice = nullptr;
        return optionPrice;
        
    }
    
}
