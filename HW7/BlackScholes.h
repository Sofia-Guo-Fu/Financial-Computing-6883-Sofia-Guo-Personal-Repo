#pragma once
#include "BinomialTreeModel02.h"
#include <cmath>

namespace fre{
    class BlackScholes{
        private:
            double S0,r,sigma, T;
            int N;
            
        public:
            BlackScholes(double S0_, double r_, double sigma_, double T_, int N_): S0(S0_),r(r_), sigma(sigma_), T(T_), N(N_){}
            ~BlackScholes(){}
            
            double cal_U();
            double cal_D();
            double cal_R();
            
            BinomialTreeModel BinomialTree(); 
    }; 
}