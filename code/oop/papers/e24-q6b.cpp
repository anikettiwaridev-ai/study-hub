#include <iostream>
using namespace std;
int main(){
   int arr[5], n;
   cout<<"enter number of elements for first loop";
   cin>>n; //user enetred n=2 here.
   for (int i=0; i<n; i++)
   {arr[i]=i;}
   for (int i=0; i<n; i++)
   {cout<<"the values of first loop are"<<arr[i]<<endl;}
   cout<<"enter number of elements for secon loop";
   cin>>n; //user enetred n=7 here.
   for (int i=0; i<n; i++)
   {arr[i]=i;}
   for (int i=0; i<8; i++)
   {cout<<"the values of second loop are"<<arr[i]<<endl;}
   return 0;}
