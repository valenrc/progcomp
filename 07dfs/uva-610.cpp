// UVa 610 - Street directions
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
void print_graph(const vvi& g) {
  forn(i, g.size()) {
    cout << i << ": ";
    forall(neighbor, g[i]) {
      cout << neighbor << " ";
    }
    cout << "\n";
  }
}

void print_edges(const vector<ii>& edges) {
  forall(e, edges) {
    cout << "(" << e.first << ", " << e.second << ") ";
  }
  cout << "\n";
}

using Graph = vvi;
using Edge = ii;

int n, m, t;

void dfs(const Graph& g, int v, int p, vector<bool> &visited, vector<ii> &bridges, vi &num, vi &low){
  visited[v] = true;

  num[v] = low[v] = t++;
  bool parent_skipped = false;
  forall(u, g[v]){
    if(!parent_skipped && u == p){
      parent_skipped = true;
      continue;
    }
    if(visited[u]){
      low[v] = min(low[v], num[u]);
    }else{
      dfs(g, u, v, visited, bridges, num, low);
      low[v] = min(low[v], low[u]);

      if(low[u] > num[v]) {
        // (u, v) es arista puente
        bridges.pb({u, v});
      }
    }
  }
}

void find_bridges(const Graph& g, vector<Edge>& bridges) {
  t = 0;
  vector<bool> visited(n, false);
  vi num(n, -1); vi low(n, -1);
  
  forn(i, n){
    if(!visited[i]){
      dfs(g, i, -1, visited, bridges, num, low);
    }
  }
}

// busca strong orientation 
void dfs_so(const Graph& g, int v, vector<int> &parent, vector<vb> &edge_used, vector<Edge> &res) {
  forall(u, g[v]){
    if(edge_used[v][u]) continue;
    if(parent[u] == -1){
      // (v,u) tree edge
      parent[u] = v;
      res.pb({v, u});
      edge_used[v][u] = true; edge_used[u][v] = true;
      dfs_so(g, u, parent, edge_used, res);
    }else{
      // (v,u) back edge
      if(u != parent[v]){
        res.pb({v, u}); // si no es padre de v lo agrego al resultado
        edge_used[v][u] = true; edge_used[u][v] = true;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int tt = 1;
  while(cin >> n >> m && (n || m)){
    Graph g(n);
    forn(i, m){
      int u, v; cin >> u >> v; 
      u--; v--; // 0-indexing
      g[u].pb(v); g[v].pb(u);
    }

    // busco las aristas puente 
    vector<Edge> bridges;
    find_bridges(g, bridges);
    //print_edges(bridges);

    // elimino las aristas puente de g
    forall(e, bridges){
      int u = e.first, v = e.second;
      auto it_u = find(g[u].begin(), g[u].end(), v);
      if(it_u != g[u].end()){
        g[u].erase(it_u);
      }
      auto it_v = find(g[v].begin(), g[v].end(), u);
      if(it_v != g[v].end()){
        g[v].erase(it_v);
      }
    }

    // busco strong orientation
    vector<Edge> res; 
    vector<int> parent(n, -1);
    vector<vb> edge_used(n, vb(n, false));
    t = 0;

    forn(i, n){
      if(parent[i] == -1){
        parent[i] = i;
        dfs_so(g, i, parent, edge_used, res);
      }
    }
    cout << tt << "\n\n";
    forall(b, bridges){
      cout << b.first + 1 << " " << b.second + 1 << "\n";
      cout << b.second + 1 << " " << b.first + 1 << "\n";
    }
    forall(e, res){
      cout << e.first + 1 << " " << e.second + 1 << "\n";
    }
    cout << "#\n";
    tt++;
    
  }

  return 0;
}