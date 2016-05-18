#include <iostream>

#include "bigInt.h"
#include "listOfPrime.h"

using namespace std;

int main()
{
    /*
    int j=0;
    for(int i=2;i<=166;i++){
        unsigned a=unsigned(modOfPower(i,2,167));
        unsigned b=unsigned(modOfPower(i,83,167));
        if(a!=1&&b!=1){
            cout<<i<<':'<<'\t'<<a<<'\t'<<b<<endl;
            j++;
        }
    }
    cout<<j<<endl;
    */
    //listOfPrime al(166);
    //al.print();

    cout<<power(2,64)<<endl;
    return 0;
}
