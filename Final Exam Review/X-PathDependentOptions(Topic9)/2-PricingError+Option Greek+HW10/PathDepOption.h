#pragma once
#include "MCModel.h"

namespace fre{
    // base class
    class PathDepOption
    {
        protected:
            double Price, PricingError,delta,gamma;
            double T;
            double K;
            int m; 
        public:
            // constructor with parameters
            PathDepOption(double T_,double K_, double m_): 
                Price(0.0), PricingError(0.0), delta(0.0), gamma(0.0), T(T_), K(K_),m(m_){}
            // virtual destructor
            virtual ~PathDepOption(){}
            // virtual member function
            virtual double Payoff(const SamplePath &S)const = 0;
            double PriceByMC(const MCModel &Model, long N, double epsilon); //added double eposilon
            // getter functions
            double GetT() const {return T;}
            double GetPrice() const {return Price;}
            double GetPricingError() const {return PricingError;}
            double GetDelta() const {return delta;}
            double GetGamma() const {return gamma;}
            
    }; 
    //derived class
    class ArthmAsianCall: public PathDepOption
    {
        public:
            // constructor with parameters
            ArthmAsianCall(double T_, double K_, int m_): PathDepOption(T_,K_,m_){}
            double Payoff(const SamplePath &S) const;
    }; 
}