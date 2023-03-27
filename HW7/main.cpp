#include <iostream>
#include <iomanip>
#include <fstream>
#include "BinomialTreeModel02.h"
#include "Option08.h"
#include "BlackScholes.h"

using namespace std; 
using namespace fre; 

int main()
{
    int N = 8;
    double S0 = 106.0;
    double r = 0.058;
    double sigma = 0.46; 
    double T = (double) 9/12;
    double K = 100.0; 
    
    cout << setiosflags(ios::fixed) << setprecision(5);
    
    BlackScholes BSModel(S0,r,sigma,T,N);
    BinomialTreeModel Model = BSModel.BinomialTree();
    
    Call call(N,K);
    OptionCalculation callCalculation(&call); 
    
    BinLattice<double> CallPriceTree(N); 
    BinLattice<bool> CallStoppingTree(N);
    
    cout<<"S0 = "<<S0<<endl;
    cout<<"r = "<< r <<endl; 
    cout<<"sigma = "<<sigma<<endl; 
    cout<<"T = "<<T<<endl;
    cout<<"K = "<<K<<endl; 
    cout<<"N = "<<N<<endl; 
    cout<<endl; 
    
    cout<<"U= "<<BSModel.cal_U()<<endl; 
    cout<<"D = "<<BSModel.cal_D()<<endl; 
    cout<<"R = "<<BSModel.cal_R()<<endl; 
    cout<<endl; 
    
    cout<<"America Call Option Price = "<<fixed<<setprecision(3)<<callCalculation.PriceBySnell(Model, CallPriceTree, CallStoppingTree) << endl; 
    return 0; 
    
}

/*

S0 = 106.00000
r = 0.05800
sigma = 0.46000
T = 0.75000
K = 100.00000
N = 8

U= 1.15125
D = 0.86862
R = 1.00545

America Call Option Price = 21.682

*/