#include "PathDepOption02.h"
#include "MCModel02.h"
#include <iostream>

using namespace std;
using namespace fre;

int main()
{
    // initialize int d
    int d = 3;
    // initialize Vector S0
    Vector S0(d);
    S0[0] = 40.0;
    S0[1] = 60.0;
    S0[2] = 100.0;
    double r = 0.03;
    
    // initialize Matrix C
    Matrix C(d);
    // resize every column of C
    for (int i=0;i<d;i++) C[i].resize(d); 
    
    C[0][0] =  0.1;  C[0][1] = -0.1;  C[0][2] = 0.0;
    C[1][0] = -0.1;  C[1][1] =  0.2;  C[1][2] = 0.0;
    C[2][0] =  0.0;  C[2][1] =  0.0;  C[2][2] = 0.3;
    // With Vector S0, double r, Matrix C all set, we can create our MCModel
    MCModel Model(S0,r,C); 
    
    double T=1.0/12.0, K=200.0;
    int m=30;
    // we can create a arithmetic call object "Option"
    ArthmAsianCall Option(T,K,m); 
    
    long N=3000;
    double epsilon = 0.001;
    
    cout<<"Arithmetic Basket Call Option Price is: "<<Option.PriceByMC(Model,N,epsilon)<<endl;
    
    // getdelta
    for (int j=0; j<d; j++)
    {
        cout<<"delta["<<j<<"] = "<<Option.GetDelta()[j]<<endl; 
    }
    return 0; 
}


/*
Arithmetic Basket Call Option Price is: 2.18595
delta[0] = 0.503859
delta[1] = 0.505984
delta[2] = 0.526536
*/