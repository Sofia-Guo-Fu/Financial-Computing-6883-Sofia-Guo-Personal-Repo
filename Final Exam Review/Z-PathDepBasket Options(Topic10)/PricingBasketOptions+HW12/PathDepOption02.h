#pragma once
#include "MCModel02.h"

namespace fre{
    // base class
    class PathDepOption
    {
        protected:
            double Price;
            // deta is a Vector 
            Vector delta; 
            double T, K;
            int m; 
        public:
            // constructor with parameters
            PathDepOption(double T_, double K_, int m_): Price(0.0), T(T_),K(K_),m(m_){}
            // added parameter epsilon for PriceByMC
            double PriceByMC(MCModel &Model, long N, double epsilon);
            // virtual destructor
            virtual ~PathDepOption(){}
            // virtual double Payoff function
            virtual double Payoff(const SamplePath &S) const = 0; 
            // Getter functions, get Price and delta, note with return type
            double GetPrice() const {return Price;}
            Vector GetDelta() const {return delta;}
    }; 
    
    // derived class ArthmAsianCall
    class ArthmAsianCall: public PathDepOption
    {
        public:
            // constructor with parameters
            ArthmAsianCall(double T_, double K_, int m_):PathDepOption(T_,K_,m_){}
            // function override
            double Payoff(const SamplePath &S) const;
    }; 
}
