  // No se entrega
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

  int nb;
  const int MAX_BEEPERS = 11;
  vvi dist(MAX_BEEPERS, vi(MAX_BEEPERS, 0));
  vvi dp(MAX_BEEPERS, vi(1 << MAX_BEEPERS, -1));

  int tsp(int i, int mask){
    if(mask == (1 << nb) - 1) return dist[i][0]; // regresar al origen, eso cuesta dist(i,0)
    if(dp[i][mask] != -1) return dp[i][mask];
    
    int res = numeric_limits<int>::max();

    forn(j, nb){
      // iterar sobre todos los beepers que no fueron visitados
      if((mask & (1 << j)) == 0){
        res = min(res, dist[i][j] + tsp(j, mask | (1 << j)));
      }
    }
    return dp[i][mask] = res;
  }

  int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int tt; cin >> tt;
    forn(_,tt){
      int n, m; cin >> n >> m;
      int x, y; cin >> x >> y;

      cin >> nb; // number of beepers
      nb++;
      vii beepers(nb);
      beepers[0] = {x,y};

      fordn(i,1,nb){
        cin >> x >> y;
        beepers[i] = {x,y};
      }

      // limpio dist y dp
      for (int i = 0; i < nb; ++i){
        std::fill(dist[i].begin(), dist[i].begin() + nb, 0);
        std::fill(dp[i].begin(), dp[i].begin() + (1 << nb), -1);
      }

      // pre-computo distancia manhattan entre beepers
      forn(i, nb){
        fordn(j, i, nb){
          if (i != j){
            dist[i][j] = abs(beepers[i].first - beepers[j].first) + abs(beepers[i].second - beepers[j].second);
            dist[j][i] = dist[i][j];
          }
        }
      }

      int res = tsp(0, 1); // empiezo en el origen (ya visitado)
      cout << res << "\n";
    }
    return 0;
  }