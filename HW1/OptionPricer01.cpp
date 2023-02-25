// OptionPricer01.cpp
//

#include "BinomialTreeModel.h"
#include "Option01.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace fre;

int main()
{
    double u = 1.15125, d = 0.86862, r = 1.00545;
    double s0 = 106.00;
    double k = 100.00;
    const unsigned int N = 8;
    
    // Change to call my version 1 HW1PriceByCRR Function
    double optionPrice1 = HW1PriceByCRR(s0, u, d, r, N, k);
    cout << "European call option price version 1= " << fixed << setprecision(2) << optionPrice1 << endl;
    
    // Call my version 2 HW1V2PriceByCRR Function 
    double optionPrice2 = HW1V2PriceByCRR(s0,u,d,r,N,k);
    cout << "European call option price version 2 ="<< fixed << setprecision(2) << optionPrice2 << endl;
    
    cout << "We are done!"<<endl;
    
    return 0;
}

/*
I got the correct answer: 

European call option price version 1= 21.68
European call option price version 2 =21.68
We are done!

*/
