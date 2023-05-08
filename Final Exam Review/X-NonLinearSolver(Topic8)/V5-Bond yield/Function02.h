#pragma once

namespace fre{
    // abstract base class Function
    class Function
    {
        public:
            // virtual functions
            virtual double Value(double x) = 0; 
            virtual double Deriv(double x) = 0; // Don't forget=0
            // virtual destructor
            virtual ~Function(){}
    }; 
    
    // child class
    class F1: public Function
    {
        public:
            // function override
            double Value(double x);
            double Deriv(double x); 
    }; 
    
    class F2: public Function
    {
        private:
            double a; // any real number
        public:
            // added: constructor for F2
            F2(double a_):a(a_){}
            double Value(double x);
            double Deriv(double x);
    }; 
}