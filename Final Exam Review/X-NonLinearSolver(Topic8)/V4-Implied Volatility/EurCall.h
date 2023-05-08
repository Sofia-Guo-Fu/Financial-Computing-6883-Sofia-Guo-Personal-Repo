#pragma once
#include "NonlinearSolver02.h"

namespace fre{
    // first class EurCall
    class EurCall
    {
        private:
            double T, K;
        public:
            EurCall():T(0),K(0){}
            EurCall(double T_, double K_): T(T_),K(K_){}
            ~EurCall(){}
            // member functions
            double d_plus(double S0, double sigma, double r);
            double d_minus(double S0, double sigma, double r);
            double PriceByBSFormula(double S0, double sigma, double r);
            double VegaByBSFormula(double S0, double sigma, double r); 
    }; 
    
    // second class: Intermediary-- multiple inheritence
    // public inherited from EurCall and Function
    class Intermediary: public EurCall, public Function
    {
        private:
            double S0, r;
        public:
            Intermediary(double T_, double K_, double S0_, double r_): EurCall(T_,K_),S0(S0_),r(r_){}
            ~Intermediary(){}
            // member function
            double Value(double sigma);
            double Deriv(double sigma);
    }; 
}