#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint

// Data structures
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

// Data types
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>  ii;
typedef pair<double, double> pdd;

typedef vector<int>     vi;
typedef vector<bool>    vb;
typedef vector<ll>     vll;
typedef vector<string>  vs;
typedef vector<vi>     vvi;
typedef vector<ii>     vii;

// Macros
#define forn(i,n)     for(int i=0; i<(int)(n); i++)
#define fordn(i,d,n)  for(int i=(int)(d); i<(int)(n); i++)
#define forall(i, c)  for(const auto& i : (c))
#define pb push_back

// Constants
const double PI = acos(-1.0);
const double EPS = 1e-9;

// Functions
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << endl;
}

///////////////////////
// UVA 524 - prime ring

void sieve(vb& prime){
  int n = (int)prime.size();
  prime[0] = prime[1] = false;
  
  for(int i=2; i*i <= n; i++){
    if(prime[i]){
      for(int j=i*i; j<n; j+=i){
        prime[j] = false;
      }
    }
  }
}

void print_primes(const vb& prime){
  for(int i=0; i<(int)prime.size(); i++){
    if(prime[i]){
      cout << i << " ";
    }
  }
  cout << endl;
}

void permutations(int n, vi& ring, vb& prime, vb& selected){
  if(!n){
    // print the ring
    forall(i, ring){
      if(i == ring.back()){
        cout << i << endl;
      }else{
        cout << i << " ";
      }
    }
    return;
  }

  for(int i=2; i<(int)(selected.size()); i++){
    if(!selected[i]){
      if(prime[ring.back() + i]){
        if(n==1 && !prime[i+1]){
          // el ultimo numero tambien debe cumplir la condicion con el primero
          continue;
        }
        ring.push_back(i);
        selected[i] = true;
        permutations(n-1, ring, prime, selected);
        ring.pop_back();
        selected[i] = false;
      }
    }
  }

}

int main(){
  // el numero primo mas grande a generar es el 15+16=31
  vb prime(32, true);
  sieve(prime);

  int n;
  int tc = 0;
  while(true){
    if(!(cin >> n)) break;
    if(tc != 0){
      cout << endl;
    }

    vi ring = {1};
    vb selected(n+1, false);
    selected[1] = true;

    cout << "Case " << ++tc << ":" << endl;
    permutations(n-1, ring, prime, selected);
  }

  return 0;
}