#pragma once
#include "BinomialTreeModel02.h"
#include "BinLattice01.h"
#include <iostream>
#include <cmath>

using namespace std; 

namespace fre{
    // as usual, define an abstact class Option
    class Option
    {
        private:
            // default constructor
            Option():N(0){}
            // copy constructor
            Option(const Option &option):N(option.N){}
        protected:
            int N; 
        public:
            // constructor with paramters 
            Option(int N_): N(N_){}
            // virtual destructor
            virtual ~Option() = 0; 
            // member function
            int GetN() const{return N;}
            // virtual double Payoff function
            virtual double Payoff(double z) const = 0; 
            
    }; 
    
    // class Call, inherited from Option
    class Call:public Option
    {
        private:
            // added data member 
            double K;
        public:
            // constructor with parameters
            Call(int N_, double K_): Option(N_),K(K_){}
            // destructor
            ~Call(){}
            // Payoff function override
            double Payoff(double z) const; 
    }; 
    
    // class Put, inheried from Option
    class Put: public Option
    {
        private:
            //added data member
            double K; 
        public:
            // constructor with parameters
            Put(int N_, double K_):Option(N_),K(K_){}
            // destructor
            ~Put(){}
            // Payoff function override
            double Payoff(double z) const; 
    }; 
    
    // class OptionCalculation
    class OptionCalculation
    {
        private:
            // base class pointer
            Option *pOption; 
            // default constructor
            OptionCalculation():pOption(0){}
            // copy constructor
            OptionCalculation(const OptionCalculation &optionCalculation): pOption(optionCalculation.pOption){}
        public:
            // constructor with parameters
            OptionCalculation(Option *pOption_):pOption(pOption_){}
            // destrictor
            ~OptionCalculation(){}
            // PriceByCRR function
            double PriceByCRR(const BinomialTreeModel & Model); 
            // PriceBySnell function, here we added a &PriceTree parameter of the BinLattice class
            double PriceBySnell(const BinomialTreeModel &Model, BinLattice & PriceTree); 
            
    }; 
}