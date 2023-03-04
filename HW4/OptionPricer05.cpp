#include <iostream>
#include <iomanip>
#include "BinomialTreeModel02.h"
#include "Option05.h"
using namespace std;
using namespace fre;

int main()
{
    int N = 8;
    double U = 1.15125, D = 0.86862, R = 1.00545;
    double S0 = 106.00, K = 100.00;
    double K1 = 100, K2 = 110;
    //Object 1: Model 
    BinomialTreeModel Model(S0,U,D,R);
    
    //Object 2: call
    Call call(N,K);
    //Object 3: callCalculation. EurOption *pOption <=> & call
    OptionCalculation callCalculation(&call);
    cout<<"European call= "<<fixed<<setprecision(2)<<callCalculation.PriceByCRR(Model)<<endl;
    
    //Object 4: put
    Put put(N,K);
    //Object 5: putCalculation
    OptionCalculation putCalculation(&put);
    cout<<"European put= "<<fixed<<setprecision(2)<<putCalculation.PriceByCRR(Model)<<endl;
    
    
    //Object 6: bullspread
    BullSpread bullspread(N,K1,K2);
    //Object 7: bullspreadCalculation
    OptionCalculation bullspreadCalculation(&bullspread);
    cout<<"European bull spread= "<<fixed<<setprecision(2)<<bullspreadCalculation.PriceByCRR(Model)<<endl;
    
    //Object 8: bearspread
    BearSpread bearspread(N,K1,K2);
    //Object 9: bearspreadCalculation
    OptionCalculation bearspreadCalculation(&bearspread); 
    cout<<"European bear spread= "<<fixed<<setprecision(2)<<bearspreadCalculation.PriceByCRR(Model)<<endl;
    return 0;
    
}

//I got the correct answer
/*

European call= 21.68
European put= 11.43
European bull spread= 4.72
European bear spread= 4.86

*/