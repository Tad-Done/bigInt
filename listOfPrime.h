#ifndef LISTOFPRIME_H_INCLUDED
#define LISTOFPRIME_H_INCLUDED


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

    class list_iterator{
    private:
        node *cur;

    public:
        void operator=(node *ptr){cur=ptr;}
        void operator++()
        {
            if(cur->next!=NULL)
                cur=cur->next;
        }
        unsigned getprime(){return cur->prime;}
        unsigned getpow(){return cur->pow;}
        bool isEnd(){return !cur->next;}
    };

public:
    listOfPrime():num(0){head=new node(0,0);}
    listOfPrime(unsigned num):num(0){head=new node(0,0);primeFact(num);}
    ~listOfPrime(){clear();delete head;}

    void clear();
    node *begin(){return head;}
    void print()const;
    unsigned numOfPrime(){return num;}
    void addBoth(unsigned p,unsigned m=1);
    void addPrime(unsigned p);
    unsigned checkPow(unsigned p)const;
    void primeFact(unsigned num);
    typedef list_iterator iterator;
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

/*int jacobiBetPrime()
{

}*/

int jacobi(unsigned a,unsigned p)
{
    if(a%p==0)return 0;
    a%=p;
    if(a==1)return 1;
    if(a==p-1){
        if(((p-1)/2)%2==1)return -1;
        else return 1;
    }
    if(a==2){
        if(((p*p-1)/8)%2==1)return -1;
        else return 1;
    }
    if(isPrime(a)){
        int tmp(1);
        if(((p-1)*(a-1)/4)%2==1)tmp=-1;
        return tmp*jacobi(p,a);
    }
    listOfPrime alist(a);
    listOfPrime::iterator itra;
    itra=alist.begin();
    int tmp=1;
    for(unsigned i=alist.numOfPrime();i!=0;i--){
        ++itra;
        if(itra.getpow()%2==1)
            tmp*=jacobi(itra.getprime(),p);
    }
    return tmp;
}

#endif // LISTOFPRIME_H_INCLUDED
