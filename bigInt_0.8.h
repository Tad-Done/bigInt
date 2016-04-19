#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include<iostream>

using namespace std;

const unsigned maxLength(400);

class BigInt{
    friend ostream &operator<<(ostream &os,const BigInt &obj);
    friend BigInt operator+(const BigInt&,const BigInt&);
    friend BigInt operator-(const BigInt&,const BigInt&);
    friend BigInt operator*(const BigInt&,const BigInt&);
    friend BigInt operator/(const BigInt&,const BigInt&);
    friend BigInt operator%(const BigInt&,const BigInt&);
    friend bool operator<(const BigInt&,const BigInt&);
    friend bool operator>(const BigInt&,const BigInt&);
    friend bool operator<=(const BigInt&,const BigInt&);
    friend bool operator>=(const BigInt&,const BigInt&);
    friend bool operator==(const BigInt&,const BigInt&);
    friend BigInt power(const BigInt&,unsigned m);
    friend BigInt modOfPower(const BigInt&,unsigned m,const BigInt&);
    friend int operator int(const BigInt&);

private:
    char num[maxLength];
    unsigned length;

    void clr();
    unsigned compare(const BigInt &other)const;
    BigInt shl_n(unsigned bit)const;
    void shl(unsigned bit);
    BigInt multionenum(unsigned num)const;

public:
    BigInt(unsigned n=0);
    BigInt(const BigInt &other);
    BigInt &operator=(const BigInt &other);
    BigInt power(unsigned n);
    BigInt modOfPower(unsigned m,const BigInt &n);
    unsigned cToU();
};

void BigInt::clr()
{
    length=0;
    for(unsigned i=0;i<maxLength;i++)num[i]='0';
}

BigInt BigInt::multionenum(unsigned n)const
{
    BigInt result;
    unsigned digi,carry=0;
    for(unsigned i=0;i<length;i++){
        digi=(this->num[i]-'0')*n+carry;
        result.num[i]='0'+digi%10;
        carry=digi/10;
    }
    result.length=length;
    if(carry>0){
        result.num[length]='0'+carry;
        result.length++;
    }
    return result;
}

BigInt BigInt::shl_n(unsigned bit=1)const
{
    BigInt result;
    if(length!=0){
        for(unsigned i=length;i!=0;i--)
            result.num[i-1+bit]=num[i-1];
        for(unsigned i=0;i<bit;i++)
            result.num[i]='0';
        result.length=length+bit;
    }
    return result;
}

void BigInt::shl(unsigned bit=1)
{
    if(length!=0){
        for(unsigned i=length;i!=0;i--)
            num[i-1+bit]=num[i-1];
        for(unsigned i=0;i<bit;i++)
            num[i]='0';
        length+=bit;
    }
}

unsigned BigInt::cToU()
{
    unsigned result(0);
    if(*this<1<<13){
        for(unsigned i=length;i!=0;i--){
            result*=10;
            result+=num[i-1]-'0';
        }
    }
    return result;
}

BigInt::BigInt(unsigned n)
{
    clr();
    unsigned digi;
    for(unsigned i=0;n>0;i++){
        digi=n%10;
        num[i]='0'+digi;
        n/=10;
        length++;
    }
}

BigInt::BigInt(const BigInt &other)
{
    length=other.length;
    for(unsigned i=0;i<length;i++)num[i]=other.num[i];
}

BigInt &BigInt::operator=(const BigInt &other)
{
    this->clr();
    length=other.length;
    for(unsigned i=0;i<length;i++)num[i]=other.num[i];
    return *this;
}

BigInt BigInt::power(unsigned n)
{
    BigInt ans=1;
    for(unsigned i=0;i<n;i++){
        ans=ans*(*this);
    }
    return ans;
}

unsigned BigInt::compare(const BigInt &other)const
{
    if(this->length<other.length)return 1;
    else if(this->length>other.length)return 2;
    else{
        for(unsigned i=this->length;i!=0;i--){
            if(this->num[i-1]<other.num[i-1])return 1;
            else if(this->num[i-1]>other.num[i-1])return 2;
        }
        return 0;
    }
}

bool operator<(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==1)return true;
    else return false;
}

bool operator>(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==2)return true;
    else return false;
}

bool operator<=(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)!=2)return true;
    else return false;
}

bool operator>=(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)!=1)return true;
    else return false;
}

bool operator==(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==0)return true;
    else return false;
}

BigInt operator+(const BigInt &n1,const BigInt &n2)
{
    BigInt ans(0);
    ans.length=(n1.length>n2.length)?n1.length:n2.length;
    unsigned digi,carry=0;
    for(unsigned i=0;i<ans.length;i++){
        digi=n1.num[i]-'0'+n2.num[i]-'0'+carry;
        ans.num[i]='0'+digi%10;
        carry=digi/10;
    }
    if(carry>0){
        ans.num[ans.length]='1';
        ans.length++;
    }
    return ans;
}

BigInt operator-(const BigInt &n1,const BigInt &n2)
{
    BigInt ans(0);
    if(n1<=n2)return ans;
    else{
        ans.length=n1.length;
        unsigned digi,borrow=0;
        for(unsigned i=0;i<ans.length;i++){
            digi=10+(n1.num[i]-n2.num[i])-borrow;
            ans.num[i]='0'+digi%10;
            borrow=(digi/10)^1;
        }
        while(ans.num[ans.length-1]=='0'){
            ans.length--;
        }
        return ans;
    }
}

BigInt operator*(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    for(unsigned i=n2.length;i!=0;i--){
        ans=ans+n1.multionenum(n2.num[i-1]-'0');
        if(i!=1)
            ans.shl(1);
    }
    return ans;
}

BigInt operator/(const BigInt &n1,const BigInt &n2)
{
    BigInt ans,tmp;
    if(n1<n2)return ans;
    else{
        for(unsigned i=n1.length;i!=0;i--){
            tmp=tmp.shl_n(1)+(n1.num[i-1]-'0');
            unsigned d=0;
            while(tmp>=n2){
                tmp=tmp-n2;
                d++;
            }
            ans.num[i-1]='0'+d;
            if(ans.length<i&&d!=0)ans.length=i;
        }
        return ans;
    }
}

BigInt operator%(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    for(unsigned i=n1.length;i!=0;i--){
        ans.shl(1);
        ans=ans+n1.num[i-1]-'0';
        while(ans>=n2){
            ans=ans-n2;
        }
    }
    return ans;
}

BigInt BigInt::modOfPower(unsigned m,const BigInt &n) //a^m==p(mod n)
{
    BigInt t(*this),r=1;
    for(unsigned i=32;i!=0;i--){
        if((m&1)!=0){
            r=(r*t)%n;
            t=t.power(2)%n;
        }
        else{
            t=t.power(2)%n;
        }
        m=m>>1;
        if(m==0)break;
    }
    return r;
}

ostream &operator<<(ostream &os,const BigInt &obj)
{
    if(obj.length==0)os<<'0';
    else{
        for(unsigned i=obj.length;i!=0;i--){
            os<<obj.num[i-1];
        }
    }
    return os;
}

int operator int(const BigInt &n)
{
    int result(0);
    if(n<1<<30){
        for(unsigned i=n.length;i!=0;i--){
            result*=10;
            result+=n.num[i-1]-'0';
        }
        if()
    }
    return result;
}

BigInt power(const BigInt &obj,unsigned m)
{
    BigInt ans=1;
    for(unsigned i=0;i<m;i++){
        ans=ans*obj;
    }
    return ans;
}

BigInt modOfPower(const BigInt &obj,unsigned m,const BigInt &n)
{
    BigInt t(obj),r=1;
    for(unsigned i=32;i!=0;i--){
        if((m&1)!=0){
            r=(r*t)%n;
            t=t.power(2)%n;
        }
        else{
            t=t.power(2)%n;
        }
        m=m>>1;
        if(m==0)break;
    }
    return r;
}

#endif // BIGINT_H_INCLUDED
