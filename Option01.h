#pragma once

namespace fre {
	//pricing European option
	double PriceByCRR(double S0, double U, double D, double R, unsigned int N, double K);

	//computing call payoff
	double CallPayoff(double z, double K);
	
	// hw1 my code
	// Version 1: Factorial
	// First I create a factorial function
	double HW1Factorial(int n);
	// Then, I will write my own PriceByCRR Function
	double HW1PriceByCRR(double S0,double U, double D,double R,int N, double K); 
	
	
	// Version 2: 
	double HW1Function(int N, int n);
	double HW1V2PriceByCRR(double S0,double U, double D,double R,int N, double K);
	
}