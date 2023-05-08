#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace fre{
    typedef vector<double> SamplePath;
    // class MCModel
    class MCModel
    {
        private:
            double S0, r, sigma;
        public:
            MCModel():S0(0.0),r(0.0),sigma(0.0){}
            MCModel(double S0_, double r_, double sigma_): S0(S0_), r(r_), sigma(sigma_)
            {
                // random seed
                srand((unsigned)time(NULL)); 
            }
            void GenerateSamplePath(double T, int m, SamplePath& S)const;
            // getter functions
            double GetS0() const{return S0;}
            double GetR() const{return r;}
            double GetSigma() const{return r;}
            // setter functions
            void SetS0(double S0_){ S0 = S0_;}
            void SetR(double r_) { r = r_;}
            void SetSigma(double sigma_){ sigma = sigma_;}
    };
}