#include "BinomialTreeModel02.h"
#include "BinLattice01.h"
#include "Option07.h" //大大小小错误
#include <iostream>
#include <cmath>

using namespace std; 

namespace fre{
    
    // define a estructor for Option!!! 
    Option::~Option()
    {cout<<"Option Destructor"<<endl;} 
    
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
        //q
        double q = Model.RiskNeutProb(); 
        // GetN()
        int N = pOption->GetN(); 
        // initialize Price as a vector of double of size N+1
        vector<double>Price(N+1); 
        
        // populate the nodes at expiration
        for (int i=0; i<=N;i++)
        {
            Price[i] = pOption->Payoff(Model.CalculateAssetPrice(N,i)); 
        }
        // populate other nodes
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0 ;i<=n;i++)
            {
                Price[i] = (q*Price[i+1] + (1-q) *Price[i]) / Model.GetR(); 
            }
        }
        return Price[0]; 
        
    }
    
    // PriceBySnell function
    double OptionCalculation::PriceBySnell(const BinomialTreeModel & Model,BinLattice &PriceTree)
    {
        // q
        double q = Model.RiskNeutProb(); 
        // GetN()
        int N = pOption->GetN(); 
        // declare a ContVal variable 
        double ContVal = 0; 
        
        // PriceTree of BinLattice class has already been passed in as a parameter
        // now we just have to populate it
        // we first populate the nodes at expiration
        for (int i=0; i<=N; i++)
        {
            PriceTree.SetNode(N,i,pOption->Payoff(Model.CalculateAssetPrice(N,i))); 
        }
        // Then we populate the others 
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0;i<=n;i++)
            {
               // comparison: (q*Price[i+1] + (1-q)*Price[i])/Model.GetR()
               ContVal = (q*PriceTree.GetNode(n+1,i+1) +(1-q)*PriceTree.GetNode(n+1,i))/Model.GetR();
               // Price[i] = pOption->Payoff(Model.CalculateAssetPrice(n,i))
               PriceTree.SetNode(n,i,pOption->Payoff(Model.CalculateAssetPrice(n,i))); 
               
               //if(ContVal>Price[i]) Price[i] = ContVal
               if (ContVal>PriceTree.GetNode(n,i)) PriceTree.SetNode(n,i,ContVal); 
            }
        }
        // return Price[0]
        return PriceTree.GetNode(0,0); 
        
    }
}