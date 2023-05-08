#pragma once
#include "BinomialTreeModel02.h"
#include "BinLattice02.h"

namespace fre{
    // abstract class
    class Option
    {
        protected:
            int N;
        private:
            // default constructor
            Option():N(0){}
            // copy constructor
            Option(const Option &option):N(option.N){}
        public:
            // constructor with parameters
            Option(int N_):N(N_){}
            int GetN() const {return N;}
            // virtual payoff function
            virtual double Payoff(double z) const = 0;
            // virtual destructor
            virtual ~Option() = 0; 
            
    }; 
    // inherited class
    class Call: public Option
    {
        private:
            double K;
        public:
            Call(int N_, double K_):Option(N_), K(K_){}
            ~Call(){}
            double Payoff(double z) const; 
    }; 
    
    class Put: public Option
    {
        private:
            double K;
        public:
            Put(int N_, double K_):Option(N_),K(K_){}
            ~Put(){}
            double Payoff(double z) const; 
    }; 
    
    //OptionCalculation class
    class OptionCalculation
    {
        private:
            Option *pOption;
            OptionCalculation():pOption(0){}
            OptionCalculation(const OptionCalculation &optionCalculation):pOption(optionCalculation.pOption){}
        public:
            // constructor with parameters
            OptionCalculation(Option *pOption_):pOption(pOption_){}
            ~OptionCalculation(){}
            //PriceByCRR
            double PriceByCRR(const BinomialTreeModel &Model);
            // PriceBySnell
            double PriceBySnell(const BinomialTreeModel &Model, 
                                BinLattice<double>&PriceTree, BinLattice<bool>&StoppingTree); 
        
    }; 
}