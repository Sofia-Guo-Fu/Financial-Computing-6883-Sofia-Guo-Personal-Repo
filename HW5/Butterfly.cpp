#include "Butterfly.h"

namespace fre{
    double Butterfly::Payoff(double z) const
    {
        if (z<=(K1+K2)/2 && z>K1) 
            return (z-K1);
        if (z>(K1+K2)/2 && z<=K2)
            return (K2-z);
        else
            return 0.0; 
    }
}