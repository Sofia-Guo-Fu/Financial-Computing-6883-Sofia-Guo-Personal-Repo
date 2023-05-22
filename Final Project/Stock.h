#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <typeinfo>

using namespace std;

namespace fre
{
    class Benchmark
    {
        protected:
            string ticker; 
            string start_date = "2022-01-02"; 
            string end_date = "2023-05-12";
            map<string, double> benchmark_return_map; 
            map<string, double> benchmark_adjclose_map; 
            map<string, double> cumulative_return;
            
        public:
            Benchmark(){ticker = "IWV";}
            Benchmark(string ticker_): ticker(ticker_){}
            ~Benchmark(){}
            
            // getter functions
            string GetTicker() const {return ticker;}
            // get return 
            map<string, double> GetDailyReturn(){return benchmark_return_map; }
            map<string, double> GetCumulativeReturn(){return cumulative_return;}
            
            string GetStart(){return start_date; }
            string GetEnd(){return end_date; }
            
            // add price
            void AddPrice(string sDate, double dValue)
            {
                benchmark_adjclose_map.insert(std::make_pair(sDate, dValue)); 
            }
            
            //get adj close 
            map<string, double> GetAdj(){return benchmark_adjclose_map;}
            
            // calculate return 
            void CalculateReturn()
            {   
                map<string, double>::iterator it;
                double r = 0; 
                for(auto it = next(benchmark_adjclose_map.begin()); it != benchmark_adjclose_map.end(); it++)
                {
                    r = (it->second/prev(it)->second - 1) * 100;
                    benchmark_return_map.insert(pair<string, double> (it->first, r));
                }
            }
            
            void CalculateCumulativeReturn(){
                if(!cumulative_return.empty()) return;
                map<string, double> :: iterator itr;
                double sum = 0;
                for(itr = benchmark_return_map.begin(); itr != benchmark_return_map.end() ; itr++){
                    sum += itr->second;
                    cumulative_return.insert(pair<string,double>(itr->first,sum));
                }
            }
            
            
    }; 

    class Stock
    {
        private:
            string ticker; 
            string annDate;
            string period_ending; 
            double estimated; 
            double reported;
            double surprise;
            double surprise_percent;
            
            map<string, double> stock_return_map;
            map<string, double> stock_adjclose_map; 
            vector<double> AR;
            map<string, double> cumulative_return;
            
        public:  
            Stock(): ticker(""),annDate(""), surprise_percent(0), 
                estimated(0), reported(0), surprise(0), period_ending(""){}
        
            Stock(string t, string a, double s, double e, double r, double ss, string pe):
                ticker(t),annDate(a),surprise_percent(s), estimated(e), reported(r), surprise(ss), period_ending(pe) {} 
            ~Stock(){}
            // getter
            string GetAnnDate() const {return annDate;}
            double GetSurprisePercentage() const {return surprise_percent;}
            // GetAR
            vector<double> GetAR(){return AR;}
            string GetTicker() {return ticker;}
            string GetEnding() {return period_ending;}
            double GetEstimated() {return estimated;}
            double GetReported() {return reported;}
            double GetSurprise() {return surprise;}
            
            // get daily return, function override
            map<string, double> GetDailyReturn(){return stock_return_map; }
            map<string, double> GetCumulativeReturn(){return cumulative_return;}
            
            // add price, function override
            void AddPrice(string sDate, double dValue)
            {
                stock_adjclose_map.insert(std::make_pair(sDate, dValue)); 
            }
            
            //get adj close: override
            map<string, double> GetAdj(){return stock_adjclose_map;}
            
            // calculate return: overload 
            void CalculateReturn()
            {   
                if(!stock_return_map.empty()) return;
                map<string, double>::iterator it;
                double r = 0; 
                for(auto it = next(stock_adjclose_map.begin()); it != stock_adjclose_map.end(); it++)
                {
                    r = (it->second/prev(it)->second - 1) * 100;
                    stock_return_map.insert(pair<string, double> (it->first, r));
                }
            }
            
            void CalculateAR(Benchmark &benchmark)
            {
                
                // new established vectors
                // vector<double> valid_stock_return;
                // vector<double> valid_benchmark_return;
                if(!AR.empty()) return;
                
                map<string,double> benchmark_return_map = benchmark.GetDailyReturn(); // date: double 
                
                CalculateReturn();
                
                // get boundaries of start and end date to later silice benchmark
                map<string,double>::iterator itr_;
                for(itr_ = stock_return_map.begin();itr_!=stock_return_map.end();itr_++)
                {   
                    AR.push_back((itr_->second) - benchmark_return_map[itr_->first]);
                }
                
            }
            void CalculateCumulativeReturn(){
                if(!cumulative_return.empty()) return;
                map<string, double> :: iterator itr;
                double sum = 0;
                for(itr = stock_return_map.begin(); itr != stock_return_map.end() ; itr++){
                    sum += itr->second;
                    cumulative_return.insert(pair<string,double>(itr->first,sum));
                }
            }
    }; 
}
