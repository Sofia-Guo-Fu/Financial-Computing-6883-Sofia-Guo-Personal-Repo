#include "Function02.h"
#include "Bond.h"
#include "NonlinearSolver02.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace fre;

int main()
{
    double BondF = 100.0;
    double BondT = 3.0;
    vector<double> C;
    // fill vector C with values
    C.push_back(1.2);C.push_back(1.2);C.push_back(1.2);
    vector<double> t;
    t.push_back(1.0);t.push_back(2.0); t.push_back(3.0);
    
    // create an object of Bond class
    Bond MyBond(BondF,BondT, C, t);
    
    double Tgt = 98.56; 
    double Acc = 0.0001;
    double LEnd = 0.0, REnd = 1.0;
    double Guess = 0.2;
    
    NonlinearSolver solver(Tgt,LEnd,REnd,Acc,Guess);
    
    // Function * Fct = &MyBond ; base class pointer associate with derived class object
    cout<<"Yield by Bisection method: "<<fixed<<setprecision(4)<<solver.SolveByBisect(&MyBond)<<endl;
    cout<<"Yield by Newton Raphson method: "<<fixed<<setprecision(4)<<solver.SolveByNR(&MyBond)<<endl;
    
    return 0; 
}

/*
Yield by Bisection method: 0.0168
Yield by Newton Raphson method: 0.0168
*/