// UVa 10707 - 2D Nim
// Problema de flood fill
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
void print_container(const vector<vector<pair<int, int>>>& container) {
  cout << "<";
  for (size_t i = 0; i < container.size(); ++i) {
    cout << "<";
    for (size_t j = 0; j < container[i].size(); ++j) {
      cout << "(" << container[i][j].first << "," << container[i][j].second << ")";
      if (j < container[i].size() - 1)
        cout << ",";
    }
    cout << ">";
    if (i < container.size() - 1)
      cout << ", ";
  }
  cout << ">" << endl;
}

// S/N/E/W
int dx[] = {0, 1, 0,-1};
int dy[] = {1, 0,-1, 0};

int w, h, n;

vvi board1;
vvi board2;
vector<vb> visited;

void dfs(const vvi& board, int x, int y, vii& cluster){
  if(x < 0 || x >= h || y < 0 || y >= w || visited[x][y] || board[x][y] == 0) return;

  visited[x][y] = true;
  cluster.pb(pair<int, int>(x,y)); // coordendas de cada pieza en el cluster
  // en este caso el parametro cluster seria vector<pair<int, int>>
  // y procedo buscando representaciones canonicas 
  //cluster.pb(board[x][y]);

  for(int d = 0; d < 4; d++){
    dfs(board, x + dx[d], y + dy[d], cluster);
  }
}

vector<vii> find_clusters(const vvi& board){
  // Dfs para encontrar componentes conexas
  vector<vii> clusters;
  visited.assign(h, vb(w, false));

  forn(i, h){
    forn(j, n){
      if(board[i][j] != 0 && !visited[i][j]){
        vii cluster;
        dfs(board, i, j, cluster);
        if(!cluster.empty()) clusters.pb(cluster);
      }
    }
  }

  return clusters;
}

void normalize(vii& shape) {
  if (shape.empty()) return;

  int min_x = shape[0].first;
  int min_y = shape[0].second;
  for (const auto& p : shape) {
    min_x = min(min_x, p.first);
    min_y = min(min_y, p.second);
  }

  for (auto& p : shape) {
    p.first -= min_x;
    p.second -= min_y;
  }
  
  // ordenar para poder compararlos
  sort(shape.begin(), shape.end());
}

vii rep_canonica(vii& cluster) {
  vector<vii> orientations;

  for (int i = 0; i < 8; ++i) {
    vii act_orientation;
    for (const auto& p : cluster) {
      int x = p.first;
      int y = p.second;
      ii new_p;

      switch (i) {
        case 0: new_p = {x, y}; break;
        case 1: new_p = {-y, x}; break; // 90 grados
        case 2: new_p = {-x, -y}; break; // 180
        case 3: new_p = {y, -x}; break;  // 270
        case 4: new_p = {x, -y}; break; // espejado
        case 5: new_p = {y, x}; break; // espejado + 90 grados
        case 6: new_p = {-x, y}; break;
        case 7: new_p = {-y, -x}; break; 
      }
      act_orientation.push_back(new_p);
    }
    normalize(act_orientation);
    orientations.push_back(act_orientation);
  }

  // la rep canonica es la rep lexicograficamente menor
  sort(orientations.begin(), orientations.end());
  return orientations[0];
}


int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; cin >> tt;
  while(tt--){
    cin >> w >> h >> n;
    board1.assign(h, vi(w, 0));
    board2.assign(h, vi(w, 0));

    for(int i = 0; i < n; i++){
      int x, y; cin >> x >> y;
      board1[y][x] = i+1;
    }

    for(int i = 0; i < n; i++){
      int x, y; cin >> x >> y;
      board2[y][x] = i+1;
    }

    vector<vii> clusters_b1 = find_clusters(board1);
    //print_container(clusters_b1);

    vector<vii> clusters_b2 = find_clusters(board2);
    //print_container(clusters_b2);

    // verificar si los clusters son iguales usando graph isomorphism para grid graphs
    // no encontre un algoritmo de isomorfismo para grid graphs pero segun la literatura este existe

    if(clusters_b1.size() != clusters_b2.size()){
      cout << "NO\n";
      continue;
    }

    vector<vii> can_b1, can_b2; // representacion canonica de cada cluster
    forall(c, clusters_b1) can_b1.push_back(rep_canonica(c));
    forall(c, clusters_b2) can_b2.push_back(rep_canonica(c));

    sort(can_b1.begin(), can_b1.end());
    sort(can_b2.begin(), can_b2.end());

    if(can_b1 == can_b2)
      cout << "YES\n";
    else cout << "NO\n";

  }

  return 0;
}