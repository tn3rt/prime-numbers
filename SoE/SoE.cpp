#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const int limit = 1000000000;
const std::vector<int> r {23,29,31,37,41,43,47,53, 59,61,67,71,73,79,83, //positions + 19
                          89,97,101,103,107,109,113,121,127, 131,137,139,
                          143,149,151,157,163,167,169,173,179,181,187,191,193, 
                          197,199,209,211,221,223,227,229};

int main()
{
// an array of length 11 times 13 times 17 times 19 = 46189 wheels initialized
// so that it doesn't contain multiples of the large wheel primes
// for n where n ← 210 × w + x where w ∈ {0,...46189}, x in r: // already
//    if (n mod cp) not equal to 0 where cp ∈ {11,13,17,19}: // no 2,3,5,7
//        mstr(n) ← true else mstr(n) ← false                // factors
  std::vector<bool> mstr(limit);
  int n;
  for (int w=0; w <= 46189; ++w) {
    for (auto x = begin(r); x != end(r); ++x) {
      n = 210*w + *x;
      if (n % 11 != 0 && n % 13 != 0 && n % 17 != 0 && n % 19 != 0)
        mstr[n]=true;
      else
        mstr[n]=false; 
    }
  }

// Initialize the sieve as an array of the smaller wheels with
// enough wheels to include the representation for limit
// for n where n ← 210 × w + x, w ∈ {0,...(limit - 19) ÷ 210}, x in r:
//    sieve(n) ← mstr(n mod (210 × 46189))    // init pre-culled primes.
  std::vector<bool> sieve(limit+1000);
  for (int w=0; w <= (limit-19)/210; ++w) {
    for (auto x = begin(r); x != end(r); ++x) {
      n = 210*w + *x;
      sieve[n] = mstr[(n % (210*46189))];
    }
  }

// Eliminate composites by sieving, only for those occurrences on the
// wheel using wheel factorization version of the Sieve of Eratosthenes
// for n² ≤ limit when n ← 210 × k + x where k ∈ {0..}, x in r
//    if sieve(n):
//        // n is prime, cull its multiples
//        s ← n² - n × (x - 23)     // zero'th modulo cull start position
//        while c0 ≤ limit when c0 ← s + n × m where m in r:
//            c0d ← (c0 - 23) ÷ 210, cm ← (c0 - 23) mod 210 + 23 //means cm in r
//            while c ≤ limit for c ← 210 × (c0d + n × j) + cm
//                    where j ∈ {0,...}:
//                sieve(c) ← false       // cull composites of this prime  
  int s, c, c0, c0d, cm, j;
  for ( auto x = begin(r); x != end(r); ++x) {
    for ( int k=0; (n=210*k + (*x)) <= sqrt(limit); ++k){
      if (sieve[n]) {
        s = n*n - n*((*x)-23);
        for ( auto m = begin(r); (c0=s+n*(*m)) <= limit &&  m != end(r); ++m) {
	  c0d = (c0-23)/210;
	  cm  = (c0-23)%210 + 23;
	  for ( int j=0; (c=210*(c0d+n*j)+cm) <= limit; ++j) {
	    sieve[c] = false;
          }
        } 
      } 
    } 
  } 

// output 2, 3, 5, 7, 11, 13, 17, 19,
// for n ≤ limit when n ← 210 × k + x where k ∈ {0..}, x in r:
//     if sieve(n): output n  
  std::cout << "2\n3\n5\n7\n11\n13\n17\n19\n";
  for ( auto x = begin(r); x != end(r); ++x) {
    for ( int k = 0; (n=210*k + (*x)) <= limit; ++k) {
      n=210*k + (*x);
      if (sieve[n]);
	std::cout << n << std::endl;
    }
  }
  std::cout << std::endl;

  return 0;
}
