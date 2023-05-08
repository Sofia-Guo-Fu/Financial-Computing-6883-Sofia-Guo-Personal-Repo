#pragma once
#include <vector>
#include <iostream>

using namespace std;

namespace fre{
    
    typedef vector<double> Vector;
    typedef vector<Vector> Matrix;
    
    // overload operators as independent functions 
    // the keyword const is to ensure the operator 
    // do not change the parameters passed by reference
    Vector operator *(const Matrix &C, const Vector &V);
    Vector operator *(const double &a, const Vector &V);
    Vector operator *(const Vector &V, const Vector &W);
    Vector operator +(const double &a, const Vector &V);
    Vector operator +(const Vector &V, const Vector &W); 
    // exponential
    Vector exp(const Vector &V); 
    // scalar operator
    double operator ^(const Vector &V, const Vector &W);
    // overload cout for Vector
    ostream &operator <<(ostream &out, Vector &V); 
    // overload cout for Matrix
    ostream &operator <<(ostream &out, Matrix &W); 
}