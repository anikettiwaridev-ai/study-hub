#include<iostream>
using namespace std;
int fun(int x, int y) {
   if (y == 0) return 0;
   return (x + fun(x, y - 1));}
int main()
{int num=fun(3, 4);
cout<<num;}
