#pragma once
#include "BinomialTreeModel02.h"

namespace fre{
    // abstract class
    class EurOption
    {
        private:
            // default constructor 
            EurOption(): N(0){}
            // copy constructor 
            EurOption(const EurOption &option): EurOption(option.N){}
        protected:
            int N; 
        public:
            // constructor with parameters
            EurOption(int N_): N(N_){}
            // pure virtual destructor ??? 
            virtual ~EurOption() = 0; 
            
            // member function
            int GetN() const{return N;}
            // pure virtual Payoff function for inheritence
            virtual double Payoff(double z) const = 0; //别忘写type double 了! 
    };
    
    // class Call, inherited from EurOption
    class Call: public EurOption
    {
        private:
            // added data member
            double K; 
        public:
            // constructor with parameters: int N inherited from class EurOption
            Call(int N_, double K_): EurOption(N_), K(K_){}
            // desctructor 
            ~Call(){}
            // function override
            double Payoff(double z) const; 
    };
    
    // class Put
    class Put: public EurOption
    {
        private:
            double K; 
        public:
            // constructor with parameters: int N inherited from class EurOption
            Put(int N_, double K_): EurOption(N_), K(K_){}
            ~Put(){}
            // function override
            double Payoff(double z) const; 
    }; 
    
    // Bull Spread
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
    
    // Bear spread
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
    
    class OptionCalculation
    {
        private:
            // pointer variable 
            EurOption *pOption;
            // default constructor 
            OptionCalculation(): pOption(0){}
            // copy constructor
            OptionCalculation(const OptionCalculation & optionCalculation): pOption(optionCalculation.pOption){}
        public:
            // constructor with parameters
            OptionCalculation(EurOption *pOption_): pOption(pOption_){}
            // PriceByCRR function
            double PriceByCRR(BinomialTreeModel & Model); 
        
    }; 
}