#include "Function02.h"
#include "Bond.h"
#include <cmath>

namespace fre{
    double Bond::Value(double y)
    {
        double P = 0;
        for(unsigned int n=0; n<=C.size(); n++)
        {
            P += C[n] * exp(-y*t[n]);
        }
        P += F * exp(-y * T);
        return P;
    }
    
    double Bond::Deriv(double y)
    {
        double D = 0;
        for (unsigned int n=0;n<=C.size();n++)
        {
            D += (-C[n]) * t[n] * exp(-y*t[n]);
        }
        D += -F * T * exp(-y * T);
        return D; 
    }
}