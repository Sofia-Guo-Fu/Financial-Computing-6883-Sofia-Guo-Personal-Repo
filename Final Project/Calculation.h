#pragma once
#include "Stock.h"
#include "Helper.h"

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include <set>

using namespace std;

namespace fre
{
    typedef map<string, Stock> StockMap; 
    
    class Calculation
    {
        private:
            int N;
            Benchmark benchmark;
            // map<string,double> AR; //abonormal return 
        public:
            Calculation(int N_, Benchmark b)
            {
                N = N_;
                benchmark = b;
            }
            ~Calculation(){}
            
            // shuffle
            StockMap shuffle(StockMap &group); 
            // calculate AAR, CAAR
            vector<double> calculate_AAR(StockMap &group);
            vector<double> calculate_CAAR(StockMap &group); 
            // Bootstrapping, loop 40 times
            Matrix calculate_Avg_Std(StockMap &group); 
           
            void SetN(int N_){N = N_;}
    }; 
    
    
    // member function definition outside
    int temp = 0; 
    
     StockMap Calculation::shuffle(StockMap &group)
    {
        vector<string> ticker_list; 
        // return 
        map<string, Stock> group_selected; 
        // populate ticker_list
        for(map<string,Stock>::iterator itr=group.begin(); itr != group.end(); itr++)
        {
            ticker_list.push_back(itr->first); 
        }
        
        unsigned int M = 80; //80
        int N = group.size(); 
        
        set<int> s; 
        
        while(s.size() < M)
        {
            int random_value = (rand() % (N)); 
            s.insert(random_value); 
        }
        
        for (std::set<int>::iterator it = s.begin(); it != s.end(); it++)
        {
            group_selected.insert(pair<string, Stock>(ticker_list[*it], group[ticker_list[*it]])); 
        }
        
        temp ++; 
        cout<<"success shuffle!"<<temp<<endl; 
        return group_selected; 
    }
    
    //calculate AAR
    vector<double> Calculation::calculate_AAR(StockMap &group_selected)
    {
        // initialize a vector of double to store AAR
        vector<double> AAR(2 * N, 0); 
        
        int M = group_selected.size();
        
        for(map<string, Stock>::iterator itr = group_selected.begin(); itr != group_selected.end(); itr++)
        {
            itr->second.CalculateAR(benchmark);
            AAR = AAR + itr->second.GetAR(); 
        }
        AAR = AAR / M;
        return AAR; 
    }
    
    // calculate CAAR
    vector<double> Calculation::calculate_CAAR(StockMap &group_selected)
    {
        vector<double> CAAR(2 * N, 0); 
        vector<double> AAR = calculate_AAR(group_selected);
        
        double sum = 0.0;
        for (int i=0; i< 2 * N; i++)
        {
            sum += AAR[i]; 
            CAAR[i] = sum; 
        }
        return CAAR;
    }
    
    // Matrix: AAR_Avg, AAR_std, CAAR_Avg, CAAR_std for beat, meet, miss groups
    // Bootstrapping: 40 times 
    Matrix Calculation::calculate_Avg_Std(StockMap &group)
    {
        int temp = 0; 
        // initialize four vectors of double
        Vector AAR_Avg(2 * N, 0);
        Vector AAR_Std(2 * N, 0); 
        Vector CAAR_Avg(2 * N, 0); 
        Vector CAAR_Std(2 * N, 0); 
        
        // initialize two temp Matrices to store 40 ARs and 40 CAARs
        Matrix AAR_temp(40, Vector(2 * N, 0));
        Matrix CAAR_temp(40, Vector(2 * N, 0));
        // initliaze two sum vectors
        Vector AAR_sum(2 * N, 0);
        Vector CAAR_sum(2 * N, 0);
        Vector AAR_stdsum(2 * N, 0);
        Vector CAAR_stdsum(2 * N, 0);
        // initialize 2 temp Matrices to store 40 aARs and 40 CAARs
        for(int i=0; i<40; i++)
        {
            StockMap group_picked = shuffle(group);
            Vector AAR = calculate_AAR(group_picked); 
            Vector CAAR = calculate_CAAR(group_picked); 
            
            AAR_temp[i] = AAR;
            CAAR_temp[i] = CAAR;
            
            AAR_sum = AAR_sum + AAR;
            CAAR_sum = CAAR_sum + CAAR; 
            
            temp ++; 
            //cout<<temp<<endl; 
        }
        // outside of for loop, calculate the AAR_Avf, CAAR_Avg
        AAR_Avg = AAR_sum / 40; 
        CAAR_Avg = CAAR_sum / 40; 
            
        // update the temp matrices by subtracting the mean vector
        AAR_temp = AAR_temp - AAR_Avg;  //Matrix - Vector
        AAR_temp = AAR_temp * AAR_temp;  // Matrix * Matrix
        CAAR_temp = CAAR_temp - CAAR_Avg; //Matrix - Vector
        CAAR_temp = CAAR_temp * CAAR_temp; // Matrix * Matrix
            
        // Calculate AAR_Std, CAAR_Std
        for (int i = 0; i < 40; i++)
        {
            // update the sum vectors
            AAR_stdsum = AAR_stdsum + AAR_temp[i];
            CAAR_stdsum = CAAR_stdsum + CAAR_temp[i];
        }
        // calculate standard deviation of the vector
        AAR_Std = sqrt(AAR_stdsum / 40);  // SQRT(Vector); Vector/double;
        CAAR_Std = sqrt(CAAR_stdsum / 40);
            
        // Populate final matrix
        Matrix m(4); 
        
        m[0] = AAR_Avg;
        m[1] = AAR_Std;
        m[2] = CAAR_Avg;
        m[3] = CAAR_Std; 
        return m; 
    }
    
    // void final_result(StockMap& BeatGroup, StockMap& MeetGroup, StockMap& MissGroup,
    //                         Matrix& m1, Matrix& m2, Matrix& m3)
    // {
    //     Matrix m0 = calculate_Avg_Std(BeatGroup);
    //     Matrix m1 = calculate_Avg_Std(MeetGroup);
    //     Matrix m2 = calculate_Avg_Std(MissGroup); 
    // }
    
    
}
    
    