#include <iostream>

using namespace std;

//Create a class called DefInt
class DefInt{
    private:
        double a,b;
        // a pointer to the funtion f
        double (*Fct)(double x);
    
    public:
        //Constructor: with parameters
        DefInt(double a_,double b_, double (*Fct_)(double x)):a(a_),b(b_), Fct(Fct_) {}
        
        //By Trapzoid
        double ByTrapzoid(int N)
        {
            double sum = 0;
            double h = (b-a)/N;
            double area;
            
            for (int k=1;k<=N;k++)
            {
                sum += Fct(a+(k-1)*h) + Fct(a+k*h);
            }
            area = h/2*sum;
            return area;
        }
        
        // By Simpson
        double BySimpon(int N)
        {
            double area;
            area = (b-a)/6 * (Fct(a) + 4 * Fct((a+b)/2) + Fct(b));
            return area;
        }
}; 


// f(x) function
double fx(double x)
{
    return x*x*x - x*x + 1;
}

//main function
int main()
{   
    double a = 1.0;
    double b = 2.0;
    int N = 1000;
    
    DefInt MyInt(a,b,fx);
    cout<<"Approximation by Trapzoid:"<<MyInt.ByTrapzoid(N)<<endl;
    cout<<"Approximation by Simpson:"<<MyInt.BySimpon(N)<<endl;
    return 0;
}

// My answer:
/*

Approximation by Trapzoid:2.41667
Approximation by Simpson:2.41667

*/