#pragma once
#include "MCModel.h"
#include "EurCall.h"

namespace fre{
    // base class PathDepOption
    class PathDepOption
    {
        protected:
            double Price, PricingError, delta;
            double T;
            double K;
            int m;
        public:
            PathDepOption(double T_, double K_, int m_): 
                Price(0.0), PricingError(0.0), delta(0.0), T(T_), K(K_), m(m_){}
            virtual ~PathDepOption(){}
            
            // memeber functions 
            double PriceByMC(const MCModel &Model, long N, double epsilon);
            double PriceByVarRedMC(const MCModel &Model, long N, PathDepOption &CVOption, double epsilon); 
            // only virtual functions
            virtual double PriceByBSFormula(const MCModel &Model){ return 0.0; }
            virtual double DeltaByBSFormula(const MCModel &Model) { return 0.0; } 
            // pure virtual function Payoff
            virtual double Payoff(const SamplePath &S) const = 0; 
            
            // getter functions
            double GetT(){ return T; }
            double GetPrice(){ return Price; }
            double GetPricingError(){ return PricingError; }
            double GetDelta(){ return delta; }
    }; 
    
    // derived class DifferenceOfOptions
    class DifferenceOfOptions : public PathDepOption
    {
        private:
            PathDepOption * Ptr1;
            PathDepOption * Ptr2; 
        public:
            DifferenceOfOptions(double T_, double K_, int m_, PathDepOption* Ptr1_, PathDepOption* Ptr2_):
                PathDepOption(T_, K_, m_), Ptr1(Ptr1_), Ptr2(Ptr2_){}
                
            // override the payoff function, with definition here
            double Payoff(const SamplePath& S) const
            {
                return Ptr1->Payoff(S) - Ptr2->Payoff(S); 
            }
    }; 
    
    // second derived class 
    class ArthmAsianCall: public PathDepOption
    {
        public:
            ArthmAsianCall(double T_, double K_, int m_): PathDepOption(T_, K_,m_){}
            double Payoff(const SamplePath& S) const; 
    }; 
}