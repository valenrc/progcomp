// CSES 1653 - Elevator Rides
// Esta solucion da TLE O(3^n)
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <bitset>     // bitset
#include <limits>     // numeric_limits
#include <functional> // function
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
#define forall(i, c)  for(auto& i : (c))
#define pb push_back
// Functions
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << endl;
}

int nn, x;
vi sum(1<<20,0); // 2^n subsets
vi dp(1<<20,-1); // 2^n subsets

int solve(int bmask){
  if(bmask == 0){
    return 0;
  }
  if(dp[bmask] != -1){
    return dp[bmask];
  }

  int res = 1e9; // res = inf

  // generar los subsets de bm
  for(int s=(bmask-1)&bmask; ; s=(s-1)&bmask){
    int ss = sum[s ^ bmask]; // subset sum
    if(ss <= x){
      res = min(res, 1 + solve(s)); // 1 + subset sum
    }
    if(s == 0) break; // no hay mas subsets
  }

  return dp[bmask] = res;
  
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int n;
  cin >> n >> x;

  nn = (1 << n) - 1; // 1111...1 (n bits)
  
  vi w(n,0);
  forn(i,n) cin >> w[i];

  // precomputar la suma de los subsets
  for(int s=nn; s; s=(s-1)&nn){
    for(int i=n-1; i>=0; i--){
      if(s & (1 << i)){ // s.test(i) == 1
        sum[s] += w[n-1-i];
      }
    }
  }
  //print_container(sum);

  int bitmask = (1 << n) - 1; // 1111...1 (n bits)
  int res = solve(bitmask); // 1111...1 (n bits)
  cout << res << "\n";

  return 0;
}
