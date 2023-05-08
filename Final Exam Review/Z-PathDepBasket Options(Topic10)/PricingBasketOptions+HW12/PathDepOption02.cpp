#include "PathDepOption02.h"
#include <cmath>

namespace fre{
    
    // first define a rescale function to compute delta later
    void Rescale(SamplePath &S, double x, int j)
    {
        int m = S.size();
        for(int k=0; k < m; k++) S[k][j] = x * S[k][j];
    }
    // PriceByMC
    double PathDepOption::PriceByMC(MCModel &Model, long N, double epsilon)
    {
        // initialize H
        double H = 0.0;
        // declare an object of type SamplePath
        SamplePath S(m);
        
        // delta resize to d
        int d = Model.GetS0().size(); 
        delta.resize(d);
        
        // initialize Heps, is a Vector
        Vector Heps(d);
        // initialize each element in Heps to 0
        for (int i=0;i<d;i++) Heps[i] = 0.0;
        
        // loop through N SamplePath 
        for(long i=0;i<N;i++)
        {
            // Generate N SamplePaths
            Model.GenerateSamplePath(T,m,S); 
            H = (i*H +Payoff(S)) / (i+1.0); 
            
            // loop through d options in the basket
            for (int j=0;j<d;j++)
            {
                // Rescale
                Rescale(S,1.0 + epsilon,j); 
                // calculate the average of Heps[j] in m nodes
                Heps[j] = (i * Heps[j] + Payoff(S)) / (i+1.0); 
                // rescale back afterwards
                if (j<d-1) Rescale(S, 1.0/(1.0+epsilon),j); 
            }
        }
        Price = std::exp(-Model.GetR()*T) * H; 
        for (int j=0; j<d; j++) delta[j] = std::exp(-Model.GetR() * T) * (Heps[j] - H) / (epsilon * Model.GetS0()[j]); 
        return Price;
    }
    
    double ArthmAsianCall::Payoff(const SamplePath& S) const // don't know where went wrong
    {
        double Ave = 0.0;
        int d = S[0].size();
        // define a Vector of one of size d
        Vector one(d);
        for (int i  =0; i < d; i++) one[i] = 1.0; 
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0); // one ^ S[k]
        }
        if (Ave < K) return 0.0;
        return (Ave - K); 
    }
    
}


