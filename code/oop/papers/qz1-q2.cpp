#include <iostream>
using namespace std;
int x = 5;
int fun(int x){
   static int s = 10;
   int y = 2;
   x += s;
   s += 3;
   y += x;
   return x + y + s;}
int main(){
   int y = 3;
   cout << fun(x) << " ";
   cout << fun(x) << " ";
   x += y;
   cout << x << " ";
   cout << fun(x);
   return 0;}
