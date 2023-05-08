#include "Function01.h"
#include "NonlinearSolver01.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace fre;

int main()
{
    double Acc = 0.0001;
    double LEnd = 0.0, REnd = 2.0;
    double Tgt = 0.0, Guess = 1.0;
    
    // create an object of the NonlinearSolver class
    NonlinearSolver solver(Tgt, LEnd, REnd, Acc, Guess);
    
    cout<<"Root of F1 by Bisect: "<<fixed<<setprecision(4)<<solver.SolveByBisect(F1)<<endl;
    cout<<"Root of F1 by Newton Ralphson: "<<fixed<<setprecision(4)<<solver.SolveByNR(F1, DF1)<<endl<<endl;
    return 0; 
}

/*

Root of F1 by Bisect: 1.4142
Root of F1 by Newton Ralphson: 1.4142

*/