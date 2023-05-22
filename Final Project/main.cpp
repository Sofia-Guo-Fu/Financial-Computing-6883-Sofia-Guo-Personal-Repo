#include "ReadData.h"
#include "Stock.h"
#include "Calculation.h"
#include "Helper.h"
#include "gnuplot.h"
#include <map>
#include <vector>
#include <string>
#include <time.h>
#include<cstring>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace fre;

void printMap(const std::map<std::string, double>& myMap) 
{
    for(const auto& pair : myMap) 
    {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

void printVector(const vector<double> &myVec)
{
    for (unsigned int i=0; i<myVec.size(); i++)
    {
        cout<<myVec[i]<<std::endl; 
    }
}

void printStock(Stock s, map<string,string> stt, map<string, string> end, Benchmark benchmark){
    cout << "ticker " << s.GetTicker() << endl;
    cout << "ann " << s.GetAnnDate() << endl;
    cout << "start date " << stt[s.GetTicker()] << endl;
    cout << "end date " << end[s.GetTicker()] << endl;
    // cout << s.GetSurprise() << endl;
    printMap(s.GetAdj());
    cout<< "adj price" << s.GetAdj().size() << endl;
    s.CalculateReturn();
    printMap(s.GetDailyReturn());
    s.CalculateAR(benchmark); 
    printVector(s.GetAR()); 
    
}

void printstockmap(map<string,Stock> m){
    for(const auto& pair : m) 
    {
        std::cout << "Key: " << pair.first <<endl;
    }
}

typedef map<string,Stock> StockMap;

int main()
{
    map<string,double> surprise_percent_map;
     
    map<string,double> beat;
    map<string,double> meet;
    map<string,double> miss;
    
    map<string, Stock> beatGroup;
    map<string, Stock> meetGroup;
    map<string, Stock> missGroup;
    
    // bool menu = true; 
    int choice = 0;
    int N = 0; 
    
    
    Matrix BeatMatrix;
    Matrix MeetMatrix;
    Matrix MissMatrix;
               
               
    while (choice != 5)
    {
        cout<<"-----------------------------------Program starts------------------------"<<endl; 
        cout<<endl; 
        cout<<"Menu"<<endl; 
        cout<<"1. Enter the number N. N has to larger or equal to 60"<<endl;
        cout<<"2. Enter the stock you want to know"<<endl;
        cout<<"3. Please enter the group you want to select:"<<endl;
        cout<<"4. Plot the average CAAR for each of three groups"<<endl;
        cout<<"5. Exit the program"<<endl;
        cout<<"Enter the number from 1 to 5."<<endl;
        cin>>choice;
       // getchar();
        cout<<endl;
        while ((choice > 5 || choice <= 0)) {
            cout << "------------------------------------REMINDER----------------------------------" << endl << endl;
            cout << "Invalid option. Please input a number from 1 to 5" << endl;
            cout << "1. Reset the number N" << endl;
            cout << "2. Pull info of a single stock" << endl;
            cout << "3. Show AAR, AAR-STD, CAAR and CAAR-STD for one group" << endl;
            cout << "4. Show the gnuplot graph with CAAR for all 3 groups" << endl;
            cout << "5. Exit" << endl << endl;
            cout << "Please Enter Number 1-5: ";
            cin >> choice;
            getchar();
            cout << endl;
            cout << "-----------------------------------FUNCTION-----------------------------------" << endl << endl;
        }
        // int intchoice = stoi(choice); 
        switch(choice)
        {
            case 1:
            {
                cout<<"Enter a number of N: "<<endl;
                cin>>N; 
                while(N<60)
                {
                    cout<<"Input Number is Invalid. Please enter a number larger or equal to 60! "<<endl; 
                    cin>>N; 
                }
                ReadData readData(N); 
                readData.ReadFromCalendar();
                readData.PopulBench(); 
    
                Benchmark benchmark = readData.GetBenchMark(); 
                benchmark.CalculateReturn(); 
                
                readData.ReadfromAnn();
                readData.ReadfromEOD_MT();
    
                StockMap StockGroup = readData.GetStockGroup();
                map<string,string> startMap = readData.GetStartMap();
                map<string,string> endMap = readData.GetEndMap();
                
                for (const auto& entry : StockGroup)
                {
                    const string& ticker = entry.first;
                    const Stock& tmp = entry.second;
                    double surprise_percent = tmp.GetSurprisePercentage();
                    surprise_percent_map[ticker] = surprise_percent;
                }
    
                splitStocks(surprise_percent_map,miss,meet,beat);
    
                for (const auto& entry : beat)
                {
                    const string& ticker = entry.first;
                    beatGroup.insert(pair<string, Stock>(ticker, StockGroup[ticker]));
                }
                
                for (const auto& entry : meet)
                {
                    const string& ticker = entry.first;
                    meetGroup.insert(pair<string, Stock>(ticker, StockGroup[ticker]));
                }
                
                for (const auto& entry : miss)
                {
                    const string& ticker = entry.first;
                    missGroup.insert(pair<string, Stock>(ticker, StockGroup[ticker]));
                }
                
                
                cout<<"The number of Stocks in Beat Group is: "<<beatGroup.size()<<endl; 
                cout<<"The number of Stocks in Meet Group is: "<<meetGroup.size()<<endl;
                cout<<"The number of Stocks in Miss Group is: "<<missGroup.size()<<endl;
                
                Calculation calculation(N,benchmark);
                 
              
                BeatMatrix = calculation.calculate_Avg_Std(beatGroup);
                
                MeetMatrix = calculation.calculate_Avg_Std(meetGroup);
                
                MissMatrix = calculation.calculate_Avg_Std(missGroup);
                
                break; 
            }
            
            case 2:
            {
                cout<<"Enter the ticker of the stock: "<<endl; 
                string key;
                cin>>key;
                
                bool found = false;
                
                // Search in the beatGroup map
                if (beatGroup.find(key) != beatGroup.end()) 
                {
                    found = true;
                    beatGroup[key].CalculateReturn();
                    beatGroup[key].CalculateCumulativeReturn();
                    
                    
                    cout<<"Daily Price"<<endl;
                    printMap(beatGroup[key].GetAdj());
                    cout<<"Cumulative Daily Return"<<endl;
                    printMap(beatGroup[key].GetCumulativeReturn());
                    cout<<"The stock belongs to Beat Group "<<endl;
                    cout<<"Earning Announcement Date "<<beatGroup[key].GetAnnDate()<<endl;
                    cout<<"Period Ending "<<beatGroup[key].GetEnding()<<endl;
                    cout<<"Estimated "<<beatGroup[key].GetEstimated()<<endl;
                    cout<<"Reported Earnings "<<beatGroup[key].GetReported()<<endl;
                    cout<<"Surprise "<<beatGroup[key].GetSurprise()<<endl;
                    cout<<"Surprise Percent "<<beatGroup[key].GetSurprisePercentage()<<endl;
                }
                
                // If key is not found in beatGroup, search in the meetGroup map
                else if (meetGroup.find(key) != meetGroup.end()) {
                    found = true;
                    meetGroup[key].CalculateReturn();
                    meetGroup[key].CalculateCumulativeReturn();
        
                    
                    cout<<"Daily Price"<<endl;
                    printMap(meetGroup[key].GetAdj());
                    cout<<"Cumulative Daily Return"<<endl;
                    printMap(meetGroup[key].GetCumulativeReturn());
                    
                    cout<<"The stock belongs to Meet Group "<<endl;
                    cout<<"Earning Announcement Date "<<meetGroup[key].GetAnnDate()<<endl;
                    cout<<"Period Ending "<<meetGroup[key].GetEnding()<<endl;
                    cout<<"Estimated "<<meetGroup[key].GetEstimated()<<endl;
                    cout<<"Reported Earnings "<<meetGroup[key].GetReported()<<endl;
                    cout<<"Surprise "<<meetGroup[key].GetSurprise()<<endl;
                    cout<<"Surprise Percent "<<meetGroup[key].GetSurprisePercentage()<<endl;
                }
                
                // If key is not found in meetGroup, search in the missGroup map
                else if (missGroup.find(key) != missGroup.end()) 
                {
                    found = true;
                    
                    missGroup[key].CalculateReturn();
                    missGroup[key].CalculateCumulativeReturn();
                    
                    
                    cout<<"Daily Price"<<endl;
                    printMap(missGroup[key].GetAdj());
                    cout<<"Cumulative Daily Return"<<endl;
                    printMap(missGroup[key].GetCumulativeReturn());
                    
                    cout<<"The stock belongs to Miss Group "<<endl;
                    
                    cout<<"Earning Announcement Date "<<missGroup[key].GetAnnDate()<<endl; 
                    cout<<"Estimated "<<missGroup[key].GetEstimated()<<endl;
                    cout<<"Reported Earnings "<<missGroup[key].GetReported()<<endl;
                    cout<<"Surprise "<<missGroup[key].GetSurprise()<<endl;
                    cout<<"Surprise Percent "<<missGroup[key].GetSurprisePercentage()<<endl;
                }
                
                if (found == false)
                {
                    cout << "false" << endl;
                   
                    
                }
                break;
            }

            case 3:
            {   
                string selectnum;
                cout << "Please enter the group you want to select: " << endl
                << "1. Beat group" << endl
                << "2. Meet group" << endl
                << "3. Miss group" << endl
                << endl;
                cout << "Please Enter Number from 1 to 3: " << endl;
                // cin >> selectnum;
                // int groupnumber = stoi(selectnum);
                // string groupname;
                
                // cout << "Beat" << endl;
                // cout << BeatMatrix << endl;
                // cout << "Meet" << endl;
                // cout << MeetMatrix << endl;
                // cout << "Miss" << endl;
                // cout << MissMatrix << endl;
                
                int choice2;
                cin>>choice2;
                switch(choice2)
                {
                    case 1:
                    {
                        cout<<"============Beat Matrix=========="<<endl; 
                        cout<<"Avg AAR: "<<BeatMatrix[0]<<endl; 
                        cout<<"Std AAR: "<<BeatMatrix[1]<<endl;
                        cout<<"Avg CAAR: "<<BeatMatrix[2]<<endl; 
                        cout<<"Std CAAR: "<<BeatMatrix[3]<<endl;
                        break;
                    }    
                    case 2:
                    {
                        cout<<"============Meet Matrix=========="<<endl; 
                        cout<<"Avg AAR: "<<MeetMatrix[0]<<endl; 
                        cout<<"Std AAR: "<<MeetMatrix[1]<<endl;
                        cout<<"Avg CAAR: "<<MeetMatrix[2]<<endl; 
                        cout<<"Std CAAR: "<<MeetMatrix[3]<<endl; 
                        break;
                    }
                    case 3:
                    {
                       cout<<"============Miss Matrix=========="<<endl; 
                        cout<<"Avg AAR: "<<MissMatrix[0]<<endl; 
                        cout<<"Std AAR: "<<MissMatrix[1]<<endl;
                        cout<<"Avg CAAR: "<<MissMatrix[2]<<endl; 
                        cout<<"Std CAAR: "<<MissMatrix[3]<<endl; 
                        break;
                    }
                     
                }
                break;
            }
            case 4:
            {
                Vector beat_AvgCAAR, meet_AvgCAAR, miss_AvgCAAR; 
                beat_AvgCAAR = BeatMatrix[2]; 
                meet_AvgCAAR = MeetMatrix[2]; 
                miss_AvgCAAR = MissMatrix[2]; 
                gnuplot AvgCAAR_plot(beat_AvgCAAR, meet_AvgCAAR, miss_AvgCAAR, "CAAR_Avg"); 
                AvgCAAR_plot.Gnuplot();
                break;
            }
            case 5:
            {
                cout<<"Exit "<<endl; 
                break; 
            }
        }
    }
    return 0; 
    
}
