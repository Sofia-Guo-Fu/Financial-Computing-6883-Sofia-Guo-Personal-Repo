#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstring>
#include "gnuplot.h"
using namespace std;

namespace fre{
    void gnuplot::Gnuplot()
    {   
        const char *tempDataFileBEAT = "Beat";
        const char *tempDataFileMEET = "Meet";
        const char *tempDataFileMISS = "Miss";
    
        // Create the x_axis
        vector<int> DATE;
        int N = datasize/2;
        for (int i = -N; i <= N; i++) {
            DATE.push_back(i);
        }
    
        // Configure gnuplot
        FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    
        if (gnuplotPipe) {
            // Set gnuplot commands
            fprintf(gnuplotPipe, "set grid\n");
            fprintf(gnuplotPipe, "set title '%s'\n", title);
            fprintf(gnuplotPipe, "set xlabel 'Announcement Date '\n");
            fprintf(gnuplotPipe, "set ylabel '%s'\n", yaxis);
            fprintf(gnuplotPipe, "set arrow from 0, graph(0,0) to 0, graph(1,1) nohead lc rgb 'red'\n");

    
            // Plot the data
            fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileBEAT, tempDataFileMEET, tempDataFileMISS);
            
            // Figure 1 - Beat_Group
            FILE* tempDataFile = fopen(tempDataFileBEAT,"w");
            for (int j = 0; j < datasize; j++) {
                fprintf(tempDataFile, "%d %lf\n", DATE[j], BEAT[j]);
            }
            
            fclose(tempDataFile);
        
            // Figure 2 - Meet_Group
            tempDataFile = fopen(tempDataFileMEET,"w");
            for (int k = 0; k < datasize; k++) {
                fprintf(tempDataFile, "%d %lf\n", DATE[k], MEET[k]);
            }
            
            fclose(tempDataFile);
        
            // Figure 3 - Miss_Group
            tempDataFile = fopen(tempDataFileMISS,"w");
            for (int m = 0; m < datasize; m++) {
                fprintf(tempDataFile, "%d %lf\n", DATE[m], MISS[m]);
            }
            
            fclose(tempDataFile);
            // Exit
            printf("Press ENTER to continue:");
            getchar();
        
            // Close the gnuplot pipe
            pclose(gnuplotPipe);
        } else {
            printf("Could not find gnuplotPipe.");
        }
    }
}
