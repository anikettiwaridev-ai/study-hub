#include <iostream>
#include <cstdio>
using namespace std;
class Test {
public:
   Test() {}
   Test(const Test& t)
   {cout << "OOPS programming"<<endl;}
   Test& operator=(const Test& t)
   {cout << "Hello World "<<endl;
      return *this;}};
int main(){
   Test t1, t2;
   t2 = t1;
   Test t3 = t1;
   Test T4(t1);
   getchar();
   return 0;}
