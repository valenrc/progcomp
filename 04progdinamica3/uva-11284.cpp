// UVA 11284 - Shopping Trip
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
#define forn(i,n)     for(int i=0; i<(int)(n); ++i)
#define fordn(i,d,n)  for(int i=(int)(d); i<(int)(n); ++i)
#define forall(i, c)  for(auto& i : (c))
#define pb push_back
// Functions
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << endl;
}

constexpr double EPS = numeric_limits<double>::epsilon();
const double INF = numeric_limits<double>::infinity();
int n, p;
vector<vector<double>> dist;
vector<vector<double>> dp;
vector<double> save; // lo que ahorro para cada dvd si lo compro en la tienda i
vector<int> store;   // tienda donde se compra el dvd i

double solve(int i, int bitmask){
  if(bitmask == 0) return -dist[i][0]; // caso base: tomo el camino minimo al origen
  if(dp[i][bitmask] > -INF + EPS) return dp[i][bitmask];

  double res = -dist[i][0];

  forn(dvd, p){
    // itero por los dvd's que no estan comprados
    if(bitmask & (1 << dvd)){
      int next = store[dvd];

      double saving = save[dvd] - dist[i][next] + solve(next, bitmask ^ (1 << dvd));
      res = max(res, saving);
    }
  }

  return dp[i][bitmask] = res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; cin >> tt;

  while(tt--){
    int m; cin >> n >> m;     // n: stores; m: num of roads
    n++; // le agrego la "tienda" 0 (origen)
    
    // limpio dist
    dist.assign(n, vector<double>(n, INF));

    forn(i,m){
      int u,v; double w;
      cin >> u >> v >> w;
      // los caminos son bidireccionales pero puede haber caminos de diferente costo!!
      dist[u][v] = min(dist[u][v], w);
      dist[v][u] = min(dist[v][u], w);
    }

    forn(i, n) dist[i][i] = 0.0; // dist(i,i) = 0

    // precomputo la dist. minima entre todas las tiendas usando floyd-warshall
    forn(k, n){
      forn(i, n){
        forn(j, n){
          if(dist[i][k] != INF && dist[k][j] != INF){
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }

    cin >> p;   // cant de de dvd's
    save.resize(p);
    store.resize(p);
    forn(i, p){
      cin >> store[i] >> save[i];
      //store[i]++;
    }

    dp.assign(n, vector<double>(1 << p, -INF));
    int bitmask = (1 << p) - 1; // bitmask para los dvd's no comprados

    double ans = solve(0,bitmask);

    if(ans - EPS <= 0) cout << "Don't leave the house\n";
    else cout << "Daniel can save $" << fixed << setprecision(2) << ans << "\n";
  }
  return 0;
}