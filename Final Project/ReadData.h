#pragma once
#include <stdio.h>
#include <cstring>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <fstream>
#include "curl/curl.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Stock.h"
#include "Helper.h"

using namespace std;

namespace fre{
    
    class ReadData
    {
        private:
            int N; 
            string url_common = "https://eodhistoricaldata.com/api/eod/";
            string api_token = "64447a8f8d87a3.07288017";
            string start; // start date entered by user
            string end; // end date entered by user 
            
            const string annoucement_file = "Russell3000EarningsAnnouncements.csv";
            const char* MarketCalendarFile = "market_calendar.txt"; 

            vector<string> market_calendar_vector;
            vector<string> ticker_list; 
            map<string, Stock> StockGroup; // string: Stock
            Benchmark benchmark; // object of Benchmark
            map<string, string> start_date_map; // for every EA_date, calculate start date
            map<string, string> end_date_map; // for every EA_date, calculate end date
        
        public:
            ReadData(int N_){ N = N_;}
            ~ReadData(){}
            
            void ReadFromCalendar(); 
            void ReadfromAnn(); // read from Russell3000EarningsAnnouncements.csv
            int ReadfromEOD(vector<string> sub_ticker_list); // read data from libcurl library
            int ReadfromEOD_MT();
            int PopulBench(); 
            
            // getter functions
            Benchmark GetBenchMark() const {return benchmark;}
            map<string, Stock> GetStockGroup() const {return StockGroup;}
            
            map<string, string> GetStartMap() const { return start_date_map;}
            map<string, string> GetEndMap() const { return end_date_map;}
    }; 
}