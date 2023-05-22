Evaluation of the impact of quarterly earnings report on stock price movement
-----------------------------------------------------------------------------------------------------
Project descriptions:
------------------------------------------------------------------
Part 1: Data downloading, washing and storing

* Use liburl to retrieve historical price data from eodhistoricaldata.com: A function retrieves the adjusted close prices for selected Russell 3000 stocks and IWV
(Russell 3000 ETF used as market benchmark) into memory
* Create a set of classes for Stock to handle EPS (earnings per share), estimate and price information. 
* The stocks and their corresponding price information is stored in a STL map with stock symbol as its keys. 
------------------------------------------------------------------------------------------------------------
Part 2: Sorting 

* Based on the 4th quarter of 2022 earnings announcement for Russell 3000 stocks, sort all the surprise% in ascending order, 
and split all the stocks into 3 groups with relatively equivalent numbers of stocks:

    i. Highest surprise group: Beat Estimate Group
    
    ii. Lowest surprise group: Miss Estimate Group
    
    iii. The rest stocks in between: Meet Estimate Group
    
* Define day “zero” for a stock as the day the earning is announced
-------------------------------------------------------------------------------------------------------------------------
Part 3: Bootstrapping and Calculation 
* Randomly selecting 80 stocks from each group, total 240 stocks
* Use libcurl lib to retrieve 2N+1 days of historical prices for Russell 3000 stocks and ETF ticker IWV (used as market benchmark) 
around the date of earning release. N is an integer which must be greater or equal to 60, will be entered by users. Users 
will be warned if there are not enough historical prices for 2N+1.

* For each stock calculate the daily returns Rit for N-1 days before the day 
“zero” and N days after, such as t = -60, -59,…-1, 0, 1,…, 59, 60:
Rit = (Price_t – Price_t-1)/ Price_t-1
Using adjusted daily closing price for your calculation
* Calculate the corresponding daily return R_mt for IWV for the same days
* Define abnormal returns as the difference ARit= R_it–R_mt.
* Calculate average daily abnormal returns for each group of stocks (with M 
stocks, M = 80 in our case) for all 2N reference days
* Cumulate the returns on the first T days to CAAR:
* Repeat steps a to g 40 times to create 40 samplings and then calculate 

        i. Average AAR and CAAR for 40 samplings for each group
        
        ii. Standard Deviation of AAR and CAAR for each group

Part 4: Visualization
* Generate a gnuplot chart show the averaged CAAR of all three groups and discuss 
the impact the earning releases on their stock prices
