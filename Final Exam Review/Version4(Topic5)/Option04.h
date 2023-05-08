#pragma once
#include "BinomialTreeModel02.h"

namespace fre{
    // create a class for Call
    class Call
    {
        private:
            int N;
            double K; 
        public:
            // default constructor
            Call():N(0),K(0.0){}
            // constructor with parameters
            Call(int N_, double K_): N(N_), K(K_){}
            // copy constructor 
            Call(const Call & call):N(call.N), K(call.K){}
            // memebr function GetN() this will be needed in PriceByCRR in the OptionCaculation class
            int GetN() const {return N;}
            //payoff function: it now only has one parameter z inside now, because N is already in this private data member
            double Payoff(double z) const; 
    }; 
    
    // create a class called OptionCalculation
    class OptionCaculation
    {
        private:
            // private data member: a pointer to the class Call
            Call *pOption; 
            // default constructor
            OptionCaculation():pOption(0){}
            //copy constructor 
            OptionCaculation(const OptionCaculation & optionCalculation): pOption(optionCalculation.pOption){}
            
        public:
            // constructor with parameters
            OptionCaculation(Call *pOption_):pOption(pOption_){} // 别忘记加data type Call, 别忘带*
            // destructor
            ~OptionCaculation(){}
            // PriceByCRR function: now it only has one paramter &Model
            double PriceByCRR(BinomialTreeModel &Model); 
            
    }; 
}