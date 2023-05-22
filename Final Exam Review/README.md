A quick review of Financial Computing class

This folder "Final Exam Review" is a quick walk through of professor Song Tang's topics in the Financial Computing class of Spring 2023 semester.

I summarized 8 different versions of Option Pricing methods seen in his PPT:
------------------------------------------------------------------------------------------------------------------------------------------
* Version 1 is the simplest version of European call option pricing. 
* Version 2 added "function pointers" to compute different payoff functions
* Version 3 created our first class of BinomialTreeModel
* Version 4 further created another class called "OptionCalculation" to perform PriceByCRR
* Version 5 incorporates inheritance and polymorphism to gurantee the pricing for different European options
* Version 6 extends the pricing further to American options by defining a "PriceBySnell" function
* Version 7 creates a new class called "BinLattice" to display the prices of American options at each node
* Version 8 incorporates function templates to show both the PriceTree and StoppingTree of American Options.
---------------------------------------------------------------------------------------------------------------------------------------------
The rest of the topics covered are:

* Nonlinear Solver(Topic 8):  3 ways-- function pointers, virtual functions (inheritance + polymorphism), class templates --can be used to solve nonlinear equations.

Furthermore, we will use the method in V2(Virtual functions) to solve for the implied volatility of European call options as well as the Yield to Maturity of a Bond in V4 and V5 folders respectively. 

* Path Dependent Options (Topic 9): we use Monte Carlo method to price Arithmetic Asian Call Options. Topic in this folder includes: price and pricing error calculation, Option Greeks (Delta & Gamma), and Variance reduction. 
* Path Dependent Basket Options (Topic 10): an extension of Topic 9, in which we further use operator overloading to price Basket Options. 


