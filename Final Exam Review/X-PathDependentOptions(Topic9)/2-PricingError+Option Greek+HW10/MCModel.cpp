#include "MCModel.h"
#include <cmath>

namespace fre{
    
    // declare pi
    const double pi = 4.0 * atan(1.0); 
    // first define a independent function Gauss()
    double Gauss()
    {
        double U1 = (rand()+1.0)/(RAND_MAX+1.0);
        double U2 = (rand()+1.0)/(RAND_MAX+1.0);
        return sqrt(-2*log(U1)) * cos(2*pi*U2);
    }
    
    // define memeber function GenerateSamplePath outside
    void MCModel::GenerateSamplePath(double T, int m, SamplePath &S)const //can't forget const
    {
        // initlialize St
        double St = S0;
        // loop through every node m
        for(int k=0; k<m; k++)
        {
            S[k] = St * exp((r - 0.5*sigma*sigma) *(T/m) + sigma*sqrt(T/m)*Gauss()); 
            St = S[k];
        }
    }
}