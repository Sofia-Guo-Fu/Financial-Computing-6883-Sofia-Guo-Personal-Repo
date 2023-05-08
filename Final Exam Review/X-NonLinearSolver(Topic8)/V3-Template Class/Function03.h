#pragma once

namespace fre{
    class F1
    {
        public:
            double Value(double x);
            double Deriv(double x);
    };
    
    class F2
    {
        private:
            double a;
        public:
            // constructor
            F2(double a_){a = a_;}
            double Value(double x);
            double Deriv(double x);
    };
}