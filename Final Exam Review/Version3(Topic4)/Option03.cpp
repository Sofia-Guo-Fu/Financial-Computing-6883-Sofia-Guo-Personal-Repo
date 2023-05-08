#include "BinomialTreeModel02.h"
#include "Option03.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string.h>  // 与memset 有关，不然会报错

using namespace std; 

namespace fre{
     // normal independnt functions
    int GetInputData(int N, double K)
    {
        cout<<"Enter steps to expiry N: "; cin>>N; 
        cout<<"Enter striking price K: "; cin>>K; 
        cout<<endl; 
        return 0; 
    }
    
    // PriceByCRR, here we pass Model instead of S0,U,D,R parameters like before
    double *PriceByCRR(const BinomialTreeModel &Model,int N, double K, double(*Payoff)(double z, double K))
    {
        // compute risk-neutral probability 
        double q = Model.RiskNeutProb(); 
        
        // initialize an array Price
        double *Price = new double[N+1]; 
        memset(Price,0,N+1); 
        
        // populate the nodes at expiration 
        for (int i=0; i<=N; i++)
        {
            Price[i] = Payoff(Model.CalculateAssetPrice(N,i),K); 
        }
        
        for (int n=N-1; n>=0; n--)
        {
            for(int i=0; i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / Model.GetR(); 
            }
        }
        
        return Price; 
    }
    
    // define payoff functions
    double CallPayoff(double z, double K)
    {
        if (z>K) return (z-K); 
        return 0.0; 
    }
    
    double PutPayoff(double z, double K)
    {
        if (z<K) return (K-z);
        return 0.0; 
    }
}