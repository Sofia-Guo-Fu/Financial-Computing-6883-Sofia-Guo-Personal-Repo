#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

namespace fre{
    class gnuplot {
        private:
            vector<double> BEAT;
            vector<double> MEET;
            vector<double> MISS;
            int datasize;
            char title[20];
            char yaxis[20];

        public:
            gnuplot (const vector<double>& BEAT_, const vector<double>& MEET_, const vector<double>& MISS_, const char* content){
                BEAT = BEAT_;
                MEET = MEET_;
                MISS = MISS_;
                datasize = BEAT_.size();
                strcpy(title, content);
                strcat(title, " for 3 groups");
                strcpy(yaxis, content);
                strcat(yaxis, "(%)");

            }
            vector<double> GetDataBEAT(){return BEAT;}
            vector<double> GetDataMEET(){return MEET;}
            vector<double> GetDataMISS(){return MISS;}
            
            ~gnuplot(){}
            void Gnuplot();
    };
}