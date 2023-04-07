// TestEuropeanOption.cpp
// Test program for the exact solutions of European options.
// (C) Datasim Component Technology BV 2003-2006
//

#include "EuropeanOption.hpp"
#include <iostream>

int main()
{
	const char * optType = NULL; 
	
	// Q1:  Call option on a stock
	EuropeanOption callOption;
	optType = callOption.GetOptType(); 
	cout<<"OptType: "<< *optType <<"\tCall option on a stock: " << callOption.Price() << endl;


	//Q2: Put price without dividend
	double U = 50.0; 
	double K = 50.0; 
	double T = 0.25;  // 3 monmths
	double r = 0.10;
	double sig = 0.30; 
	char OptionType = 'P'; 
	
	double q1 = 0.0; 
	
	EuropeanOption indexOption1(r,sig,K,T,U, q1, OptionType); 
	optType = indexOption1.GetOptType();
	cout<<"OptType: "<< *optType << "\tPut option on a stock: "<<indexOption1.Price()<<endl; 
	
	//Q3: Put price with dividends
	double q2 = 0.119793;
	// double q2 = 0.1184;
	
	EuropeanOption indexOption2(r,sig, K, T, U, q2, OptionType); 
	optType = indexOption2.GetOptType(); 
	cout<<"OptType: "<<*optType <<"\tPut option with dividend: "<<indexOption2.Price()<<endl; 
	
	
	// Put option on a stock index
	// EuropeanOption indexOption;
	// indexOption.optType = "P";
	// indexOption.U = 100.0;
	// indexOption.K = 95.0;
	// indexOption.T = 0.5;
	// indexOption.r = 0.10;
	// indexOption.sig = 0.20;

	// double q = 0.05;		// Dividend yield
	// indexOption.b = indexOption.r - q;

	// cout << "Put option on an index: " << indexOption.Price() << endl;
	// cout << "Delta on a put option: " << indexOption.Delta() << endl;

	return 0;
}


/*

OptType: C      Call option on a stock: 2.13293
OptType: P      Put option on a stock: 2.37561
OptType: P      Put option with dividend: 3.03039

*/