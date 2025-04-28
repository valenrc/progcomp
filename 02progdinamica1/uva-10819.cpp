// UVa 10819 - trouble of 13-dots
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
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

vi price; vi fav;
int n,m;

int solve(int mt, int i, vvi& dp){
  if(i==n){
    if(mt <= 2000 && mt > m) return -1e9;  // se pasa del m y no hay refund 
    else return 0; // mt > 2000 o mt<=m
  }

  if(dp[mt][i] != -1) return dp[mt][i];

  int notpick = solve(mt, i+1, dp); // no elegir el item i

  int pick = -1e9;
  // si m + 200 > 2000 puedo gastar m+200 pues hay refund
  if((mt+price[i] <= m) || (m > 1800 && mt+price[i] <= m+200)){
    pick = fav[i] + solve(mt+price[i], i+1, dp); // elegir el item i
  }
  return dp[mt][i] = max(pick, notpick);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  while(cin >> m >> n &&  !cin.eof()){
    price.resize(n); fav.resize(n);

    forn(i,n){
      cin >> price[i] >> fav[i];
    }
    //print_container(fav);
    vvi dp(m+201, vi(n+1, -1));

    int res = solve(0,0,dp);
    cout << res << endl;
  }
  return 0;
}