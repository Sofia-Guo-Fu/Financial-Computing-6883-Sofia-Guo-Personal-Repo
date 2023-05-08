#include <iostream>
using namespace std;

class A
{
protected:
    int a;
public:
    A(int a_)
    {
        a = a_;
        cout << "class A Constructor with Parameter" << endl;
    }
    //virtual ~A()
    ~A()
    {
        cout << "class A Destructor" << endl;
    }
};

class B : public A
{
private:
    int b;
public:
    B(int a_, int b_) : A(a_), b(b_)
    {
        cout << "class B Constructor with Parameter" << endl;
    }
    ~B()
    {
        cout << "class B Destructor" << endl;
    }
};

void test1()
{
    A* ptrA = new B(1, 2); // for polymorphism
    delete ptrA;
    ptrA = NULL;

}
void test2()
{
    B* ptrB = new B(1, 2);
    delete ptrB;
    ptrB = NULL;
}
int main()
{
    test1();
    cout << "test1 is done" << endl;
    test2();
    cout << "test2 is done" << endl;
    return 0;
}

/* Virtual destructor
class A Constructor with Parameter
class B Constructor with Parameter
class B Destructor //
class A Destructor
test1 is done
class A Constructor with Parameter
class B Constructor with Parameter
class B Destructor
class A Destructor
test2 is done

*/

/* Not virtual destructor
class A Constructor with Parameter
class B Constructor with Parameter
class A Destructor  
test1 is done
class A Constructor with Parameter
class B Constructor with Parameter
class B Destructor
class A Destructor
test2 is done

*/