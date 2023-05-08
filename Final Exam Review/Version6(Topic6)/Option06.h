#pragma once
#include "BinomialTreeModel02.h"


namespace fre{
    // define an abstact class called Option for both European and American Options
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
            // constructor with parameters
            Option(int N_):N(N_){}
            // virtual destructor
            virtual ~Option() = 0 ; //??
            // member function GetN()
            int GetN() const{return N;}
            // virtual Payoff function 
            virtual double Payoff(double z) const = 0; 
    }; 
    
    // Call class, inherited from Option class
    class Call:public Option
    {
        private:
            double K;
        public:
            // constructor with parameters
            Call(int N_, double K_): Option(N_), K(K_){}
            // destructor 
            ~Call(){}
            // Payoff function override
            double Payoff(double z) const; 
    }; 
    
    // Put class, inherited from Option class
    class Put:public Option
    {
        private:
            double K; 
        public:
            // constructor with parameters
            Put(int N_, double K_):Option(N_), K(K_){}
            // destructor 
            ~Put(){}
            //Payoff function override
            double Payoff(double z) const; 
    }; 
    
    //OptionCalculation class
    class OptionCalculation
    {
        private:
            // base class pointer
            Option *pOption; 
            // default constructor
            OptionCalculation():pOption(0){}
            // copy constructor
            OptionCalculation(const OptionCalculation & optionCalculation): pOption(optionCalculation.pOption){}
        public:
            // constructor with paramters
            OptionCalculation(Option *pOption_): pOption(pOption_){}
            // destructor 
            ~OptionCalculation(){}
            // PriceByCRR function
            double PriceByCRR(const BinomialTreeModel &Model); 
            // PriceBySnell function
            double PriceBySnell(const BinomialTreeModel &Model); // for now, only one parameter &Model 
        
    }; 
}