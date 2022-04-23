#include<iostream>
using namespace std;
void swap(int & a, int & b){
    int c = a;
    a = b;
    b = c;
}
int main(){
    int a = 0;
    int b = 1;
    swap(a,b);
    cout << a << b;
}