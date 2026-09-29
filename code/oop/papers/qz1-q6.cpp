#include <iostream>
using namespace std;
void fun(int &a, int b, int c[]) {
a += 2;
b += a;
c[0] += b;}
int main() {
int x = 3, y = 4;
int arr[] = {5, 6};
fun(x, y, arr);
cout<<x<<"  "<<y<<"  "<<arr[0];}
