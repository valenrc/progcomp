// - Robots on ice
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <bitset>     // bitset

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

#define MAX 64 //8x8
ii p1;
ii p2;
ii p3;
int t1, t2, t3;

//ull node_count = 0;

int bfs(bitset<MAX> visited, int n, int m, int r, int c){
  // visited es pasado por valor
  int count = 0;
  queue<ii> q;
  visited[r*m+c] = true;
  visited[1] = true; // (0,1)

  // source = (0,1)
  q.push(ii(0,1));

  while(!q.empty()){
    count++;
    ii s = q.front();
    q.pop();

    // meto los puntos alcanzables
    if(s.first-1 >= 0){
      if(!visited[(s.first-1)*m + s.second]){
      visited[(s.first-1)*m + s.second] = true;
      q.push(ii(s.first-1, s.second));
      }
    }
    if(s.first+1 < n){
      if(!visited[(s.first+1)*m + s.second]){
      visited[(s.first+1)*m + s.second] = true;
      q.push(ii(s.first+1, s.second));
      }
    }
    if(s.second-1 >= 0){
      if(!visited[s.first*m + (s.second-1)]){
      visited[s.first*m + (s.second-1)] = true;
      q.push(ii(s.first, s.second-1));
      }
    }
    if(s.second+1 < m){
      if(!visited[s.first*m + (s.second+1)]){
      visited[s.first*m + (s.second+1)] = true;
      q.push(ii(s.first, s.second+1));
      }
    }
  }
  return count;
}

// r:row, c:column, t:time in steps, n,m: dimensiones del grid
int solve(int r, int c, int t, int n, int m, bitset<MAX>& visited){
  //cout << "visited: " << r << " " << c << " " << t << endl;
  //node_count++;
  if(r == 0 && c == 1){
    if(t == n*m){
      return 1;
    }else{
      return 0;
    }
  }

  // si llego al step de un checkpoint y no estoy en el punto correcto, hago backtracking
  if(t == t1 && (r != p1.first || c != p1.second)) return 0;
  if(t == t2 && (r != p2.first || c != p2.second)) return 0;
  if(t == t3 && (r != p3.first || c != p3.second)) return 0;

  // si estoy en un checkpoint y no estoy en el tiempo correcto
  if(p1.first == r && p1.second == c && t != t1) return 0;
  if(p2.first == r && p2.second == c && t != t2) return 0;
  if(p3.first == r && p3.second == c && t != t3) return 0;

  // si ya pase por un checkpoint en el tiempo incorrecto
  if(t < t1 && visited[p1.first * m + p1.second]) return 0;
  if(t < t2 && visited[p2.first * m + p2.second]) return 0;
  if(t < t3 && visited[p3.first * m + p3.second]) return 0;

  // si el tiempo minimo + el t actual es mayor al t del siguiente checkpoint, no es posible llegar
  int d;
  if(t < t1){
    // el siguiente checkpoint es p1
    d = abs(r - p1.first) + abs(c - p1.second);
    if(d + t > t1) return 0;
  }else if(t < t2){
    d = abs(r - p2.first) + abs(c - p2.second);
    if(d + t > t2) return 0;
  }else if(t < t3){
    d = abs(r - p3.first) + abs(c - p3.second);
    if(d + t > t3) return 0;
  }else{
    // si no, el siguiente es el final (1,0)
    d = abs(r - 0) + abs(c - 1);
    if(d + t > n*m) return 0;
  }

  // busco todos los puntos alcanzables desde el final (0,1), la cantidad debe ser igual a n*m - t
  int count = bfs(visited, n, m, r, c);
  if(count != n*m - t) return 0;

  // visitar los demas grids que no esten visitados
  int res = 0;
  if(c-1 >= 0){
    if(!visited[r*m + (c-1)]){
      visited[r*m + (c-1)] = true;
      res += solve(r, c-1, t+1, n, m, visited);
      visited[r*m + (c-1)] = false;
    }
  }
  if(c+1 < m){
    if(!visited[r*m + (c+1)]){
      visited[r*m + (c+1)] = true;
      res += solve(r, c+1, t+1, n, m, visited);
      visited[r*m + (c+1)] = false;
    }
  }
  if(r-1 >= 0){
    if(!visited[(r-1)*m + c]){
      visited[(r-1)*m + c] = true;
      res += solve(r-1, c, t+1, n, m, visited);
      visited[(r-1)*m + c] = false;
    }
  }
  if(r+1 < n){
    if(!visited[(r+1)*m + c]){
      visited[(r+1)*m + c] = true;
      res += solve(r+1, c, t+1, n, m, visited);
      visited[(r+1)*m + c] = false;
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n,m;
  int c = 0;
  cin >> n; cin >> m;

  while(n || m){
    bitset<MAX> visited; // visited[r][c] -> visited[r*m+c]
    visited[0] = true; // (0,0)

    size_t size = n*m;

    cin >> p1.first >> p1.second;
    cin >> p2.first >> p2.second;
    cin >> p3.first >> p3.second; 

    t1 = (int)((size)/4);
    t2 = (int)((size)/2);
    t3 = (int)((size*3)/4);

    //cout << t1 << " " << t2 << " " << t3 << endl;
    //node_count = 0;
    int res = solve(0,0,1,n,m,visited);
    //cout << "node_count: " << node_count << endl;

    cout << "Case " << ++c << ": " << res << endl;
    cin >> n; cin >> m;
  }

  return 0;
}