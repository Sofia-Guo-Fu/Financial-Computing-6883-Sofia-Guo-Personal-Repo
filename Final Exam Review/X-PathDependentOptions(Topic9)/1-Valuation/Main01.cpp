#include <iostream>
#include "PathDepOption.h"

using namespace std;
using namespace fre;

int main()
{
    // initialize S0,r,sigma
    double S0 = 100.0, r = 0.03, sigma = 0.2;
    MCModel Model(S0,r,sigma);
    // initialize T,K,int m, long N
    double T = 1.0/12.0, K = 100.0;
    int m = 30;
    long N = 3000;
    // create an object from the ArthmAsianCall class
    ArthmAsianCall Option(T,K,m);
    Option.PriceByMC(Model,N);
    
    cout<<"Arithmetic Asian Call by direct Monte Carlo= "<<Option.GetPrice()<<endl; 
    return 0; 
}

/*
Arithmetic Asian Call by direct Monte Carlo= 1.35925
*/