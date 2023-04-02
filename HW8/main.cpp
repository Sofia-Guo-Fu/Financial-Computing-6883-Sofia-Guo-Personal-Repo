#include <iostream>
#include <iomanip>
#include "Bond.h"
#include "NonlinearSolver02.h"

using namespace std; 
using namespace fre; 

int main()
{
    double F = 100.0;
    double T = 3.0;
    double C = 1.2;
    
    double P = 98.56; 
    double Acc = 0.0001; 
    double LEnd = 0.0, REnd = 1.0;
    double Guess = 0.2; 
    
    Bond bond(F,T,C); 
    
    NonlinearSolver solver(P,LEnd,REnd,Acc,Guess); 
    
    cout<<"Yield by Bisect: "<<fixed<<setprecision(4)<<solver.SolveByBisect(&bond)<<endl; 
    cout<<"Yield by Newton-Rahpson: "<<fixed<<setprecision(4)<<solver.SolveByNR(&bond)<<endl; 
    
}


/*

Yield by Bisect: 0.0168
Yield by Newton-Rahpson: 0.0168

*/