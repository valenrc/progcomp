// Mines
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

int n; 
struct Node{
  ll x, y, d;
};
vb visited;
vi finish_order;
vi scc_id;
vector<Node> mines;
int scc_id_act;

inline bool neighbor(int i, int j){
  const Node& mi = mines[i];
  const Node& mj = mines[j];
  return (abs(mi.x - mj.x) <= mi.d) and (abs(mi.y - mj.y) <= mi.d);
}

// dfs para finish order
void dfs1(int u) {
  visited[u] = true;
  forn(v, n) {
    if (!visited[v] && neighbor(u, v)) {
      dfs1(v);
    }
  }
  finish_order.push_back(u);
}

// dfs para asignar las sccs
void dfs2(int u) {
  visited[u] = true;
  scc_id[u] = scc_id_act;
  forn(v, n) { 
    // u->v es arista del grafo transpuesto si v->u es arista del grafo
    if (!visited[v] && neighbor(v, u)) {
      dfs2(v);
    }
  }
}

// Algoritmo de Kosaraju para encontrar sccs
// no tuve que definir explicitamente ningun grafo (G, G_t, G_c)
int sccs() {
  if (n == 0) return 0;

  visited.assign(n, false);
  finish_order.clear();
  finish_order.reserve(n);

  forn(i, n) {
    if (!visited[i]) {
      dfs1(i);
    }
  }

  scc_id.assign(n, 0);
  scc_id_act = 0;
  visited.assign(n, false);

  for (int i = n - 1; i >= 0; --i) {
    int u = finish_order[i];
    if (!visited[u]) {
      scc_id_act++;
      dfs2(u);
    }
  }

  if (scc_id_act == 0) return n;

  // cuento el in-degree de cada scc recorriendo el grafo original
  vi scc_in_degree(scc_id_act + 1, 0);

  forn(u, n) {
    forn(v, n) {
      if(u==v) continue;
      if (scc_id[u] != scc_id[v] && neighbor(u, v)) {
        scc_in_degree[scc_id[v]]++;
      }
    }
  }

  // cuento las sccs de in-degree cero
  int res = 0;
  for (int i = 1; i <= scc_id_act; ++i) {
    if (scc_in_degree[i] == 0) {
      res++;
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; cin >> tt;
  while(tt--){
    cin >> n;  
    mines.clear();
    mines.resize(n);

    forn(i, n){
      cin >> mines[i].x;
      cin >> mines[i].y;
      cin >> mines[i].d;

      mines[i].d /= 2;
    }

    int res = sccs();

    cout << res << "\n";
  }

  return 0;
}