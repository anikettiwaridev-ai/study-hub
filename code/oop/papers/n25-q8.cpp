#include <iostream>
using namespace std;
class MyClass{
private:
int i;
public:
MyClass(int num)
{i=num;}
void operator ++(int)
{cout<<"First";}
void operator ++(void)
{cout<<"second";}
};
int  main()
{MyClass myObj(10);
myObj++;
return 0;}
