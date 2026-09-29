#include <iostream>
using namespace std;
void test(int a, int b = 5, int c = 10){
   cout << "First";}
void test(int a, int b = 5){
   cout << "Second";}
void test(double a, int b = 5){
   cout << "Second";}
int main(){
   test(10,6);
   return 0;}
