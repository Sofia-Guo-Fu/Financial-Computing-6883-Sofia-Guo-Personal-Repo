#pragma once
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std; 

namespace fre{
    // define a BinLattice class
    class BinLattice
    {
        private:
            // 2 variables
            int N; 
            // a vector of vector of doubles called Lattice
            vector<vector<double>> Lattice; 
        public:
            // default constructor 
            BinLattice():N(0){}
            // constructor with parameters
            BinLattice(int N_):N(N_)
            {
                //inside Lattcie.resize(...)
                // N+1 time steps vertically
                Lattice.resize(N+1); 
                // for each time step n, there is n nodes
                for (int n=0; n<=N; n++)
                {
                    Lattice[n].resize(n+1); 
                }
            }
            ~BinLattice(){}
            // member functions
            void SetN(int N_)
            {
                // rewrite
                N = N_;
                Lattice.resize(N+1);
                for(int n=0;n<=N;n++) Lattice[n].resize(n+1); 
            }
            
            void SetNode(int n, int i, double x)
            {
                Lattice[n][i] = x; 
            }
            double GetNode(int n, int i)
            {
                return Lattice[n][i]; 
            }
            // Display() function 
            void Display()
            {
                cout<<setiosflags(ios::fixed)<<setprecision(3); 
                
                for(int n=0;n<=N;n++)
                {
                    for(int i=0;i<=n;i++)
                    {
                        cout<<setw(15)<<GetNode(n,i); 
                    }
                    cout<<endl; 
                }
                cout<<endl; 
            }
    }; 
}