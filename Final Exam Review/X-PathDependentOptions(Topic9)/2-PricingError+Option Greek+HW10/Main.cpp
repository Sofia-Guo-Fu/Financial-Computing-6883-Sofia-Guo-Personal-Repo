#include "PathDepOption.h"
#include "MCModel.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace fre;

int main()
{
    // initialize S0, r, sigma
    double S0=100.0, r=0.03, sigma=0.2;
    // create a Model of class MCModel
    MCModel Model(S0,r,sigma);
    // initliaze T,m,K
    double T =1.0/12.0, K=100.0;
    int m=30;

    ArthmAsianCall Option(T,K,m);
    
    long N=30000;
    double epsilon =0.001;
    Option.PriceByMC(Model,N,epsilon);
    cout << "Arithmetic Asian Call by direct Monte Carlo = " << Option.GetPrice() << endl
        << "Error = " << Option.GetPricingError() << endl
        << "delta = " << Option.GetDelta() << endl
        <<"gamma = "<<Option.GetGamma()<<endl; 

    return 0;
}


/*
Arithmetic Asian Call by direct Monte Carlo = 1.42145
Error = 0.0119846
delta = 0.525568
gamma = 0.114969
*/