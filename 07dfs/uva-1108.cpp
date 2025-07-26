// Mining your own business
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <utility>    // pair, make_pair, swap, min, max
#include <limits>     // numeric_limits
// Data structures
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;
// Data types
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>  ii;
typedef vector<int>     vi;
typedef vector<bool>    vb;
typedef vector<ll>     vll;
typedef vector<vi>     vvi;
typedef vector<ii>     vii;
// Macros
#define forn(i,n)     for(int i=0; i<(int)(n); i++)
#define fordn(i,d,n)  for(int i=(int)(d); i<(int)(n); i++)
#define forall(i, c)  for(auto& i : (c))
#define pb push_back

unordered_map<ll, vll> adj;
vector<vll> bcc_graph;
vector<bool> is_art_point;
ll bcc_count;

vll dfn, low;
vector<pair<ll,ll>> edge_stack;
ll timer;
ll max_v_num;

void dfs(ll u, ll p){
  dfn[u] = low[u] = timer++;
  int children = 0;

  forall(v, adj[u]){
    if(v == p) continue;

    if(dfn[v] != -1){
      // es back edge
      if(dfn[v] < dfn[u]){
        edge_stack.pb({u,v});
        low[u] = min(low[u], dfn[v]);
      }
    } else{
      // tree edge
      children++;
      edge_stack.pb({u,v});
      dfs(v, u);
      low[u] = min(low[u], low[v]);

      if((p != -1 && low[v] >= dfn[u]) || (p == -1 && children > 1)){
        is_art_point[u] = true;

        bcc_count++;
        set<ll> curr_bcc_nodes;

        while(true){
          pair<ll, ll> edge = edge_stack.back();
          edge_stack.pop_back();
          curr_bcc_nodes.insert(edge.first);
          curr_bcc_nodes.insert(edge.second);

          if(edge.first == u && edge.second == v) break;
        }

        bcc_graph.pb(vll(curr_bcc_nodes.begin(), curr_bcc_nodes.end()));
      }
    }
  }
}

void tarjan(){
  // limpia bcc_index, is_art_point y bcc_count
  // luego encuentra los articulation points de adj y particiona adj en componentes biconexas en el grafo bcc_graph
  // bcc_graph[i] es el vector de vertices que se encuentra en la componente biconexa i
  bcc_graph.clear();
  bcc_count = 0;
  max_v_num = 0;
  if(adj.empty()) return;

  forall(pair, adj) max_v_num = max(max_v_num, pair.first);

  is_art_point.assign(max_v_num + 1, false);
  dfn.assign(max_v_num + 1, -1);
  low.assign(max_v_num + 1, -1);
  edge_stack.clear();
  timer = 0;

  fordn(i, 1, max_v_num +1){
    if(adj.count(i) && dfn[i] == -1) dfs(i,-1);
  }

  // pueden quedar aristas en el stack!!
  if(!edge_stack.empty()){
    bcc_count++;
    set<ll> last_bcc_nodes;
    forall(edge, edge_stack){
      last_bcc_nodes.insert(edge.first);
      last_bcc_nodes.insert(edge.second);
    }

    bcc_graph.pb(vll(last_bcc_nodes.begin(), last_bcc_nodes.end()));
    edge_stack.clear();
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  ll n;
  int test_case = 1;

  while(cin >> n && n != 0){
    adj.clear();

    forn(_,n){
      int s,t;
      cin >> s >> t;
      adj[s].pb(t);
      adj[t].pb(s);
    }

    tarjan();

    ll g_size = adj.size();
    ll maneras = 1;

    if(bcc_count == 1){
      // elegir 2 vertices cualquiera del total
      maneras = g_size * (g_size - 1) / 2;
      cout << "Case " << test_case << ": " << 2 << " " << maneras << "\n";
      test_case++;
      continue;
    }

    ll scapes = 0;
    // recorrer bc
    forall(nodes, bcc_graph){
      int cant_art_points = 0;
      forall(v, nodes){
        if(is_art_point[v]) cant_art_points++;
      }

      if(cant_art_points != 1) continue;
      // si esta comp solo tiene un punto de articulacion, agregar un scape-shaft
      scapes++;
      ll bcc_size = nodes.size();
      maneras = maneras * (bcc_size - 1); // todos los nodos menos el pto de art.
    }

    cout << "Case " << test_case << ": " << scapes << " " << maneras << "\n";
    test_case++;
  }

  return 0;
}