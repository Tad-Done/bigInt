#include <iostream>

#include "bigInt.h"
#include "listOfPrime.h"

using namespace std;

/*
int Legendre(BigInt a,BigInt p)
{

}
*/

int main()
{
    BigInt a=(1<<30)-1,b=127871392;
    cout<<int(a)<<endl;
    listOfPrime list(27);
    list.print();
    return 0;
}
