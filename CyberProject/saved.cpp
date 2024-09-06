// Online C++ compiler to run C++ program online
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to check if a number is prime
bool isprime(uint32_t num) {
    if (num <= 1) return false;
    if (num == 2) return true;  // 2 is a prime number
    if (num % 2 == 0) return false; // Exclude even numbers greater than 2

    uint32_t limit = sqrt(num);
    for (uint32_t i = 3; i <= limit; i += 2)
    {
        if (num % i == 0) 
        {
            return false;
        }
    }
    return true;
}
// Function to generate a large random number
uint32_t generate_large_random() 
{
    return ((uint32_t)rand() << 31) | rand();
}
// Function to find the greatest coprime number less than phie
long long find_greatest_coprime(long long phie) 
{
    for (long long e = phie - 2; e > 1; e--) 
    {
        if (__gcd(e, phie) == 1) 
        { 
            return e;
        }
    }
    return 1; 
}
//this is for extended gcd calculation..............................................................
long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

// Function to find modular inverse using Extended Euclidean Algorithm
long long mod_inverse(long long a, long long m) {
  long long m0 = m;
  long long y = 0, x = 1;

  if (m == 1) return 0;

  while (a > 1) {
    long long q = a / m;
    long long t = m;

    m = a % m;
    a = t;
    t = y;

    y = x - q * y;
    x = t;
  }

  if (x < 0) x += m0;

  return x;
}

//Power and mod calculation 
long long int modpow(long long int base, long long int exp, long long int modulus)
{
  base %= modulus;                          
  
  long long int result = 1;                                                             
                                            
  while (exp > 0) {                         
    if (exp & 1) {                          
      result = (result * base) % modulus;   
     }
    base = (base * base) % modulus;         
    exp >>= 1;                               
  }
  return result;
}


int main()
{
    srand(time(0));
    uint16_t p, q;

    while (true) 
    {
        p = generate_large_random();
        if (isprime(p)) 
        {
            cout << "The prime number P is: " << p << endl;
            break;
        }
    }
    while (true) {
        q = generate_large_random();
        if (isprime(q)) {
            cout << "The prime number Q is: " << q << endl;
            break;
        }
    }
    // Calculating n and phie
    long long int n,phie,C;
    long long int e;                                                  //Private key
    n = p * q;
    phie = (p - 1) * (q - 1);
    cout << "Value of n: " << n << endl;
    cout << "Value of phie function: " << phie << endl;
    // Find coprime number
    e = find_greatest_coprime(phie);
    cout << "The E number is: " << e << endl;
    cout<<"Encryption Key [e,n]:"<< e <<" and "<< n <<endl;
    //Now public key is [e,n]
    //Now Calculte D decryption key
    // Private key (d stands for decrypt)
    // Find decryption key (d)
    long long  d = mod_inverse(e, phie);
    cout << "The decryption key [d,n]: " << d << " and " << n << endl;
    //Now the decryption key [d,n]
    //Now converting message[m] to ciphertext C = m^e mod n
    long long mess,check;
    cout<<endl;
    cout<<"Entre your message in number:";
    cin>>mess;
    C = modpow(mess,e,n);
    cout << "The ciphertext of message is"<< " = " << C <<endl;
    check = modpow(C,d,n);
    cout<<"The message is:"<<check;
    return 0;
}
