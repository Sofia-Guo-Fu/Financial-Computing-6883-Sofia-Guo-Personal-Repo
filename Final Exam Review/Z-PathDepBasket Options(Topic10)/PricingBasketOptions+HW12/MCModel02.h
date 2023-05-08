#pragma once
#include "Matrix.h"
#include <cmath>
#include <vector>

namespace fre{
    // SamplePath is now a vector of Vector
    typedef vector<Vector> SamplePath;
    class MCModel
    {
        private:
            Vector S0, sigma;
            Matrix C;
            double r; // risk-free rate is a double
        public:
            // constructor with parameters, write it outside
            MCModel(Vector S0_, double r_, Matrix C_); 
            // GenerateSamplePath
            void GenerateSamplePath(double T, int m, SamplePath &S) const;
            
            // getter functions, note the return type
            Vector GetS0() const {return S0;}
            Vector GetSigma() const {return sigma;}
            Matrix GetC() const {return C;}
            double GetR() const {return r;}
            
            // setter functions
            void SetS0(const Vector &S0_) {S0 = S0_;}
            void SetSigma(const Vector &sigma_){sigma = sigma_;}
            void SetC(const Matrix &C_){C = C_;}
            void SetR(double r_){r = r_;}
    };
}