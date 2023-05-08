#include "Function02.h"
#include "EurCall.h"
#include "NonlinearSolver02.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace fre;

int main()
{
    // declare S0,r, T,K
    double S0 = 100.0; 
    double r = 0.1;
    double T = 1.0;
    double K = 100.0;
    
    // create an object "Call" of the class "Intermediary"
    Intermediary Call(T,K,S0,r); 
    
    // declare Acc, LEnd, REnd,Tgt, Guess
    double Acc = 0.0001; 
    double LEnd = 0.01, REnd = 1.0;
    double Tgt = 12.56, Guess = 0.23;
    
    // create object of "NonlinearSolver"
    NonlinearSolver solver(Tgt,LEnd,REnd,Acc,Guess);
    
    // Function *Fct = &Call; base class pointer associate with derived class object
    cout<<"Implied volatility by Bisect: "<<fixed<<setprecision(4)<<solver.SolveByBisect(&Call)<<endl; 
    cout<<"Implied volatility by NR: "<<fixed<<setprecision(4)<<solver.SolveByNR(&Call)<<endl;
    return 0;
}


/*
Implied volatility by Bisect: 0.1784
*/