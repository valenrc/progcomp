// Number of paths in grid - Gym 325692O
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <bitset>

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

extern int ans;
int ans = 0;

void solve(vvi& a, vector<vb>& visited, int i, int j, int n, int m){
  if( i>=n || j>=m ) return;
  if ( i<0 || j<0 ) return;
  if( a[i][j] == 0 ) return;
  if( visited[i][j] ) return;
  if( i==n-1 && j==m-1 ){
    ans++;
    return;
  }

  visited[i][j] = 1;
  solve(a, visited, i+1, j, n, m);
  solve(a, visited, i, j+1, n, m);
  solve(a, visited, i-1, j, n, m);
  solve(a, visited, i, j-1, n, m);
  visited[i][j] = 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n,m;
  cin >> n >> m;
  vvi a(n, vi(m));                 // matriz de enteros - a lo sumo de 6x6
  vector<vb> visited(n, vb(m,0));  // matriz de elementos visitados

  forn(i,n) {
    forn(j,m) {
      cin >> a[i][j];
    }
  }
  solve(a, visited, 0, 0, n, m);
  cout << ans << endl;

  return 0;
}