// UVa 10911 - Forming Quiz Teams
// no se entrega
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

constexpr int MAX = (1 << 16); // 2^16 = 65536

vi vx(17,0);
vi vy(17,0);
vector<double> dp(MAX, -1); // 2^16 combinaciones para visitados
int n;

// se puede precomputar esto en una matriz 
double distance(int i, int j){
  return hypot(vx[i] - vx[j], vy[i] - vy[j]); 
}

double solve(int visited){
  if(visited == (1 << (2*n)) - 1){ // 11...1
    return 0;
  }
  if(dp[visited] != -1){
    return dp[visited];
  }

  double res = __DBL_MAX__;
  forn(i,2*n){
    if(visited & (1 << i)){
      continue;
    }
    forn(j,2*n){
      if(i != j && !(visited & (1 << j))){
        res = min(res, distance(i,j) + solve(visited | (1 << i) | (1 << j)));
      }
    }
  }
  return dp[visited] = res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  string _;
  int test_case = 1;

  while(cin >> n && n){
    int v = 0; // visitados
    dp.assign(MAX, -1);
    forn(i,2*n){
      cin >> _ >> vx[i] >> vy[i];
    }

    double res = solve(v);

    cout << fixed << setprecision(2) << "Case " << test_case++ << ": " << res << "\n"; 
  }

  return 0;
}