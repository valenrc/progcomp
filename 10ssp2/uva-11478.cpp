// Halum - Da TLE porque usé matriz de adyacencias :(
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
const int INF = numeric_limits<int>::max();
void print_adj_matrix(const vvi& matrix) {
  forn(i, matrix.size()) {
    forn(j, matrix[i].size()) {
      if (matrix[i][j] == INF) cout << "INF ";
      else cout << matrix[i][j] << " ";
    }
    cout << "\n";
  }
}

int n,m;

bool dfs(int u, const vvi& a, vb& visited, vb& on_path){
  if(on_path[u]) return false;
  if(visited[u]) return true;

  visited[u] = true;
  on_path[u] = true;

  forn(v, n){
    if(a[u][v] != INF){
      if(!dfs(v, a, visited, on_path)) return false;
    }
  }

  on_path[u] = false;
  return true;
}

bool is_dag(const vvi& a){
  // dfs para chequear si el grafo es un DAG
  vb visited(n, false);
  vb on_path(n, false);

  forn(u, n){
    if(!visited[u]){
      if(!dfs(u, a, visited, on_path)) return false;
    }
  }
  return true;
}

bool sys_has_solution(const vvi& a, int x){
  // bellman-ford para chequear si el sistema de restricciones de diferencias tiene solucion
  // adapté el algoritmo de la clase 9 (soulignac) para matriz de adyacencia
  vi dist(n+1, INF);
  vi iter(n+1, 0);
  vi changed;

  dist[n] = 0;
  changed.pb(n);

  for(int i=1; i<= n+1 && !changed.empty(); i++){
    vi extensions;
    forall(v, changed){
      forn(u, n+1){
        if(a[v][u] == INF) continue;
        // todas las aristas del grafo tienen peso a[v][u] - x
        if(dist[v] + (a[v][u] - x) < dist[u]){
          if(iter[u] != i) extensions.pb(u);
          iter[u] = i;
          dist[u] = dist[v] + (a[v][u] - x);
        }
      }
    }
    swap(extensions, changed);
  }

  // si changed no esta vacio, hay ciclo negativo
  if(!changed.empty()) return false;
  else return true;

}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  while(cin >> n >> m){
    vvi a(n+1, vi(n+1, INF));

    forn(i, n) a[n][i] = 0; // vertice source para el sistema de restricciones

    int sum_w = 0;

    forn(i, m){
      int u, v, w; cin >> u >> v >> w;
      u--; v--;
      a[u][v] = w;
      sum_w += w;
    }

    if(is_dag(a)){
      cout << "Infinite\n";
      continue;
    }

    // BSTA para encontrar el maximo X
    int l = 0, r = sum_w +1;
    while(l < r){
      int x = (l+r+1) / 2;

      if(sys_has_solution(a, x)){
        l = x;
      }else{
        r = x-1;
      }
    } 

    if(l <= 0) cout << "No Solution\n";
    else cout << l << "\n";
    
  }

  return 0;
}