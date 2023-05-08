#include "BinomialTreeModel.h"
#include<iostream>
#include <cmath>

using namespace std; 

namespace fre{
     double RiskNeutProb(double U, double D, double R)
    {
        return (R-D)/(U-D);
    }
    
     double CalculateAssetPrice(double S0, double U, double D, int n, int i)
    {
        return S0 * pow(U,i) * pow(D,n-i);
    }
    
    int GetInputData(double &S0, double &U, double &D, double &R)
    {   
        // enter data
        cout<<"Enter S0"; cin>>S0; 
        cout<<"Enter U"; cin>>U; 
        cout<<"Enter D"; cin>>D;
        cout<<"Enter R"; cin>>R; 
        cout<<endl; 
        
        // make sure S0>0; U>D>0; R>0
        if (S0<=0.0|| U<=0.0|| D<=0.0|| U<D || R<=0.0)
        {
            cout<<"Illegal data ranges"<<endl; 
            cout<<"Terminating program"<<endl; 
            return -1; 
        }
        
        // checking for arbitrage
        if (R>=U || U<= D)
        {
            cout<<"Arbitrage Exits!"<<endl;
            cout<<"Terminating program "<<endl; 
            return -1; 
        }
        
        // after everything is fine
        cout<<"Input data checked"<<endl; 
        cout<<"There is no arbitrage"<<endl; 
        
        return 0; 
    }
}
