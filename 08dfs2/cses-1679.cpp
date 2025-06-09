// CSES 1679 - Course schedule
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

#define WHITE 0
#define GRAY  1
#define BLACK 2

int n,m;
vi topo;
vi color;
bool cycle = false;

void dfs(const vvi& graph, int v){
  color[v] = GRAY;

  forall(u, graph[v]){
    if(cycle) return;
    
    if(color[u] == WHITE){
      dfs(graph, u);
    }else{
      if(color[u] == GRAY){
        cycle = true;
        return;
      }
    }
  }
  color[v] = BLACK;
  topo.pb(v);
}

void topo_sort(const vvi& graph){
  color.assign(n, WHITE);
  cycle = false;

  forn(i, n){
    if(color[i] == WHITE) dfs(graph, i);
  }

  if(cycle){
    cout << "IMPOSSIBLE" << "\n";
  }else{
    for(int i=n-1; i>=0; i--){
      cout << topo[i] + 1 << " ";
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  cin >> n >> m;
  vvi graph(n);
  forn(i, m){
    int u, v; cin >> u >> v;
    u--; v--;
    graph[u].pb(v);
  }

  topo_sort(graph); cout << "\n";

  return 0;
}