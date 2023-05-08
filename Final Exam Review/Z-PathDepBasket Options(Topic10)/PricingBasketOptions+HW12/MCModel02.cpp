#include "MCModel02.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

namespace fre{
    // define pi
    const double pi = 4.0 * atan(1.0); 
    // independent function Gauss()
    double Gauss()
    {
        double U1 = (rand() + 1.0) / (RAND_MAX + 1.0);
        double U2 = (rand() + 1.0) / (RAND_MAX + 1.0);
        return sqrt(-2*log(U1)) * cos(2.0*pi*U2);
    }
    
    // overload Gauss(int d) function, return a Vector of Gauss
    Vector Gauss(int d)
    {
        // first initialize a return Vector Z
        Vector Z(d);
        for(int j=0; j<d; j++) Z[j] = Gauss();
        return Z;
    }
    
    // define constructor outside 
    MCModel::MCModel(Vector S0_,double r_, Matrix C_):S0(S0_),r(r_),C(C_)
    {
        // random seed
        srand(time(NULL)); 
        // compute sigma
        int d = S0.size();
        // resize sigma
        sigma.resize(d); 
        for (int j=0;j<d;j++)
        {
            sigma[j] = sqrt(C[j]^C[j]); 
        }
    }
    
    // member function of MCModel
    void MCModel::GenerateSamplePath(double T, int m, SamplePath &S) const
    {
        // don't forget to specify the type of St
        Vector St = S0;
        int d = S0.size();
        for (int k=0; k<m;k++)
        {
            // S[k] = St * exp((T/m) * (r + (-0.5)*sigma*sigma) + sqrt(T/m) * (C * Gauss(d))); 
            // St = S[k]; 
            S[k] = St * exp((T / m) * (r + (-0.5) * sigma * sigma) + sqrt(T / m) * (C * Gauss(d)));
            St = S[k];
        }
    }
}