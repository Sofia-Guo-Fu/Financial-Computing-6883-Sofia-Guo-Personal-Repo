#include "Function02.h"
#include "NonlinearSolver02.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace fre;

int main()
{
    double Acc1 = 0.0001;
    double LEnd1 = 0.0, REnd1 = 2.0; 
    double Tgt1 = 0.0, Guess1 = 1.0;
    
    // create object of NonlinearSolver, only one solver object
    NonlinearSolver solver(Tgt1,LEnd1,REnd1,Acc1,Guess1); 
    
    // derived class object MyF1
    F1 MyF1;
    cout<<"Root of F1 by Bisect: "<<fixed<<setprecision(4)<<solver.SolveByBisect(&MyF1)<<endl;
    cout<<"Root of F1 by Newton Ralphson: "<<fixed<<setprecision(4)<<solver.SolveByNR(&MyF1)<<endl;
    
    double Acc2 = 0.0001; 
    double LEnd2 = 0.0, REnd2 = 4.0;
    double Tgt2 = 0.0, Guess2 = 3.0; 
    
    // derived class object MyF2
    F2 MyF2(10.0);

    solver.UpdateSolver(Tgt2,LEnd2,REnd2,Acc2,Guess2); 
    cout<<"Root of F1 by Bisect: "<<fixed<<setprecision(4)<<solver.SolveByBisect(&MyF2)<<endl; 
    cout<<"Root of F1 by Newton-Rahpson: "<<fixed<<setprecision(4)<<solver.SolveByNR(&MyF2)<<endl; 
    
    return 0; 
}

/*

Root of F1 by Bisect: 1.4142
Root of F1 by Newton Ralphson: 1.4142
Root of F1 by Bisect: 3.1623
Root of F1 by Newton-Rahpson3.1623

*/