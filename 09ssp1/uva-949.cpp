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
template <typename TCOMP>
void print_container(const TCOMP& c){
  forall(i,c) cout << i << " ";
  cout << "\n";
}

const int MAX_TIME = 600;

bool monitored[MAX_TIME][100][100] = {{false}};
bool restricted[100][100][100][100] = {{{{false}}}};
bool visited[100][100][MAX_TIME] = {{{false}}};

int dx[] = {1, 0, -1, 0, 0}; // dx/dy[4]: caso de esperar
int dy[] = {0, 1, 0, -1, 0};
int n,m;

struct state{
  int x, y, t;
  state(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {} // constructor
};

int bfs(){
  queue<state> q;

  q.push(state(0, 0, 0));

  while(!q.empty()){
    state act = q.front(); q.pop();

    if(act.x == n-1 && act.y == m-1){
      return act.t;
    }

    int nt = act.t + 1;

    forn(i, 5){
      int nx = act.x + dx[i];
      int ny = act.y + dy[i];
      
      if(nx < 0 || nx >= n || ny < 0 || ny >= m)  continue;
      if(restricted[act.x][act.y][nx][ny])        continue;
      if(visited[nx][ny][nt])                     continue;
      // si monitored[nt]=(nx, ny) entonces no puedo ir a (nx, ny)
      if(monitored[nt][nx][ny]) continue;

      visited[nx][ny][nt] = true;
      q.push(state(nx, ny, nt));
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
  
  while(cin >> n >> m) {
    // reinicializar los arrays
    memset(monitored, 0, sizeof(monitored));
    memset(visited, 0, sizeof(visited));
    memset(restricted, 0, sizeof(restricted));
    
    int r;
    cin >> r;
    forn(i, r) {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      restricted[a][b][c][d] = true;
    }
    
    int s;
    cin >> s;
    forn(i, s) {
      int t, x, y;
      cin >> t >> x >> y;
      monitored[t][x][y] = true;
    }
    
    int res = bfs();
    cout << res << "\n";
  }
  return 0;
}