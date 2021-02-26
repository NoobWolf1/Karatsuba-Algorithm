#include<iostream>
#include<string.h>
#include<vector>
#include<math.h>

using namespace std;

//to display the vector
void display(vector<int> x)
{ 
    for (int i = 0; i < x.size(); i++) 
    { 
        cout << x[i]; 
    }
    cout<<endl;
}

//to flip the vector
vector<int> flip(vector<int> x)
{
    vector<int> y;
    for(int i=x.size()-1;i>=0;i--)
    {
        y.push_back(x[i]);
    }
    return y;
}

//to initialize the vector of length l to zero
vector<int> initializeToZero(int l)
{
    vector<int> y(l,0);
    return y;
}

//to initialize the vector of length l to nine
vector<int> initializeToNine(int l)
{
    vector<int> y(l,9);
    return y;
}

//to provide padding to vector (changing the size of vector from x.size() to l by adding zeroes)
vector<int> padding(vector<int> x,int l)
{
    vector<int> y;
    y = flip(x);
    int i = l-y.size();
    while(i)
    {
        y.push_back(0);
        i--;
    }
    y = flip(y);
    return y;
}

//to split the vector of length 0....n-1 to l...r-1
vector<int> split(vector<int> x,int l,int r)
{
    vector<int> a;
    for(int i =l;i<r;i++)
    {
        a.push_back(x[i]);
    }
    return a;
}

//to convert string to vector
vector<int> makeBigInt(string str) 
{ 
    int x = str.size(), a = 0; 
    vector<int>nvm;

    while (a != x) 
    { 
        nvm.push_back(str[a] - '0'); 
        a++; 
    } 
    return nvm; 
}

//to calculate sum of two vectors
vector<int> sum(vector<int> x, vector<int> y)
{
    int carry = 0,sum;
    vector<int> sum_v;
    int lx = x.size(), ly = y.size();

    if(lx > ly)
    {
        y = padding(y,lx);

    }
    if(ly > lx)
    {
        x = padding(x,ly);
    }

    lx = x.size(), ly = y.size();

    x = flip(x);
    y = flip(y);

    for(int i = 0;i<lx;i++)
    {
        sum = (x[i] + y[i] + carry) % 10;
        carry = (x[i] + y[i] + carry) / 10;
        sum_v.push_back(sum);
    }
    if(carry != 0)
    {
        sum_v.push_back(carry);
    }

    return flip(sum_v);

}

//to calculate 9's Complement of a vector
vector<int> ninesComplement(vector<int> x,int l)
{
    vector<int> y = initializeToNine(l);
    x = padding(x,l);

    l--;
    while(l >-1)
    {
        y[l] = y[l] - x[l];
        l--;
    }
    return y;    
}

//to calculate the difference of two vectors ie., x-y
vector<int> subtract(vector<int> x, vector<int> y)
{
    
    //x - y
    //nines complement of positive number is same
    // does not work for x<y
    int len = max(x.size(),y.size());
    y = ninesComplement(y,len);
    vector<int> z,z1 = {1};
  
    z = sum(x,y);
    z = sum(z,z1);
    z = flip(z);
    
    z.pop_back();
    
    //to remove the redundant zeroes
    while(z[z.size()-1] == 0 && z.size()>1)
    z.pop_back();
    
    z = flip(z);
    return z;

}

//to multiply two vectors of length 1
vector<int> multiply(vector<int> x, vector<int> y)
{

    vector<int> z;
    int a = x[0], b = y[0],c;
    //cout<<endl<<"multiply("<<a<<","<<b<<")";

    c = a*b;
    string s = to_string(c);
    z = makeBigInt(s);

    //cout<<endl<<"Result of above operation was : ";
    //display(z); 
    return z;
}

//to find next nearest 2s power of l
int twosPower(int l)
{
    int x;
    x = log2(l);
    if(pow(2,x) == l)
    {
        return l ;
    }
    return pow(2,++x);
}

//karatsuba algorithm 
vector<int> karatsuba(vector<int> x, vector<int> y)
{
    //a,b,c,d are splitting vectors
    //res is the result vector
    vector<int> a,b,c,d;
    vector<int> res;

    //lx,ly initially contain sizes of input vectors x and y 
    int lx = x.size(), ly = y.size();
    //now lx and ly are containing closest power of 2 
    lx = twosPower(lx), ly = twosPower(ly);

    //padding x and y corresponding to lx and ly
    if(lx > ly)
    {
        y = padding(y,lx);
        x = padding(x,lx);
    }
    if(ly > lx)
    {
        x = padding(x,ly);
        y = padding(y,ly);
    }
    if(lx == ly)
    {
        x = padding(x,lx);
        y = padding(y,ly);
    }

    //recalculating lx and ly
    lx = x.size(), ly = y.size();

    //additional pointers for splitting
    int l1 = min(lx,ly);
    int l2 = l1/2;
    
    //base condition
    if(x.size() < 2 && y.size() < 2)
    {
        //multiplying unit length vectors as base condition
        //as this is a divide and conquer paradigm
        return multiply(x,y);
    }


    //splitting given numbers in form of x = (10^^n/2)*a + b and y = (10^^n/2)*c + d

    a = split(x,0,l2);
    b = split(x,l2,l1);
    c = split(y,0,l2);
    d = split(y,l2,l1);


    //in karatsuba algorithm we decrease the time complexity from O(n^^2) to O(n^^1.59)
    //here we need to find x*y = ((10^^n/2)*a + b) * ((10^^n/2)*c + d)
    // x*y = (10^^n)*ac + (10^^n/2)*(ad+bc) + bd
    //so now we will find ac,(ad+bc),bd recursively 
    //we also know that (a+b)*(c+d) = ac+ad+bc+bd
    //if we find ac, bd and (a+b)*(c+d) recurrsively we can find (ad+bc) as (a+b)*(c+d) - ac - bd 


    vector<int> ac = karatsuba(a,c);

    vector<int> bd = karatsuba(b,d);
    
    vector<int> abcd = karatsuba(sum(a,b),sum(c,d));

    //finding (ad+bc) as (a+b)*(c+d) - ac - bd
    abcd = subtract(abcd,sum(ac,bd));

    //x*y = 10^^n*ac + 10^^n/2*(ad+bc) + bd

    //setting ac = 10^^n*ac
    for(int i=0;i<x.size();i++) ac.push_back(0);

    //setting abcd = 10^^n/2*(ad+bc)
    for(int i=0;i<x.size()/2;i++) abcd.push_back(0);

    //final x*y
	res = sum(ac,sum(abcd,bd));

    //removing redundant zeroes from result
    res = flip(res);
    while(res[res.size()-1]==0 && res.size()>1)
    res.pop_back();
    res = flip(res);


    return res;
}



int main()
{
    //for test we will have
    // x = 3141592653589793238462643383279502884197169399375105820974944592
    // y = 2718281828459045235360287471352662497757247093699959574966967627
    // correct answer will be 
    //x*y = 8539734222673567065463550869546574495034888535765114961879601127067743044893204848617875072216249073013374895871952806582723184
    
    string x,y;
    vector<int> res; 
    
    cout<<"Enter the first number: ";
    cin>>x;
    cout<<"\nEnter the second number:";
    cin>>y;
    vector<int> x1=makeBigInt(x),y1=makeBigInt(y);

    res = karatsuba(x1,y1);    

    cout<<"\nThe product is : ";
    display(res);

    return 0;
    
}
