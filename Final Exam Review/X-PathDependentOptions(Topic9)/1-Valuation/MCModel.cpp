#include "MCModel.h"
#include <cmath>

namespace fre{
    
    // define pi
    const double pi = 4.0 * atan(1.0); 
    // independent function Gauss()
    double Gauss()
    {
        double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
        double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
        return sqrt(-2*log(U1))* cos(2*pi*U2);
    }
    
    void MCModel::GenerateSamplePath(double T, int m, SamplePath &S) const
    {
        // declare St
        double St = S0; 
        for(int k=0; k<m; k++)
        {
            S[k] = St * exp((r - 0.5*sigma*sigma) * (T/m) + sigma * sqrt(T/m) * Gauss()); 
            St = S[k];
        }
    }
}