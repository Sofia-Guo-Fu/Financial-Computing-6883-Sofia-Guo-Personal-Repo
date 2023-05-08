#include "Matrix.h"
#include <cmath>

using namespace std;

namespace fre{
    // Matrix * Vector 
    Vector operator *(const Matrix &C, const Vector &V)
    {
        int d = (int)C.size(); 
        // initialize the output vector W of size d
        Vector W(d);
        // two nested for loops
        for (int j=0; j<d;j++)
        {
            W[j] = 0.0;
            for (int l=0; l<d;l++)
            {
                W[j] = W[j] + C[j][l] * V[j]; 
            }
        }
        return W; 
    }
    // double * Vector
    Vector operator *(const double &a, const Vector &V)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j=0;j<d;j++)
        {
            U[j] = a * V[j];
        }
        return U; 
    }
    // Vector * Vector
    Vector operator *(const Vector &V, const Vector &W)
    {
        int d = (int)V.size();
        Vector U(d);
        for(int j=0;j<d;j++)
        {
            U[j] = V[j] * W[j]; 
        }
        return U;
    }
    // double + vector
    Vector operator +(const double &a, const Vector &V)
    {
        int d = (int)V.size();
        Vector U(d);
        for(int j=0;j<d;j++)
        {
            U[j] = a + V[j];
        }
        return U;
    }
    // vector + vector
    Vector operator +(const Vector &V, const Vector &W)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j=0;j<d;j++)
        {
            U[j] = V[j] + W[j];
        }
        return U; 
    }
    // exponential
    Vector exp(const Vector &V)
    {
        int d = (int)V.size();
        Vector U(d);
        for (int j=0;j<d;j++)
        {
            U[j] = std::exp(V[j]); 
        }
        return U;
    }
    // scalar operator
    double operator ^(const Vector &V, const Vector &W)
    {
        int d = (int)V.size();
        double sum = 0.0; 
        for(int j=0;j<d;j++)
        {
            sum = sum + V[j] * W[j];
        }
        return sum; 
    }
    // output Vector
    ostream &operator <<(ostream &out, Vector &V)
    {
        // use itr
        for(Vector::iterator itr = V.begin(); itr != V.end(); itr++)
        {
            out<<*itr<<" "; 
        }
        out<<endl; 
        return out; 
    }
    // output Matrix
    ostream &operator <<(ostream &out, Matrix &W)
    {
        // use itr
        for(Matrix::iterator itr = W.begin(); itr != W.end(); itr++)
        {
            out<<*itr<<" "; 
        }
        out<<endl; 
        return out; 
    }
}