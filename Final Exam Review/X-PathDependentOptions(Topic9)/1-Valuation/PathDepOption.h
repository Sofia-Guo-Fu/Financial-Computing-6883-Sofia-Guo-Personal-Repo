#pragma once
#include "MCModel.h"

namespace fre{
    // base class
    class PathDepOption
    {
        protected:
            double Price;
            double T, K;
            int m;
        public:
            // constructor with parameters
            PathDepOption(double T_, double K_, int m_):Price(0.0),T(T_),K(K_),m(m_){}
            virtual ~PathDepOption(){}
            // virtual Payoff function
            virtual double Payoff(const SamplePath &S) const = 0;
            double PriceByMC(const MCModel &Model, long N); 
            // Getter functions
            double GetT() {return T;}
            double GetPrice(){return Price;}
    }; 
    
    class ArthmAsianCall : public PathDepOption
    {
        public:
            ArthmAsianCall(double T_, double K_, int m_):PathDepOption(T_,K_,m_){}
            double Payoff(const SamplePath &S) const;
    }; 
}