#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include<iostream>

using namespace std;

const unsigned maxLength(100);

class BigInt{
    friend ostream &operator<<(ostream &os,const BigInt &obj);
    friend BigInt operator+(const BigInt&,const BigInt&);
    friend BigInt unsPlus(const BigInt&,const BigInt&);
    friend BigInt operator-(const BigInt&,const BigInt&);
    friend BigInt unsMinus(const BigInt&,const BigInt&);
    friend BigInt operator*(const BigInt&,const BigInt&);
    friend BigInt operator/(const BigInt&,const BigInt&);
    friend BigInt operator%(const BigInt&,const BigInt&);
    friend bool operator<(const BigInt&,const BigInt&);
    friend bool operator>(const BigInt&,const BigInt&);
    friend bool operator<=(const BigInt&,const BigInt&);
    friend bool operator>=(const BigInt&,const BigInt&);
    friend bool operator==(const BigInt&,const BigInt&);
    friend bool operator!=(const BigInt&,const BigInt&);
    friend BigInt power(const BigInt&,unsigned m);
    friend BigInt modOfPower(const BigInt&,unsigned m,const BigInt&);
    friend BigInt abs(const BigInt&);

private:
    char num[maxLength];
    unsigned length;
    bool sig;

    void clr();
    int compare(const BigInt &other)const;
    BigInt shl_n(unsigned bit)const;
    void shl(unsigned bit);
    BigInt multionenum(unsigned num)const;
    BigInt nega()const;
    bool isZero()const{return (length==0);}

public:
    BigInt(unsigned n=0);
    BigInt(int n);
    BigInt(const BigInt &other);
    BigInt &operator=(const BigInt &other);
    BigInt power(unsigned n);
    BigInt modOfPower(unsigned m,BigInt n);
    BigInt operator-()const;
    explicit operator int()const;
    explicit operator unsigned()const;
};

void BigInt::clr()
{
    sig=true;
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

BigInt BigInt::nega()const
{
    BigInt ans(*this);
    if(this->isZero())return ans;
    else
        ans.sig=!ans.sig;
    return ans;
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

BigInt::operator unsigned()const
{
    unsigned result(0);
    if(abs(*this)<1<<30){
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

BigInt::BigInt(int n)
{
    clr();
    unsigned digi;
    sig=(n>=0)?true:false;
    if(n<0)n*=-1;
    for(unsigned i=0;n>0;i++){
        digi=n%10;
        num[i]='0'+digi;
        n/=10;
        length++;
    }
}


BigInt::BigInt(const BigInt &other)
{
    clr();
    sig=other.sig;
    length=other.length;
    for(unsigned i=0;i<length;i++)num[i]=other.num[i];
}

BigInt &BigInt::operator=(const BigInt &other)
{
    this->clr();
    sig=other.sig;
    length=other.length;
    for(unsigned i=0;i<length;i++)num[i]=other.num[i];
    return *this;
}

BigInt BigInt::power(unsigned n)
{
    BigInt ans=1;
    if(!sig)
        ans.sig=(n%2==0)?true:false;
    for(unsigned i=0;i<n;i++){
        ans=ans*(*this);
    }
    return ans;
}

int BigInt::compare(const BigInt &other)const
{
    if(this->sig&&!other.sig)return 1;
    else if(!this->sig&&other.sig)return -1;
    else if(this->sig&&other.sig){
        if(this->length<other.length)return -1;
        else if(this->length>other.length)return 1;
        else{
            for(unsigned i=this->length;i!=0;i--){
                if(this->num[i-1]<other.num[i-1])return -1;
                else if(this->num[i-1]>other.num[i-1])return 1;
            }
            return 0;
        }
    }
    else{
        if(this->length<other.length)return 1;
        else if(this->length>other.length)return -1;
        else{
            for(unsigned i=this->length;i!=0;i--){
                if(this->num[i-1]<other.num[i-1])return 1;
                else if(this->num[i-1]>other.num[i-1])return -1;
            }
            return 0;
        }
    }
}

bool operator<(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==-1)return true;
    else return false;
}

bool operator>(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==1)return true;
    else return false;
}

bool operator<=(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)!=1)return true;
    else return false;
}

bool operator>=(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)!=-1)return true;
    else return false;
}

bool operator==(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)==0)return true;
    else return false;
}

bool operator!=(const BigInt &n1,const BigInt &n2)
{
    if(n1.compare(n2)!=0)return true;
    else return false;
}

BigInt abs(const BigInt &n)
{
    BigInt ans(n);
    ans.sig=true;
    return ans;
}

BigInt unsPlus(const BigInt &n1,const BigInt &n2)
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

BigInt unsMinus(const BigInt &n1,const BigInt &n2)
{
    BigInt ans(0);
    int com=n1.compare(n2);
    if(com==0)return ans;
    else if(com==-1)return unsMinus(n2,n1);
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

BigInt operator+(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    if(n1.sig^n2.sig){
        ans=unsMinus(abs(n1),abs(n2));
        if(n1<n2.nega())ans.sig=false;
        else ans.sig=true;
    }
    else{
        ans=unsPlus(n1,n2);
        ans.sig=n1.sig;
    }
    return ans;
}

BigInt operator-(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    ans=n1+n2.nega();
    return ans;
}

BigInt operator*(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    for(unsigned i=n2.length;i!=0;i--){
        ans=ans+n1.multionenum(n2.num[i-1]-'0');
        if(i!=1)
            ans.shl(1);
    }
    ans.sig=!(n1.sig^n2.sig);
    return ans;
}

BigInt operator/(const BigInt &n1,const BigInt &n2)
{
    BigInt ans,tmp;
    if(abs(n1)<abs(n2))return ans;
    else{
        for(unsigned i=n1.length;i!=0;i--){
            tmp=tmp.shl_n(1)+(n1.num[i-1]-'0');
            unsigned d=0;
            while(tmp>=abs(n2)){
                tmp=tmp-abs(n2);
                d++;
            }
            ans.num[i-1]='0'+d;
            if(ans.length<i&&d!=0)ans.length=i;
        }
        ans.sig=!(n1.sig^n2.sig);
        return ans;
    }
}

BigInt operator%(const BigInt &n1,const BigInt &n2)
{
    BigInt ans;
    for(unsigned i=n1.length;i!=0;i--){
        ans.shl(1);
        ans=ans+n1.num[i-1]-'0';
        while(ans>=abs(n2)){
            ans=ans-abs(n2);
        }
    }
    if(n1.sig)
        return ans;
    else
    {
        ans=ans-abs(n2);
        ans=abs(ans);
        return ans;
    }
}

BigInt BigInt::modOfPower(unsigned m,BigInt n) //a^m==p(mod n)
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
        if(!obj.sig)os<<'-';
        for(unsigned i=obj.length;i!=0;i--){
            os<<obj.num[i-1];
        }
    }
    return os;
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

BigInt BigInt::operator-()const
{
    BigInt ans=this->nega();
    return ans;
}

BigInt::operator int()const
{
    int result(0);
    if(abs(*this)<1<<30){
        for(unsigned i=length;i!=0;i--){
            result*=10;
            result+=num[i-1]-'0';
        }
    }
    if(!sig)
        result*=-1;
    return result;
}

BigInt gcd(const BigInt &a,const BigInt &b)
{
    if(a!=0&&b!=0){
        BigInt r=a%b,ta=a,tb=b;
        while(r!=0){
            ta=tb;
            tb=r;
            r=ta%tb;
        }
        return tb;
    }
    return 0;
}

BigInt mod_inv(const BigInt &a,const BigInt &b)
{
    if(a!=0&&b!=0){
        BigInt ta(a),tb(b),r=a%b,s=0,os=1,t=1,ot=0,q=a/b,tmp;
        while(r!=0){
            tmp=s;
            s=os-q*s;
            os=tmp;
            tmp=t;
            t=ot-q*t;
            ot=tmp;
            ta=tb;tb=r;
            r=ta%tb;
            q=ta/tb;
            //cout<<s<<'\t'<<t<<endl;
        }
        if(s<0)
            s=(s+b)%b;
        return s;
    }
    return 0;
}



#endif // BIGINT_H_INCLUDED
