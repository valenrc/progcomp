// Wormholes
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
  cout << "\n";
}

constexpr int INF = numeric_limits<int>::max() / 2;
int n, m;

struct Edge{
  int u, v, w;
};

bool neg_cycle(const vector<Edge>& g){
  vi d(n, 0);
  vi p(n, -1);
  int x = -1;

  forn(i, n){
    x = -1;

    forall(e, g){
      if(d[e.u] + e.w < d[e.v]){
        d[e.v] = max(-INF, d[e.u] + e.w);
        p[e.v] = e.u;
        x = e.v;
      }
    }
  }

  return x != -1;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; cin >> tt;
  forn(i, tt){
    cin >> n >> m;
    vector<Edge> wh;

    forn(j, m){
      Edge e;
      cin >> e.u >> e.v >> e.w;
      wh.pb(e);
    }

    bool negative_cycle = neg_cycle(wh);

    cout << (negative_cycle ? "possible" : "not possible") << "\n";
  }

  return 0;
}