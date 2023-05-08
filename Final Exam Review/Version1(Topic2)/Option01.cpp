#include "Option01.h"
#include "BinomialTreeModel.h"
#include <iostream>
#include <cmath>

using namespace std; 
namespace fre{
     // get option data 
    int GetInputData(int &N, double &K)
    {
        cout<<"Enter steps to expiration N: "; cin>>N; 
        cout<<"Enter striking price: "; cin>>K; 
        cout<<endl;
        return 0; 
    }
    
    // Call Pay off funciton 
    double CallPayOff(double z, double K)
    {
        if (z>K) return (z-K); 
        return 0.0; 
    }
    
    // Pricing European option PriceByCRR
    double PriceByCRR(double S0, double U, double D, double R, double K, int N)
    {
        // compuete risk neutral probability 
        double q= RiskNeutProb(U,D,R); 
        
        // initialize a Price array 
        double Price[N+1]; 
        // for (int i=0; i<N; i++)
        // {
        //     Price[i] = 0.0; 
        // }
        
        // compute the prices at expiration
        for (int i=0; i<=N; i++)
        {
            Price[i] = CallPayOff(CalculateAssetPrice(S0,U,D,N,i),K); 
        }
        // discount them back
        for (int n=N-1;n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q)*Price[i]) / R; 
            }
        }
        return Price[0]; 
            
    }
}