#include "Helper.h"
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include <iomanip>
#include <map>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <random>
using namespace std;

namespace fre {
// Matrix * Vector
Vector operator*(const Matrix& C, const Vector& V)
{
    int d = (int)C.size();
    Vector W(d);
    for (int j = 0; j < d; j++)
    {
        W[j] = 0.0;
        for (int l = 0; l < d; l++) W[j] = W[j] + C[j][l] * V[l];
    }
    return W;
}

// Matrix * Matrix
Matrix operator*(const Matrix& M, const Matrix& W)
{
    int d = (int)M.size();
    int m = (int)M[0].size();
    Matrix U(d, Vector(m, 0));
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            U[i][j] = M[i][j] * W[i][j];
        }
    }
    return U;
}

// Vector * double
Vector operator*(const Vector& V, const double& a)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = a * V[j];
    return U;
}

// Vector * Vector
Vector operator*(const Vector& V, const Vector& W)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] * W[j];
    return U;
}

// Vector / double
Vector operator/(const Vector& V, const double& a)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] / a;
    return U;
}

// Added：Vector / Vector, maybe edge cases need redefine
Vector operator/ (const Vector& V, const Vector& W)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] / W[j];
    return U;
}

// Vector + double
Vector operator+(const double& a, const Vector& V)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = a + V[j];
    return U;
}

// Vector + Vector
Vector operator+(const Vector& V, const Vector& W)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = V[j] + W[j];
    return U;
}

// Matrix - Vector
Matrix operator-(const Matrix& V, const Vector& W)
{
    int d = (int)V.size();
    int m = (int)W.size();
    Matrix U(d, Vector(m, 0));
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            U[i][j] = V[i][j] - W[j];
        }
    }
    return U;
}

// square root: sqrt(V)
Vector sqrt(const Vector& V)
{
    int d = (int)V.size();
    Vector U(d);
    for (int j = 0; j < d; j++) U[j] = std::sqrt(V[j]);
    return U;
}

// scalar operator
double operator^(const Vector& V, const Vector& W)
{
    double sum = 0.0;
    int d = (int)V.size();
    for (int j = 0; j < d; j++) sum = sum + V[j] * W[j];
    return sum;
}

// Overload cout for Vector
ostream& operator<<(ostream& out, Vector& V)
{
    int count = 0;
    for (Vector::iterator itr = V.begin(); itr != V.end(); itr++)
    {
        out << fixed << setprecision(3);
        out << setiosflags(ios::left) << setw(10) << *itr;
        count = count + 1;
        if (count % 11 == 0)
        {
            cout << endl;
        }
    }
    out << endl;
    return out;
}

// Overload cout for Matrix
ostream& operator<<(ostream& out, Matrix& W)
{
    for (Matrix::iterator itr = W.begin(); itr != W.end(); itr++)
    out << *itr;    // Use ostream & operator<<(ostream & out, Vector & V)
    out << endl;
    return out;
}

int findDateIndex(std::vector<std::string>& dates, std::string& targetDate) 
    {   
        
        //cout << dates[1].substr(0,10).length() << "equal?" << targetDate.length() << endl;
        for (unsigned int i = 1; i < dates.size(); i++) 
        {   
            
            if (dates[i].substr(0,10) == targetDate) 
            {
                return i;  // Return the index when the target date is found
                
            }
            else
            {
                continue; 
            }
        }
        return -1;  // Return -1 if the target date is not found in the vector
    }

    // fill premade miss, meet, beat maps with stock:surprise 
    void splitStocks(const map<string, double>& data, map<string, double>& miss, map<string, double>& meet, map<string, double>& beat) 
    {
        vector<pair<string, double>> stockVector; // vector of (stock:data)
        for (const auto& pair:data) // It loops through each pair in the data map and adds them to the stockVector vector
        {
            stockVector.push_back(pair);
        }
        sort(stockVector.begin(), stockVector.end(),[](const pair<string, double>& a, const pair<string, double>& b) 
        // It sorts the stockVector vector in ascending order based on the second element of each pair (the stock values) using a lambda function as the comparison criterion.
        {return a.second < b.second;});
        
        int totalStocks = stockVector.size();
        int groupSize = ceil(static_cast<double>(totalStocks) / 3.0); // determine size of each group
        for (int i = 0; i < totalStocks; i++) // fill the three maps that's used in sampling
        {
            if (i < groupSize) 
            {
                miss.insert(pair<string, double>(stockVector[i].first, stockVector[i].second));
            }
            else if (i < 2 * groupSize) 
            {
                meet.insert(pair<string, double>(stockVector[i].first, stockVector[i].second));
            }
            else 
            {
                beat.insert(pair<string, double>(stockVector[i].first, stockVector[i].second));
            }
        }
        
    }
}

