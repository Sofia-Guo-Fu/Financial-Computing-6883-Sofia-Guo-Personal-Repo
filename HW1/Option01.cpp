#include "Option01.h"
#include "BinomialTreeModel.h"
#include <iostream>
#include <cmath>
using namespace std;

namespace fre {
    
    // Version 1:  factorial
    // First, we define a new function that calculates the factorial 
    double HW1Factorial(int n)
    {
        double num = 1.0;
        if (n<=0) return num;
        do {
            num = num * n;
            n--;
        } while (n>0);
        
        return num;
    }
    
    // Then, define my own PriceByCRR Function
    double HW1PriceByCRR(double S0,double U, double D,double R, int N, double K)
    {
        
        double Price = 0.0;
        double q = RiskNeutProb(U,D,R);
        
        double Factorial_N = HW1Factorial(N);
        
        for(int i=0; i<=N; i++)
        {
            Price = Price + Factorial_N /(HW1Factorial(i) * HW1Factorial(N-i)) * pow(q,i) * pow(1-q,N-i) 
            * CallPayoff(CalculateAssetPrice(S0, U, D, N, i), K);
        }
        Price = Price/pow(R,N);
        return Price;
        
    }
    
    // Version 2
    // First, calculate the combination function as a whole
    double HW1Function(int N, int n)
    {
        if (n<0 || n>N) return 0;
        double result = 1;
        for (int i=1; i<=n;i++) result = result * (N-n+i) / i;
        return result;
    }
    
    //Then we write the version 2 PriceByCRR function
    double HW1V2PriceByCRR(double S0, double U, double D, double R, int N, double K)
    {
        double q = RiskNeutProb(U,D,R);
        double Price = 0.0;
        for (int i=0;i<=N;i++)
        {
            Price = Price + HW1Function(N,i) * pow(q,i) * pow(1-q,N-i) * CallPayoff(CalculateAssetPrice(S0,U,D,N,i),K);
        }
        Price = Price/pow(R,N);
        return Price;
        
    }
    
    // Professor's original PriceByCRR function
    double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K)
    {
        double q = RiskNeutProb(U, D, R);
        double Price[N+1];
        
        for (unsigned int i = 0; i < sizeof(Price) / sizeof(Price[0]); i++)
            Price[i] = 0.0;

        for (unsigned int i = 0; i <= N; i++)
        {
            // Calculate the Price of Binomial Tree at each node i
            Price[i] = CallPayoff(CalculateAssetPrice(S0, U, D, N, i), K);
            
        }
        
        for (int n = N - 1; n >= 0; n--)
        {
            for (int i = 0; i <= n; i++)
            {
                Price[i] = (q * Price[i + 1] + (1 - q) * Price[i]) / R;
            }
        }
        return Price[0];
        
    }
    

    double CallPayoff(double z, double K)
    {
        if (z > K) return z - K;
        return 0.0;
    }
}
