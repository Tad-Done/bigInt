#ifndef LISTOFPRIME_H_INCLUDED
#define LISTOFPRIME_H_INCLUDED

unsigned intsqrt(unsigned num)
{
    unsigned tmp=num;
    unsigned len=0;
    for(;tmp!=0;len++){
        tmp>>=1;
    }
    tmp=num>>(len/2+1);
    for(;tmp*tmp<=num;tmp++);
    return tmp-1;
}

bool isPrime(unsigned num)
{
    if(num<2)return false;
    if(num==2)return true;
    if(num%2==0)return false;
    bool *numlist=new bool[num/2];
    for(unsigned i=0;i<num/2;i++)
        numlist[i]=true;
    for(unsigned i=0;i<num/2;i++){
        if(numlist[i]){
            for(unsigned j=3;j*(i*2+3)<=num;j+=2){
                numlist[j*(i*2+3)/2-1]=false;
            }
        }
    }
    bool result=numlist[num/2-1];
    delete []numlist;
    return result;
}

class listOfPrime{
private:
    struct node{
        unsigned prime,pow;
        node *next;

        node(unsigned p,unsigned m=1,node *n=NULL):prime(p),pow(m),next(n){}
    };
    node *head;
    unsigned num;

public:
    listOfPrime():num(0){head=new node(0,0);}
    listOfPrime(unsigned num):num(0){head=new node(0,0);primeFact(num);}
    ~listOfPrime(){clear();delete head;}

    void clear();
    void print()const;
    unsigned numOfPrime(){return num;}
    void addBoth(unsigned p,unsigned m=1);
    void addPrime(unsigned p);
    unsigned checkPow(unsigned p)const;
    void primeFact(unsigned num);
};

void listOfPrime::clear()
{
    node *t=head->next,*q;
    while(t!=NULL)
    {
        q=t->next;
        delete t;
        t=q;
    }
    head->next=NULL;
    num=0;
}

void listOfPrime::print()const
{
    node *t=head->next;
    for(;t!=NULL;t=t->next)
        cout<<t->prime<<'^'<<t->pow<<'\t';
    cout<<endl;
}

void listOfPrime::addBoth(unsigned p,unsigned m)
{
    node *tmp=new node(p,m,head->next);
    head->next=tmp;
    num++;
}

void listOfPrime::addPrime(unsigned p)
{
    node *t=head->next;
    if(num!=0&&t->prime==p){
        t->pow++;
    }
    else{
        addBoth(p);
    }
}

unsigned listOfPrime::checkPow(unsigned p)const
{
    node *t=head;
    for(;t->next!=NULL;t=t->next){
        if(t->prime==p){
            return t->pow;
        }
    }
    return 0;
}

void listOfPrime::primeFact(unsigned num)
{
    bool *numlist=new bool[num/2];
    for(unsigned i=0;i<num/2;i++)
        numlist[i]=true;
    for(unsigned i=0;i<num/2;i++){
        if(numlist[i]){
            for(unsigned j=3;j*(i*2+3)<=num;j+=2){
                numlist[j*(i*2+3)/2-1]=false;
            }
        }
    }
    clear();
    unsigned tmp=num;
    for(;tmp%2==0;tmp>>=1)
        addPrime(2);
    for(unsigned i=0;(i*2+3)<=tmp;i++){
        if(numlist[i]){
            while(tmp%(i*2+3)==0){
                tmp/=(i*2+3);
                addPrime(i*2+3);
            }
        }
    }
    delete []numlist;
}

#endif // LISTOFPRIME_H_INCLUDED
