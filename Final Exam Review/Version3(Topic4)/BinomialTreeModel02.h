#pragma once

namespace fre{
    class BinomialTreeModel
    {
        private:
            // private data members * 4: S0,U,D,R
            double S0;
            double U;
            double D;
            double R;
        public:
            // default constructor
            BinomialTreeModel():S0(0.0),U(0.0),D(0.0),R(0.0){}
            // constructor with paramters
            BinomialTreeModel(double S0_, double U_, double D_, double R_):
                S0(S0_),U(U_),D(D_),R(R_){}
            // copy constructor
            BinomialTreeModel(const BinomialTreeModel&B): S0(B.S0),U(B.U),D(B.D),R(B.R){}
            // destructor 别忘记写了！
             ~BinomialTreeModel() {}
            
            // memeber functions
            double RiskNeutProb() const; 
            double CalculateAssetPrice(int n, int i) const; 
            void UpdateBinomialTreeModel(double S0_, double U_, double D_, double R_);
            int GetInputData(); 
            // member functions to access private data members
            double GetS0() const{return S0;}
            double GetU() const {return U;}
            double GetD() const {return D;}
            double GetR() const {return R;}
    }; 
}

