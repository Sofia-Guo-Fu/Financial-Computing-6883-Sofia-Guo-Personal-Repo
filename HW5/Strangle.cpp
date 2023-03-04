#include "Strangle.h"

namespace fre {
    double Strangle::Payoff(double z) const
    {
        if (z<K1) return K1-z;
        else if (K1 < z&&z < K2) return 0.0;
        return z-K2;
    }
}