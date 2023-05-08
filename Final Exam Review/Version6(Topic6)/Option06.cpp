#include "BinomialTreeModel02.h"
#include "Option06.h"
#include <iostream>
#include <cmath>
#include <vector> // to later create this type 
#include <string.h>

using namespace std;

namespace fre{
    // define a estructor for Option
    Option::~Option(){}
    // define call Payoff function
    double Call::Payoff(double z) const
    {
        if(z>K) return (z-K); 
        return 0.0;
    }
    // define Put Payoff function
    double Put::Payoff(double z) const
    {
        if (z<K) return (K-z); 
        return 0.0; 
    }
    
    // define PriceBycRR function
    double OptionCalculation::PriceByCRR(const BinomialTreeModel & Model)
    {
        // q
        double q = Model.RiskNeutProb();
        // GetN
        int N = pOption->GetN(); 
        
        // define Price as a vector of double of size N+1
        vector<double>Price(N+1); 
        
        // populate the nodes at expiration
        for (int i=0; i<=N; i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        
        // populate the rest of the nodes
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n;i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
            }
        }
        return Price[0]; 
    }
    
    // define PriceBySnell function
    double OptionCalculation::PriceBySnell(const BinomialTreeModel &Model)
    {
        //q
        double q = Model.RiskNeutProb();
        //GetN
        int N = pOption->GetN(); 
        
        // define Price as a vector of double of size N+1
        vector<double>Price(N+1);
        
        // declare a variable called ContVal
        double ContVal = 0.0; 
        
        // populate the nodes at expiration
        for (int i=0; i<=N;i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i));
        }
        
        // populate the rest of the nodes
        for (int n=N-1; n>=0; n--)
        {
            for(int i=0;i<=n;i++)
            {
                // ConVal calculated using PriceByCRR function
                ContVal = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
                // Assume payoff at every node
                Price[i] = pOption->Payoff(Model.CalculateAssetPrice(n,i)); 
                if(ContVal>Price[i]) Price[i] = ContVal; 
            }
        }
        return Price[0];
    }
}