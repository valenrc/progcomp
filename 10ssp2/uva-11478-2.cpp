// Halum - refactorizado con lista de adyacencias
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
typedef vector<ii>     vii;
typedef vector<vii>     vvii; // Adjacency list: vector of vector of pairs
// Macros
#define forn(i,n)     for(int i=0; i<(int)(n); i++)
#define fordn(i,d,n)  for(int i=(int)(d); i<(int)(n); i++)
#define forall(i, c)  for(auto& i : (c))
#define pb push_back
// Functions
const int INF = numeric_limits<int>::max();

int n, m;

bool dfs(int u, const vvii& adj, vb& visited, vb& on_path) {
  visited[u] = true;
  on_path[u] = true;
  
  for (const auto& edge : adj[u]) {
    int v = edge.first;
    if (on_path[v]) {
      return false;
    }
    if (!visited[v]) {
      if (!dfs(v, adj, visited, on_path)) {
        return false;
      }
    }
  }

  on_path[u] = false;
  return true;
}

bool is_dag(const vvii& adj) {
  // dfs para chequear si el grafo es un DAG
  vb visited(n, false);
  vb on_path(n, false);

  forn(u, n) {
    if (!visited[u]) {
      if (!dfs(u, adj, visited, on_path)) return false;
    }
  }
  return true;
}

// SPFA para chequear si el sistema de restricciones tiene solucion
// i.e. el grafo tiene ciclos negativos
bool sys_has_solution(const vvii& adj, int x) {
  int num_vertices = n + 1;
  vi dist(num_vertices, INF);
  vi relax_count(num_vertices, 0);
  vb on_queue(num_vertices, false);
  queue<int> q;

  int source = n;
  dist[source] = 0;
  q.push(source);
  on_queue[source] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    on_queue[u] = false;

    for (const auto& edge : adj[u]) {
      int v = edge.first;
      int w = edge.second;
      int weight = w - x; // las aristas tiene peso w(u. w) - x

      if (dist[u] != INF && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        if (!on_queue[v]) {
          q.push(v);
          on_queue[v] = true;
          relax_count[v]++;
          if (relax_count[v] >= num_vertices) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  while (cin >> n >> m) {
    vvii adj(n + 1);

    forn(i, m) {
      int u, v, w; cin >> u >> v >> w;
      u--; v--;
      adj[u].pb({v, w});
    }

    if (is_dag(adj)) {
      cout << "Infinite\n";
      continue;
    }

    // vertice source para el sistema de restricciones
    forn(i, n) {
      adj[n].pb({i, 0});
    }

    // BSTA para encontrar el maximo X
    int l = 0, r = 10001;
    while (l < r) {
      int x = l + (r - l + 1) / 2;

      if (sys_has_solution(adj, x)) {
        l = x;
      } else {
        r = x - 1;
      }
    }

    if (l <= 0) {
      cout << "No Solution\n";
    } else {
      cout << l << "\n";
    }
  }

  return 0;
}