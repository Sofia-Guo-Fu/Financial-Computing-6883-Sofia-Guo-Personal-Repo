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
    
    // Original PriceByCRR
    double OptionCalculation::PriceByCRR(const BinomialTreeModel & Model)
    {
        double q = Model.RiskNeutProb(); 
        int N = pOption->GetN(); 
        vector <double> Price(N+1);
        
        for (int i=0;i<=N; i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        
        for(int n=N-1; n>=0; n--)
        {
            for (int i=0;i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q) * Price[i]) / Model.GetR();
            }
        }
        return Price[0]; 
    }
    
    // Overload: Modify the PriceByCRR function here in HW6
    double OptionCalculation:: PriceByCRR(const BinomialTreeModel &Model, BinLattice<double> &PriceTree,
                                BinLattice<double> &XTree, BinLattice<double> &YTree)
    {
        // q
        double q = Model.RiskNeutProb();
        // N
        int N = pOption -> GetN();
        // Set N for PriceTree, XTree, YTree
        PriceTree.SetN(N);
        XTree.SetN(N);
        YTree.SetN(N);
        // Contval
        double ContVal = 0;
        
        // populate nodes at expiration
        for (int i=0; i<=N;i++)
        {
            PriceTree.SetNode(N,i,pOption->Payoff(Model.CalculateAssetPrice(N,i)));
        }
        // construct the rest of the PriceTree
        for (int n=N-1; n>=0; n--)
        {
            for(int i=0; i<=n; i++)
            {
                ContVal = (q*PriceTree.GetNode(n+1,i+1) + (1-q)*PriceTree.GetNode(n+1,i))/Model.GetR();
                PriceTree.SetNode(n,i,ContVal);
            }
        }
        
        for(int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                // x(n,i) = (H(n+1,i+1) - H(n+1,i)) / (S(n+1,i+1) - S(n+1,i))
                double x = (PriceTree.GetNode(n+1,i+1) - PriceTree.GetNode(n+1,i)) / (Model.CalculateAssetPrice(n+1,i+1) - Model.CalculateAssetPrice(n+1,i)); 
                // y(n,i) = (H(n+1,i) - x(n,i)*S(n+1,i)) / R
                double y = (PriceTree.GetNode(n+1,i) - x * Model.CalculateAssetPrice(n+1,i)) / Model.GetR();
                
                // SetNode for XTree and YTree
                XTree.SetNode(n,i,x);
                YTree.SetNode(n,i,y); 
            }
        }
        return PriceTree.GetNode(0,0);
        
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