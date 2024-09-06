// C++ program to generate random numbers 
#include <cstdlib> 
#include <iostream> 
#include <time.h> 
using namespace std;
bool isprime(int random)
{
    int flag=0;
    for (int i =2;i<random ; i++)
    {
        if(random%i==0)
        {
          flag++;  
        }
        else
        {
        }
    }
    if(flag ==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    int p;
    srand(time(0)); 
 	p = rand();
 	cout<<endl;
 	for(int j =0;isprime(p)==false;j++)
 	{
 	    if(isprime(p)==false)
 	    {
 	        p=rand();
 	        isprime(p);
 	    }
 	    else
 	    {
 	        return true;
 	    } 
 	}
    cout<<"The prime number is :"<<p;
    return 0;
}

//Second part
// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
bool isprime(long num) {
    if (num <= 1) return false;
    for (long i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() 
{
    long phie,e;
    cout<<"Entre phie value:";
    cin>>phie;
    long j=phie;
    do {
        isprime(j);
        j--;
        e=j; 
    } while(isprime(j) ==false);
    cout<<"The coprime number is :"<<e;
    return 0;
}

//Best way to calculate Power and mod of number (power mod algorithm)
long long int modpow(long long int base, long long int exp, long long int modulus)
{
  base %= modulus;                          // Eliminate factors; keeps intermediate results smaller
  long long int result = 1;                 // Start with the multiplicative unit (a.k.a. one)
                                            // Throughout, we are calculating:
                                            // `(result*base^exp)%modulus`
  while (exp > 0) {                         // While the exponent has not been exhausted.
    if (exp & 1) {                          // If the exponent is odd
      result = (result * base) % modulus;   // Consume one application of the base, logically
                                            // (but not actually) reducing the exponent by one.
                                            // That is: result * base^exp == (result*base)*base^(exp-1)
    }
    base = (base * base) % modulus;         // The exponent is logically even. Apply B^(2n) == (B^2)^n.
    exp >>= 1;                              // The base is squared and the exponent is divided by 2 
  }
  return result;
}