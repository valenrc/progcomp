// UVA 12524 - Arranging Heaps
// TO-DO: Da TLE! 
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

const int MAX = 1000; // max valor de n
const ll INF = numeric_limits<ll>::max()/2;
int n;

vll dist(MAX);
vll w(MAX);

vector<vector<ll>> cost(MAX, vll(MAX, 0));
vector<vector<ll>> dp(MAX, vll(MAX, -1));

ll solve(int i, int k){
  if(k==0){
    return (i==n) ? 0 : INF;
  }
  if(i==n) return INF;
  if((n-i) < k) return INF; // no hay suficientes mining points para alcanzar k heaps

  if(dp[i][k] != -1) return dp[i][k];
  
  // agrupo i...j en un heap
  // busco j que minimice el costo total
  ll res = numeric_limits<ll>::max();
  fordn(j, i, n){
    ll total_cost = 0;
    fordn(x, i, j){
      total_cost += cost[x][j];
    }
    total_cost += solve(j+1, k-1);
    res = min(res, total_cost);
  }

  return dp[i][k] = res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int k;
  while(cin >> n >> k){
    forn(i, n) cin >> dist[i] >> w[i];

    // precomputo cost[i][j] = w[i] * (dist[j] - dist[i])
    forn(i, n){
      fordn(j, i, n) cost[i][j] = w[i] * (dist[j] - dist[i]);
    }

    ll res = solve(0, k);

    cout << res << "\n";

    // llenar dp con -1
    forn(i, n) forn(j, n) dp[i][j] = -1;
  }

  return 0;
}