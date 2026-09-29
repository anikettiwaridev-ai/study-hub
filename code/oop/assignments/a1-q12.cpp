#include <iostream>
using namespace std;

int x = 10;

void fun(int x)
{
 static int s = 2;
 int y = x + s;
 s += x;
  ::x += y;
 cout << x << " " << y << " " << s << " " << ::x << endl;
}

int main()
{
  int x = 3;

 for (int i = 1; i <= 4; i++)
  {
       x += i;
       fun(x);
    }
  cout << x << " " << ::x << endl;

    return 0;
}
