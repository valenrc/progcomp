// Wishmaster
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
typedef unsigned int uint;
typedef unsigned long ulong;
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

int n, m;
vi sccs_id;

inline int neg(int i){
  if(i<=n) return i+n;
  else return i-n;
}
void dfs1(int u, const vvi& adj, vb& visited, vi& order) {
  visited[u] = true;
  for (int v : adj[u]) {
    if (!visited[v]) {
      dfs1(v, adj, visited, order);
    }
  }
  order.pb(u);
}

void dfs2(int u, const vvi& rev_adj, int c) {
  sccs_id[u] = c;
  for (int v : rev_adj[u]) {
    if (sccs_id[v] == -1) {
      dfs2(v, rev_adj, c);
    }
  }
}

void sccs(vvi& adj){
  int num_nodes = 2 * n;
  vvi rev_adj(num_nodes + 1);
  fordn(u, 1, num_nodes + 1) {
    for (int v : adj[u]) {
      rev_adj[v].pb(u);
    }
  }

  vi order;
  vb visited(num_nodes + 1, false);

  fordn(i, 1, num_nodes + 1) {
    if (!visited[i]) {
      dfs1(i, adj, visited, order);
    }
  }

  int c = 0;
  reverse(order.begin(), order.end());
  for (int u : order) {
    if (sccs_id[u] == -1) {
      dfs2(u, rev_adj, c);
      c++;
    }
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int t; cin >> t;
  int tt = 1;
  while(tt <= t){
    cin >> n >> m;
    vvi adj(n*2+1);

    forn(i,m){
      int w1, w2; cin >> w1 >> w2;
      if(w1 < 0) w1 = n-w1;
      if(w2 < 0) w2 = n-w2;
      // agrego las aristas (w1 -> ~w2)y (w2 -> ~w1)
      adj[w1].pb(neg(w2));
      adj[w2].pb(neg(w1));
    }

    // busco las scc del grafo
    sccs_id.clear();
    sccs_id.resize(n*2+1, -1);
    sccs(adj);

    // evaluo satisfactibilidad de 2-sat
    bool res = true;
    fordn(i, 1, n+1){
      if(sccs_id[i] == sccs_id[i+n]) res = false;
    }

    cout << "Case " << tt << ": ";
    if(res) cout << "Yes\n";
    else cout << "No\n";

    tt++;
  }

  return 0;
}