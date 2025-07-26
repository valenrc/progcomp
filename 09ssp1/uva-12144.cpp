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
void print_adjacency_list(const vector<vector<ii> >& adj) {
  for (int i = 0; i < adj.size(); i++) {
    cout << i << ": ";
    for (auto &edge : adj[i])
      cout << "(" << edge.first << ", " << edge.second << ") ";
    cout << "\n";
  }
}

vi parent;
vi dist_s;
vi dist_d;
vi used;
int n, m;
const int INF = 1e9;

void dijkstra(const vector<vii>& adj, vi& dist, int s){
  parent.assign(n, -1);
  used.assign(n, false);
  dist[s] = 0;

  forn(i, n){
    int v = -1;

    // buscar el vertice no usado con dist minima
    forn(j, n){
      if(!used[j] && (v == -1 || dist[j] < dist[v])) v = j;
    }

    if(dist[v] == INF) break;

    used[v] = true;

    forall(e, adj[v]){
      int u = e.first;
      int p = e.second;

      if(dist[v] + p < dist[u]){
        dist[u] = dist[v] + p;
        parent[u] = v;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  while(cin >> n >> m && (n || m)) {
    vector<vii> adj(n); // adj[u][_].first = v, adj[u][_].second = p para la arista (u,v) con peso p
    vector<vii> rev_adj(n); // inverso
    int s, d;
    cin >> s >> d;

    forn(i, m){
      int u, v, p;
      cin >> u >> v >> p;
      adj[u].pb(ii(v, p));
      rev_adj[v].pb(ii(u, p));
    }

    dist_s.assign(n, INF);
    dist_d.assign(n, INF);

    dijkstra(adj, dist_s, s);
    int p = dist_s[d];

    // busco la dist de todos los nodos hacia d
    dijkstra(rev_adj, dist_d, d);

    vector<vii> new_adj(n);

    forn(u, n){
      forn(i, adj[u].size()){
        int v = adj[u][i].first;
        int w = adj[u][i].second;

        if(dist_s[u] + w + dist_d[v] != p){
          new_adj[u].pb(ii(v, w));
        }
      }
    }

    dist_s.assign(n, INF);
    dijkstra(new_adj, dist_s, s);
    p = dist_s[d];

    if(p == INF){
      cout << -1 << "\n";
    }else{
      cout << p << "\n";
    }

  }

  return 0;
}