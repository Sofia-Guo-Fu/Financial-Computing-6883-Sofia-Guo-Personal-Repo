// EuropeanOption2.hpp
//
// Class that represents  solutions to European options. This is
// an implementation using basic C++ syntax only. It has been 
// written for pedagogical reasons
//
// (C) Datasim Component Technology BV 2003-2006
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp


#include <string>
using namespace std;

class EuropeanOption
{
	
	private:
	
		// Make function n() and N() as private functions 
		// Gaussian functions
		double n(double x) const;
		double N(double x) const;
		
		//1. Move data into private sections
		double r;		// Interest rate
		double sig;		// Volatility
		double K;		// Strike price
		double T;		// Expiry date
		double U;		// Current underlying price (e.g. stock, forward)
		double b;		// Cost of carry
		
		//string optType; // Option name (call, put)
		// string unam; // Name of underlying asset 
		
		// 3. Use char point and dynamic allocation to replace the STL string, optType
		const char *optType = new char; // Option name (call, put)
		
	
	public:				// For TEST purposes only
		
		// 2. Remove inint() and copy() functionsxz, commented them out 
		// void init();	// Initialise all default values
		// void copy(const EuropeanOption& o2);
	
		// 'Kernel' functions for option calculations
		double CallPrice() const;
		double PutPrice() const;
		double CallDelta() const;
		double PutDelta() const;
		double CallGamma() const;
		double PutGamma() const;
		double CallVega() const;
		double PutVega() const;
	

	public:	// Public functions
		EuropeanOption();							// Default call option
		EuropeanOption(double r_, double sig_, double K_, double T_, double U_, double q_, const char & optType_); // construnctor with parameters
		EuropeanOption(const EuropeanOption& option2);	// Copy constructor
		
		// 3. Use char point and dynamic allocation to replace the STL string, optType
		EuropeanOption (const char& optionType);	// Create option type
		// 3. Make sure no memory leak 
		virtual ~EuropeanOption()
		{
			delete optType; 
			optType = NULL; 
		}; 
	
		EuropeanOption& operator = (const EuropeanOption& option2);
	
		// Functions that calculate option price and sensitivities
		double Price() const;
		double Delta() const;
	
		// Modifier functions
		void toggle();		// Change option type (C/P, P/C)
		
		// 5. Create a member function GetOptType() to get the optType in main() function.
		const char * GetOptType()
		{
			return optType; 
		}


};

#endif
