// CSES 1140 - Project
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

constexpr int MAX = 2*100000;
struct proy {
  int a,b;
  ll p;
}; // 16 bytes

bool comp_a(const proy& p1, const proy& p2) {
  return p1.a < p2.a;
}

vector<ll> dp(MAX, -1);

ll solve(int i, int n, vector<proy>& v, vi& s){
  if (i >= n) return 0;
  if (dp[i] != -1) return dp[i];
  ll skip = solve(i+1, n, v, s);

  // busco min(j) tal que a_j > b_i
  // lower_bund usa binary search O(log n)
  vi::iterator jj = lower_bound(s.begin(), s.end(), v[i].b+1);
  int j;
  if(jj == s.end()) j=n; else j = (int)(jj - s.begin());

  ll take = v[i].p + solve(j, n, v, s);

  return dp[i] = max(skip, take);
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  vector<proy> v(n); // 3.2 mb como maximo
  forn(i,n){
    cin >> v[i].a >> v[i].b >> v[i].p;
  }

  // ordeno por dia de inicio
  sort(v.begin(), v.end(), comp_a);

  vi start(n);
  forn(i,n) start[i] = v[i].a;

  ll res = solve(0, n, v, start);

  cout << res << "\n";
  return 0;
}