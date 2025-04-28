// CSES 1637 - removing digits
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <bitset>     // bitset
#include <cstdint>    // int, int64_t, uint, uint64_t+
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
// Constants
const double PI = acos(-1.0);
const double EPS = 1e-9;
// Functions
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << endl;
}

constexpr int MAX = 1000000;
constexpr int INF = numeric_limits<int>::max() - 1;  //int=int32_t

vector<vector<int>> dp;

int solve(int n, int k){
  if (n == 0) return 0;
  if (n == 1) return 1;
  if (n < 0) return INF;
  if (dp[n][k] != INF) return dp[n][k];

  int res = INF;
  forn(j, k){
    int d = (n / (int)(pow(10, j))) % 10; // iesimo digito de n
    if(d == 0) continue;
    //cout << "n: " << n << " d: " << d << " j: " << j << endl;
    res = min(res, solve(n-d, k));
  }
  
  dp[n][k] = res + 1;
  return dp[n][k];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  int cd = (int)(floor(log10(n) + 1)); // cantidad de digitos de n

  dp.resize(n+1, vector<int>(cd+1, INF));

  int r = solve(n, cd);
  
  cout << r << "\n";

  return 0;
}