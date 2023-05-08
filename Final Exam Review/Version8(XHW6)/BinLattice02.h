#pragma once
#include <iostream>
#include <fstream> // new
#include <iomanip>
#include <vector>

using namespace std;

namespace fre{
    // template
    template<typename Type>
    
    class BinLattice
    {
        private:
            int N;
            vector<vector<Type>>Lattice;
        public:
            // default constructor
            BinLattice():N(0){}
            // constructor with parameters
            BinLattice(int N_):N(N_)
            {
                Lattice.resize(N+1);
                for (int n=0;n<=N;n++) Lattice[n].resize(n+1);
            }
            ~BinLattice(){}
            
            // member function
            void SetN(int N_)
            {
                N = N_;
                Lattice.resize(N+1);
                for(int n=0;n<=N;n++) Lattice[n].resize(n+1);
            }
            
            void SetNode(int n, int i, Type x)
            {
                Lattice[n][i] = x;
            }
            
            Type GetNode(int n, int i)
            {
                return Lattice[n][i]; 
            }
            
            // Display function
            void Display()
            {
                cout<<setiosflags(ios::fixed)<<setprecision(3);
                for(int n=0;n<=N;n++)
                {
                    for (int i=0; i<=N; i++)
                    {
                        cout<<setw(15)<<GetNode(n,i); 
                    }
                    cout<<endl;
                }
                cout<<endl; 
            }
            
            // overload Display function
            void Display(ofstream & foutput)
            {   
                // all "cout" convert to "foutput" here
                foutput<<setiosflags(ios::fixed)<<setprecision(3);
                for(int n=0; n<=N; n++)
                {
                    for (int i=0; i<=N;i++)
                    {
                        foutput<<setw(15)<<GetNode(n,i);
                    }
                    foutput<<endl;
                }
                foutput<<endl; 
            }
    }; 
}