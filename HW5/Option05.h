#pragma once
#include "BinomialTreeModel02.h"

namespace fre{
    
    //first class: EurOption
    class EurOption
    {
        private:
            EurOption():N(0){}
            EurOption(const EurOption & option):N(option.N){}
        protected:
            int N;
        public:
            EurOption(int N_):N(N_){}
            int GetN() const {return N;}
            // pure virtual 
            virtual double Payoff(double z) const=0;
            virtual ~EurOption() = 0;
    };

    //Second class: Call, child concrete class
    class Call:public EurOption
    {
        private:
            double K;
        public:
            Call(int N_,double K_): EurOption(N_),K(K_){}
            ~Call(){}
            //memeber function override 
            double Payoff(double z) const;
    };
    
    // Third class: Put, child concrete class
    class Put: public EurOption
    {
        private:
            double K;
        public:
            Put(int N_,double K_): EurOption(N_),K(K_){}
            ~Put(){}
            //memeber function override 
            double Payoff(double z) const;
    };
    
    // Fourth class: Bull spread
    class BullSpread: public EurOption
    {
        private:
            double K1;
            double K2;
        public:
            BullSpread(int N_,double K1_, double K2_): EurOption(N_),K1(K1_),K2(K2_){}
            ~BullSpread(){}
            double Payoff(double z) const;
    };
    
    //Fifth class: Bear spread
    class BearSpread: public EurOption
    {
        private:
            double K1;
            double K2;
        public:
            BearSpread(int N_,double K1_,double K2_): EurOption(N_),K1(K1_),K2(K2_){}
            ~BearSpread(){}
            double Payoff(double z) const;
    };
    
    // Last class: OptionCalculation
    class OptionCalculation
    {
        private:
            EurOption *pOption;
            OptionCalculation(): pOption(0){}
            OptionCalculation(const OptionCalculation & optionCalculation):
                                    pOption(optionCalculation.pOption){}
        public:
            // constructor with parameters
            OptionCalculation(EurOption *pOption_):pOption(pOption_){}
            //destructor 
            ~OptionCalculation(){}
            double PriceByCRR(const BinomialTreeModel & model);
    };
    
}
