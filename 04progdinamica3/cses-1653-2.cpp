// CSES 1653 - Elevator Rides
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

ll x;
vi sum(1<<20,0); // 2^n subsets

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int n;
  cin >> n >> x;
  
  vll w(n,0);
  forn(i,n) cin >> w[i];
  
  // dp[bmask] = {min_rides, min(last_ride)}
  vector< pair<int,ll> > dp(1<<n, {n+1, 0});
  // caso base dp[0] = {0, 0}
  dp[0].first = 1;
  dp[0].second = 0LL;

  // dp bottom-up
  for(int bmask=0; bmask < (1<<n); bmask++){
    if(dp[bmask].first > n) continue;

    forn(i,n){
      if(bmask & (1<<i)) continue; // si ya esta seteado ignorar
      
      int new_mask = bmask | (1<<i); // bmask.set(i)
      ll w_new = w[i];

      // ver si se puede agregar a w[i] al ascensor
      if(dp[bmask].second + w_new <= x){
        pair<int,ll> add_i = {dp[bmask].first, dp[bmask].second + w_new};
        
        // actualizar dp[new_mask] si es mejor
        dp[new_mask] = min(dp[new_mask], add_i);
      }else{
        // si no, hacer otro ride
        pair<int,ll> add_i = {dp[bmask].first + 1, w_new};
        dp[new_mask] = min(dp[new_mask], add_i);
      }
    }
  }

  cout << dp[(1<<n)-1].first << "\n";

  return 0;
}
