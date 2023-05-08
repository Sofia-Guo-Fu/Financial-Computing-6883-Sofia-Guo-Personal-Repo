#pragma once

#include <vector>
#include "Function02.h"

using namespace std;
namespace fre {
    class Bond : public Function
    {
    private:
        double F;
        double T;
        vector<double> C;
        vector<double> t;
    public:
        Bond(double F_, double T_, vector<double>& C_, vector<double>& t_)
        {
            F = F_; T = T_; C = C_; t = t_;
        }
        double Value(double y);
        double Deriv(double y);
    };
}
