// UVa 10306 - e-coins
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
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
// Constants
const double PI = acos(-1.0);
const double EPS = 1e-9;
// Functions
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << endl;
}

// BFS explorando todo el espacio de busqueda me garantiza un camino minimo.
// Cada arista que sale de un nodo es una moneda que se agrega a la solucion, se actualiza el valor e-module y se decide si podar o seguir buscando
// Un estado es solucion cuando e-module == S
// Como hay riesgo de TLE entonces puedo usar DP, pero no se si es necesario

// Custom hash for pairs used in unordered_map
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2> &pair) const {
      auto hash1 = std::hash<T1>{}(pair.first);
      auto hash2 = std::hash<T2>{}(pair.second);

      // Combine hashes (simple XOR and shift)
      return hash1 ^ (hash2 << 1);
  }
};

int n, m, s;

int solve(vector<ii>& coins, int std_value, int it_value){
  // bfs hasta encontrar el valor exacto de s
  queue<ii> q;
  unordered_map<ii, int, pair_hash> dist; // Use the custom hash

  q.push({std_value, it_value});
  dist[{std_value, it_value}] = 0;

  int conv, it;
  int res = -1;

  while(!q.empty()){
    ii c = q.front(); q.pop();
    //cout << "c = " << c.first << " " << c.second << endl;
    if(c.first*c.first + c.second*c.second == s){
      res = dist[c];
      break;
    }
    // genero los hijos
    forall(cc, coins){
      conv = c.first + cc.first;
      it = c.second + cc.second;
      if(dist.find({conv, it}) == dist.end() && conv*conv + it*it <= s){
        dist[{conv, it}] = dist[c] + 1;
        q.push({conv, it});
      }
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  while(n--){
    cin >> m >> s;
    s *= s; // uso el cuadrado de s para no tener que usar sqrt
    vector<ii> coins(m);
    forn(i, m) cin >> coins[i].first >> coins[i].second; // conv_value; it_value

    //forall(coin, coins) cout << coin.first << " " << coin.second << endl;

    int res = solve(coins, 0, 0);

    // if res==-1 cout "not possible" else cout << res << endl;
    res == -1 ? cout << "not possible" : cout << res;
    cout << endl;

  }

  return 0;
}