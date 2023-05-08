#include "BinomialTreeModel02.h"
#include "BinLattice02.h"
#include "Option08.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

namespace fre{
    // destructor for Option class
    Option::~Option(){}
    
    double Call::Payoff(double z) const
    {
        if (z>K) return (z-K);
        return 0.0; 
    }
    
    double Put::Payoff(double z) const
    {
        if (z<K) return (K-z);
        return 0.0; 
    }
    
    double OptionCalculation::PriceByCRR(const BinomialTreeModel &Model)
    {
        // q
        double q = Model.RiskNeutProb();
        // N
        int N = pOption->GetN(); 
        
        //Price is a vector of double of size (N+1)
        vector<double>Price(N+1); 
        
        for(int i=0; i<=N;i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        
        for (int n=N-1;n>=0;n--)
        {
            for (int i=0;i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
            }
        }
        return Price[0]; 
    }
    
    // PriceBySnell!!
    double OptionCalculation::PriceBySnell(const BinomialTreeModel &Model, 
                                BinLattice<double>&PriceTree, BinLattice<bool>&StoppingTree)
    {
        double q = Model.RiskNeutProb();
        // N
        int N = pOption->GetN();
        // Set N for both PriceTree and StoppingTree
        PriceTree.SetN(N);
        StoppingTree.SetN(N);
        
        // initialize ContVal
        double ContVal = 0;
        
        for(int i=0;i<=N;i++)
        {
            PriceTree.SetNode(N,i,pOption->Payoff(Model.CalculateAssetPrice(N,i))); 
            StoppingTree.SetNode(N,i,1);
        }
        
        for(int n=N-1;n>=0;n--)
        {
            for(int i=0;i<=n;i++)
            {
                // first define ContVal as discount back
                ContVal = (q*PriceTree.GetNode(n+1,i+1) + (1-q)*PriceTree.GetNode(n+1,i))/Model.GetR();
                PriceTree.SetNode(n,i,pOption->Payoff(Model.CalculateAssetPrice(n,i)));
                StoppingTree.SetNode(n,i,1);
                
                if (ContVal > PriceTree.GetNode(n,i)) // PriceTree.GetNode(n,i)
                {
                    PriceTree.SetNode(n,i,ContVal);
                    StoppingTree.SetNode(n,i,0);
                }
                else if(PriceTree.GetNode(n,i) == 0.0)
                {
                    StoppingTree.SetNode(n,i,0);
                }
            }
        }
        return PriceTree.GetNode(0,0); 
    }
}