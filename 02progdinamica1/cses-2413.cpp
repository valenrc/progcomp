// CSES 2413 - counting towers
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

constexpr int MAX = 1000000;
constexpr int mod = 1000000007;
int lastcomputed = 1;

vector<vector<ull>> dp(MAX+1, vector<ull>(2, 0));

ull solve(int n){
  fordn(i,lastcomputed+1,n+1){ // empiezo por el ultimo n computado
    ull b1 = dp[i-1][1] + 2*dp[i-1][0];
    ull b2 = dp[i-1][0] + 4*dp[i-1][1];
    dp[i][0] = b1 % mod;
    dp[i][1] = b2 % mod;
  }
  lastcomputed = n;
  return (dp[n][0] + dp[n][1]) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  dp[1][0] = 1; // torres de altura 1 con dos bloques de ancho 1
  dp[1][1] = 1; // "" con un bloque de ancho 2

  int n; cin >> n;
  int t;
  forn(i,n){
    cin >> t;
    cout << solve(t) << "\n";
  }

  return 0;
}