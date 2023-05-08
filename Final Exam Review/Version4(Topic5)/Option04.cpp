#include "BinomialTreeModel02.h"
#include "Option04.h"
#include <iostream>
#include <cmath>
#include <string.h> // for memset()

using namespace std;

namespace fre{
    
    // define payoff member function in class Call
    double Call::Payoff(double z) const
    {
        if (z>K) return (z-K); 
        return 0.0;
    }
    
    // define PriceByCRR function in OptionCalculation class
    double OptionCaculation::PriceByCRR(BinomialTreeModel & Model)
    {
        // first, initialize a result variable optionPrice
        double optionPrice = 0.0;
        // then, declare risk-neutral q
        double q = Model.RiskNeutProb(); 
        
        // Next, we also need to get N, to know how big should the Price array be
        // How to realize it？ Via our pOption, it is a pointer to the Call class
        int N = pOption->GetN(); 
        
        // create a Price array via dynamic memory allocation
        double *Price = new double[N+1]; // don't forget * 
        memset(Price,0,N+1); 
        
        // populate the nodes at expiration
        for (int i=0; i<=N; i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        // then discount back to calculate the payoff in each other nodes
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
            }
        }
        
        // finally assign optionPrice to Price[0]
        optionPrice = Price[0];
        
        // free memory 
        delete [] Price;
        Price = NULL; 
        return optionPrice; 
    }
}