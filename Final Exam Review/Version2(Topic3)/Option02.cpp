#include "BinomialTreeModel.h"
#include "Option02.h"
#include <iostream>
#include <cmath>

using namespace std; 

namespace fre{
    // Get input data
    int GetInputData(int &N, double &K)
    {
        cout<<"Enter steps to expiry N: "; cin>>N;
        cout<<"Enter striling price K: "; cin>>K; 
        cout<<endl; 
        return 0; 
    }
    
    //PriceByCRR
    double *PriceByCRR(double S0, double U, double D, double R, int N, double K, 
                                            double (*Payoff)(double z, double K))
    {
        // Risk-neutral probability
        double q = RiskNeutProb(U,D,R); 
        
        // initialize an Price array through dynamic memory allocation
        double *Price = new double[N+1]; 
        
        //populate the nodes at expiration 
        for (int i=0; i<=N;i++)
        {
            // This is where function pointer does its magic
            Price[i] = Payoff(CalculateAssetPrice(S0,U,D,N,i),K); //参数中不带R
        }
        
        // populate the rest of nodes by discounting back
        for (int n=N-1; n>=0; n--)
        {
            for (int i=0; i<=n; i++)
            {
                Price[i] = (q*Price[i+1] + (1-q) * Price[i]) / R; 
            }
        }
        return Price; // the first element of the Price array
    }
    
    // defintion of a variety of Payoff functions
    double CallPayoff(double z, double K)
    {
        if (z>K) return (z-K);
        return 0.0; 
    }
    
    double PutPayoff(double z, double K)
    {
        if (K>z) return (K-z); 
        return 0.0;
    }
    
    double DigitalCallPayoff(double z, double K)
    {
        if (z>K) return 1.0; 
        return 0.0;
    }
    
    double DigitalPutPayoff(double z, double K)
    {
        if (K>z) return 1.0; 
        return 0.0; 
    }
}

