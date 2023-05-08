#pragma once
#include "Function03.h"

namespace fre{
    // declare that it is a class template
    template<typename Function>
    class NonlinearSolver
    {
        private:
            double Tgt;
            double LEnd;
            double REnd;
            double Acc;
            double Guess;
        public:
            // default constructor
            NonlinearSolver():Tgt(0),LEnd(0),REnd(0),Acc(0),Guess(0){}
            // constructor with parameters
            NonlinearSolver(double Tgt_, double LEnd_, double REnd_, double Acc_, double Guess_):
                Tgt(Tgt_), LEnd(LEnd_), REnd(REnd_), Acc(Acc_), Guess(Guess_){}
            // destructor
            ~NonlinearSolver(){}
            void UpdateSolver(double Tgt_, double LEnd_, double REnd_, double Acc_, double Guess_)
            {
                Tgt = Tgt_;
                LEnd = LEnd_;
                REnd = REnd_;
                Acc = Acc_;
                Guess = Guess_;
            }
            
            // template member function
            double SolverByBisect(Function * Fct)
            {
                double left = LEnd, right = REnd, mid = (left+right)/2; 
                double y_left = Fct->Value(left)-Tgt, y_mid = Fct->Value(mid)-Tgt;
                while (mid - left >Acc)
                {
                    if ((y_left>0 && y_mid>0) || (y_left<0 && y_mid<0))
                    {
                        left = mid; y_left = y_mid; 
                    }
                    else right = mid; 
                    mid = (left + right)/2; 
                    y_mid = Fct->Value(mid) - Tgt;
                }
                return mid; 
            }
            
            // template function
            double SolveByNR(Function *Fct)
            {
                double x_prev = Guess;
                double x_next = x_prev - (Fct->Value(x_prev) - Tgt)/Fct->Deriv(x_prev); 
                while (x_next - x_prev>Acc || x_prev - x_next > Acc)
                {
                    x_prev = x_next;
                    x_next =  x_prev - (Fct->Value(x_prev) - Tgt)/Fct->Deriv(x_prev); 
                }
                return x_next;
            }
    }; 
}