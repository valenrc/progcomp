// CSES 1160 - Planet queries II
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
void print_matrix(const vvi& m) {
  for(const auto& row : m) {
    for(const auto& elem : row) {
      cout << elem << " ";
    }
    cout << "\n";
  }
}

int timer;
const int MAX = 200000;
const int LOG = 18; // ~=log2(MAX)

vi tin, tout;
vvi up;

int cont_cycle_id = 0;

// busca el k-esimo sucesor del nodo v
int jump(int v, int k) {
  if(k<0) return -1;
  for(int i = LOG-1; i >= 0; i--){
    if((k >> i) & 1){
      v = up[i][v]; // salto de 2^i
      if(v == -1) break;
    }
  }
  return v;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int n, queries;
  cin >> n >> queries;

  vi adj(n);
  up.resize(LOG, vi(n, -1));
  vi cycle_rep(n, -1);

  forn(i, n){
    cin >> adj[i];
    adj[i]--;
    up[0][i] = adj[i]; // el sucesor directo de i es adj[i]
  }

  // binary lifting
  fordn(k, 1, LOG){
    forn(i, n){
      if(up[k-1][i] != -1){
        up[k][i] = up[k-1][up[k-1][i]];
      }else{
        up[k][i] = -1;
      }
    }
  }

  // inicializar todo
  vi dist_to_cycle(n, -1);
  vi cycle_id(n, -1);
  vi pos(n, -1);
  vi cycle_size(n, -1);
  vi visited(n, 0); // 0/1: no visitado/visitado; 2: procesado
  vi temp_idx(n, 0);

  // DFS para encontrar ciclos
  forn(i, n){
    if(visited[i] != 0) continue;

    vi camino_actual;
    int act = i;
    int idx = 0;

    while(visited[act] == 0){
      visited[act] = 1;
      temp_idx[act] = idx;

      camino_actual.pb(act);
      act = adj[act];
      idx++;
    }

    if(visited[act] == 1){
      // se encontro un ciclo
      cont_cycle_id++;

      int inicio_ciclo = temp_idx[act];
      int ciclo_size = idx - inicio_ciclo;
      int rep = camino_actual[inicio_ciclo];

      fordn(k, inicio_ciclo, idx){
        // procesar los nodos en el ciclo
        int v = camino_actual[k];

        visited[v] = 2; // procesado
        cycle_id[v] = cont_cycle_id;
        pos[v] = k - inicio_ciclo;
        cycle_size[v] = ciclo_size;
        dist_to_cycle[v] = 0; // la distancia al ciclo de todos los nodos en el ciclo es 0

        cycle_rep[v] = rep;
      }

      forn(k, inicio_ciclo){
        int v = camino_actual[k]; // nodo fuera del ciclo

        visited[v] = 2;
        cycle_id[v] = cont_cycle_id;

        // distancia desde v hasta el inicio del ciclo
        dist_to_cycle[v] = inicio_ciclo - k;

        cycle_rep[v] = rep; 
        cycle_size[v] = ciclo_size;
      }
    }else{
      // act ya fue procesado
      // todos los nodos en el camino actual llegan al ciclo de act

      forn(k, idx){
        // idx = tamaño del camino actual
        int v = camino_actual[k];
        visited[v] = 2;

        cycle_id[v] = cycle_id[act];
        
        // distqancia desde v hasta el inicio del ciclo
        dist_to_cycle[v] = (idx - k) + dist_to_cycle[act];

        cycle_rep[v] = cycle_rep[act];
        cycle_size[v] = cycle_size[act];
      }
    }
  }

  // procesar las queries
  forn(q, queries){
    int u, v; cin >> u >> v;
    u--; v--;

    if(cycle_id[u] == -1 || cycle_id[v] == -1 || cycle_id[u] != cycle_id[v]) {
      // si alguno de los nodos no pertenece a un ciclo o pertenecen a ciclos diferentes
      cout << -1 << "\n";
      continue;
    }
    
    int dist_u = dist_to_cycle[u];
    int dist_v = dist_to_cycle[v];

    int res = -1;

    if(dist_u >= dist_v){
      // dist_u - dist_v es exactamente la distancia entre u y v
      if(jump(u, dist_u - dist_v) == v)
      res = dist_u - dist_v;
    }

    if(res == -1){
      if(dist_v == 0){
        int anc_u = jump(u, dist_u);

        int dist_anc_u = pos[anc_u];
        int v_anc_u = pos[v]; // posicion de v en el ciclo

        int size = cycle_size[u];

        int dist = (v_anc_u - dist_anc_u + size) % size;
        // mod la long del ciclo para asegurar que la distancia sea positiva y represente la dist. mas chica dentro del ciclo

        res = dist + dist_u;
      }
    }

    cout << res << "\n";
  }

  return 0;
}