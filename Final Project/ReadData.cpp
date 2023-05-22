#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <vector>
#include <locale>
#include <iomanip>
#include <curl/curl.h>
#include <string.h>
#include "ReadData.h"
#include "Helper.h"
#include <thread>
#include <functional>
#include <mutex>

using namespace std;
using namespace fre;

// const char* cIWV3000SymbolFile = "Russell_3000_component_stocks.csv";


// global functions
//============================================================================
struct MemoryStruct
{
    char* memory;
    size_t size;
};

void* myrealloc(void* ptr, size_t size)
{
    if (ptr)
        return realloc(ptr, size);
    else
        return malloc(size);
}

int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)data;
    mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory)
    {
        memcpy(&(mem->memory[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;
    }
    return realsize;
}

//======================================================================

namespace fre
{

    void ReadData::ReadFromCalendar()
    {
        // store trading dates in a vector
        ifstream fin;
        fin.open(MarketCalendarFile); 
        string date;
        getline(fin, date); // skip first
        
        while (getline(fin, date))
        {
            market_calendar_vector.push_back(date.substr(0,10)); 
        }
        fin.close(); 
    }
    
    int ReadData:: PopulBench()
    {
        CURL* handle;
        CURLcode result;
        curl_global_init(CURL_GLOBAL_ALL);
 
        // curl_easy_init() returns a CURL easy handle 
        handle = curl_easy_init();
        
        if(handle)
        {
            struct MemoryStruct data;
            data.memory = NULL; 
            data.size = 0; 
            
            string url_request = url_common + "IWV" + ".US?" + "from=" + "2022-01-05" + "&to=" + "2022-03-03" + "&api_token=" + api_token + "&period=d";
            curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
            
            curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
            
            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
            
            result = curl_easy_perform(handle);
            
            if (result != CURLE_OK)
            {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                return -1;
            }
            
            stringstream sData;
            sData.str(data.memory);
            string sValue, sDate;
            double dValue = 0;
            string line;
            
            while(getline(sData, line))
            {
                //cout<<line<<endl;
                size_t found = line.find('-');
                if (found != std::string::npos)
                {
                sDate = line.substr(0, line.find_first_of(','));
                line.erase(line.find_last_of(','));
                sValue = line.substr(line.find_last_of(',') + 1);
                dValue = strtod(sValue.c_str(), NULL);
                //cout << "sDate " << sDate << " dValue " << dValue << endl;
                benchmark.AddPrice(sDate, dValue);
                }
            }
            free(data.memory); 
            data.size = 0; 
        }
        curl_easy_cleanup(handle);
        curl_global_cleanup();
        return 0;
    }
    
    void ReadData::ReadfromAnn()
    {
        ifstream fin;
        fin.open(annoucement_file, ios::in);
        string line, ticker, annDate, period_ending, estimate, reported, surprise,surprise_percent;
        
        getline(fin,line); //skip the first line
        
        while (!fin.eof())
        {
            getline(fin, line);
            stringstream sin(line);
            getline(sin, ticker, ',');
            getline(sin, annDate, ',');
            getline(sin, period_ending, ',');
            getline(sin, estimate, ',');
            getline(sin, reported, ',');
            getline(sin, surprise, ',');
            getline(sin, surprise_percent); 
            double surprise_percent_val = std::stod(surprise_percent);
            
            double estimate_val = std::stod(estimate);
            double reported_val = std::stod(reported);
            double surprise_val = std::stod(surprise);
            
            // populate StockGroup
            if(annDate.empty() || std::isnan(surprise_percent_val))
            {
                continue;
            }
            else
            {   
                 // populate start_date_map and end_date_map 
                int annIndex = findDateIndex(market_calendar_vector, annDate); 
                if (annIndex != -1 && (annIndex+N) < market_calendar_vector.size())
                {
                    int startIndex = annIndex - N;
                    string startDate = market_calendar_vector[startIndex]; 
                    start_date_map.insert(pair<string,string>(ticker, startDate));
                    int endIndex = annIndex + N;
                    string endDate = market_calendar_vector[endIndex];
                    end_date_map.insert(pair<string, string>(ticker, endDate));
                    
                    //populate ticker vector 
                    ticker_list.push_back(ticker);
                     // populate StockGroup
                    Stock s(ticker, annDate,double(surprise_percent_val), double(estimate_val), double(reported_val), double(surprise_val), period_ending);
                    StockGroup.insert(pair<string, Stock>(ticker, s));
                }
                
            }
        }
    }
    
        int ReadData::ReadfromEOD_MT() {
        //cut up whole ticker list based on specified number of threads. run readfromeod MT with each sub vector
        int threadnum = 4, m = 0;
        int sub_ticker_list_size = ceil(ticker_list.size() / (threadnum - 1));
        vector<vector<string>> list_of_sub_ticker_lists(threadnum);
        for (auto i = 0; i < list_of_sub_ticker_lists.size(); i++) {
            list_of_sub_ticker_lists[i].resize(sub_ticker_list_size);
        }
        // for (int i = 0; i < (int)ticker_list.size(); i++) {
        //     if (i <= sub_ticker_list_size * (m + 1)) {
        //         int ind = i - m * sub_ticker_list_size;
        //         list_of_sub_ticker_lists[m];
        //         list_of_sub_ticker_lists[m][ind] = ticker_list[i];
        //     }
        //     else {
        //         m += 1;
        //         int ind = i - m * sub_ticker_list_size;
        //         list_of_sub_ticker_lists[m][ind] = ticker_list[i];
        //     }
        // }
        for (int i = 0; i < (int)ticker_list.size(); i++) {
            if (i <= sub_ticker_list_size * (m + 1)) {
                int ind = i - m * sub_ticker_list_size;
                list_of_sub_ticker_lists[m].push_back(ticker_list[i]);
            }
            else {
                m += 1;
                int ind = i - m * sub_ticker_list_size;
                list_of_sub_ticker_lists[m].push_back(ticker_list[i]);
            }
        //cout<<"split ok"<<endl;
        }
        

        
        // Create the threads
        int num_threads = 4;  // Set the number of threads you want to use
        vector<thread> threads;
        for (int i = 0; i < num_threads; i++) {
        //    cout<<i<<"i"<<endl;
            vector<string> subvector = list_of_sub_ticker_lists[i];
        //    cout<<"pass vector"<<endl;
            threads.push_back(std::thread(std::bind(&ReadData::ReadfromEOD, this, subvector)));
       //     cout<<"threadend"<<endl;
        
        }
        //cout<<"join"<<endl;
        for (auto& t: threads) {
            t.join();
        //    cout<<"joined"<<endl;
        }
        return 0;
    }
    
    int ReadData::ReadfromEOD(vector<string> sub_ticker_list)
    {
        cout<<"downloading data, please wait..."<<endl;
        CURL* handle;
        CURLcode result;
        curl_global_init(CURL_GLOBAL_ALL);
        handle = curl_easy_init();
        
        if (handle)
        {
            vector<string>::iterator itr =sub_ticker_list.begin();
            // loop through ticker list 
            // int temp1 = 0; 
            for (; itr != sub_ticker_list.end(); itr++)
            {
                struct MemoryStruct data;
                data.memory = NULL;
                data.size = 0;
                
                // get 
                string symbol = *itr;
                string start = start_date_map[*itr]; 
                string end = end_date_map[*itr]; 
                
                string url_request = url_common + symbol + ".US?" + "from=" + start + "&to=" + end + "&api_token=" + api_token + "&period=d";
                curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());

                //adding a user agent
                curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
                curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
                curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
                result = curl_easy_perform(handle);

                if (result != CURLE_OK)
                {
                    // if errors have occured, tell us what is wrong with result
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
                    return 1;
                }
                
                // ================================read data============================
                // stringstream sData;
                
                // ensure that the std::stringstream is only initialized with a non-null pointer
                if (data.memory != nullptr)
                {
                    stringstream sData;
                    sData.str(data.memory);
                    string sValue, sDate;
                    double dValue = 0;
                    string line;
                    
                    int count = 0; 
                    getline(sData,line);
                    while (getline(sData, line))
                    {   
                        //cout << line << endl;
                        size_t found = line.find('-');
                        
                        if (found != std::string::npos)
                        {
                            sDate = line.substr(0, line.find_first_of(','));
                            line.erase(line.find_last_of(','));
                            sValue = line.substr(line.find_last_of(',') + 1);
                            dValue = strtod(sValue.c_str(), NULL);
                            std::lock_guard<std::mutex> guard(mutex); // Lock the mutex
                            // skip empty
                            if(sDate.empty() || std::isnan(dValue))
                            {
                                StockGroup.erase(*itr); 
                                break; 
                            }
                            else
                            {
                                StockGroup[*itr].AddPrice(sDate, dValue); 
                                //cout<<dValue<<endl;
                            }
                        }
                        else
                        {
                            StockGroup.erase(*itr);
                            break; 
                        }
                    }
                }
                free(data.memory);
                data.size = 0;
            }
            
        }
        else
        {
            
            fprintf(stderr, "Curl init failed!\n");
            return -1;
        }
        // cleanup since you've used curl_easy_init
        curl_easy_cleanup(handle);
        // release resources acquired by curl_global_init() 
        curl_global_cleanup();
        return 0;
    }

        
}
    
    
