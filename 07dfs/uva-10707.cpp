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
void print_container(const vector<vector<int>>& container) {
  cout << "<";
  for (size_t i = 0; i < container.size(); ++i) {
    cout << "<";
    for (size_t j = 0; j < container[i].size(); ++j) {
      cout << container[i][j];
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
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int w, h, n;

vvi board1;
vvi board2;
vector<vb> visited;

void dfs(const vvi& board, int x, int y, vi& cluster){
  if(x < 0 || x >= h || y < 0 || y >= w || visited[x][y] || board[x][y] == 0) return;

  visited[x][y] = true;
  cluster.pb(board[x][y]);

  for(int d = 0; d < 4; d++){
    dfs(board, x + dx[d], y + dy[d], cluster);
  }
}

vvi find_clusters(const vvi& board){
  // Dfs para encontrar componentes conexas
  vvi clusters;
  visited.assign(h, vb(w, false));

  forn(i, h){
    forn(j, n){
      if(board[i][j] != 0 && !visited[i][j]){
        vi cluster;
        dfs(board, i, j, cluster);
        if(!cluster.empty()) clusters.pb(cluster);
      }
    }
  }

  return clusters;
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

    vvi clusters_b1 = find_clusters(board1);
    print_container(clusters_b1);

    vvi clusters_b2 = find_clusters(board2);
    print_container(clusters_b2);

  }

  return 0;
}