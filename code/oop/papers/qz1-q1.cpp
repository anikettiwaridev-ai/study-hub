#include <iostream>
using namespace std;
int main() {
   int x = 2, y = 3, z = 4;
   z = ((x += 3, y *= 2), (z++, x + y),(x -= 2, y + z));
   cout << "x = " << x  << ", y = " << y  << ", z = " << z << endl;
   return 0;}
