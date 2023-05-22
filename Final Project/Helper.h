#pragma once
#include <stdio.h>
#include <string>
#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <cmath>
#include <map>
#include "curl/curl.h"

using namespace std;

namespace fre {
typedef vector<double> Vector;
typedef vector<Vector> Matrix;

// overload operators as independent functions
Vector operator*(const Matrix& C, const Vector& V); // Matrix * Vector
Matrix operator*(const Matrix& M, const Matrix& W); // Matrix * Matrix
Vector operator*(const Vector& V, const double& a); // Vector * double
Vector operator*(const Vector& V, const Vector& W); // Vector * Vector

Vector operator/(const Vector& V, const double& a); // Vector / double
Vector operator/ (const Vector& V, const Vector& W); // Vector / Vector

Vector operator+(const double& a, const Vector& V); // Vector +  double
Vector operator+(const Vector& V, const Vector& W); // Vector + Vector
Matrix operator-(const Matrix& V, const Vector& W); // Matrix - Vector

Vector sqrt(const Vector& V); // sqrt(Vector)

double operator^(const Vector& V, const Vector& W); // scalar operator
ostream& operator<<(ostream& out, Vector& V); // Overload cout for Vector
ostream& operator<<(ostream& out, Matrix& W); // Overload cout for Matrix

int findDateIndex(std::vector<std::string>& dates, std::string& targetDate);
    
void splitStocks(const map<string, double>& data,map<string, double>& group1,map<string, double>& group2,map<string, double>& group3) ;

    
}
