// 15-puzzle
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
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>  ii;
typedef pair<double,double> pdd;
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
#define pb            push_back
template <typename TCOMP>
void print_container(const TCOMP& c){
  cout << "----\n";
  for(const auto& row : c){
    for(const auto& val : row){
      cout << val << " ";
    }
    cout << "\n";
  }
  cout << "----\n";
}

inline int manhattan(int i, int j, int k, int l){return abs(i - k) + abs(j - l);}
inline int inv(int d){
  switch (d){
    case 0: return 2; // u -> d
    case 1: return 3; // l -> r
    case 2: return 0; // d -> u
    case 3: return 1; // r -> l
  }
  return -1;
}
constexpr int MOV_LIMIT = 45;
vvi board(4, vi(4));
int di[] = {-1,0, 1, 0};   // 0: up, 1: left, 2: down, 3:right
int dj[] = {0,-1, 0, 1};
char p[] = "ULDR";
ii miss_tile_idx;

vii goal = {
  ii(0, 0), 
  ii(0, 0), ii(0, 1), ii(0, 2), ii(0, 3),
  ii(1, 0), ii(1, 1), ii(1, 2), ii(1, 3),
  ii(2, 0), ii(2, 1), ii(2, 2), ii(2, 3),
  ii(3, 0), ii(3, 1), ii(3, 2), ii(3, 3)
};

int mov[MOV_LIMIT+1] = {-1}; // mov[i] es la dirección en el i-esimo movimiento (∈ {ULDR})

int sum(){
  int res = 0;
  forn(i, 4){
    forn(j, 4){
      if(board[i][j] == 0) continue;
      res += manhattan(i, j, goal[board[i][j]].first, goal[board[i][j]].second);
    }
  }
  return res;
}

// deep limited search
// explora hasta que f-cost = g(n) + h(n) > thres
int dls(int thres, int g, int miss_i, int miss_j){
  int h = sum();
  int f_cost = g + h;
  
  //print_container(board);

  if(h == 0) return 0;
  if(f_cost > thres) return f_cost;

  int min_t = numeric_limits<int>::max(); 
  
  forn(i, 4){
    if(g != 0 && (i == inv(mov[g-1]))) continue;

    // calcular nueva posición del tile vacío
    int ni = miss_i  + di[i];
    int nj = miss_j + dj[i];
    if(ni < 0 || ni >= 4 || nj < 0 || nj >= 4) continue; // fuera del limite

    swap(board[miss_i][miss_j], board[ni][nj]); // mover tile vacío
    mov[g] = i; // guardar dirección del movimiento

    int res = dls(thres, g+1, ni, nj);
    
    if(res == 0) return 0;
    min_t = min(min_t, res);

    swap(board[ni][nj], board[miss_i][miss_j]);
  }
  return min_t;
}

// llega a goal cuando sum(board) == 0
int ida_star(){
  int thres = sum();

  while(thres <= MOV_LIMIT){
    int new_t = dls(thres, 0, miss_tile_idx.first, miss_tile_idx.second);

    if(new_t == 0) return thres;
    if(new_t == numeric_limits<int>::max()) break;  // no hay solucion
    
    thres = new_t; 
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int n; cin >> n;
  forn(_,n){
    forn(i, 4){
      forn(j, 4){
        cin >> board[i][j];
        if(board[i][j] == 0) miss_tile_idx = ii(i, j);
      }
    }

    // solvability:
    // si sum(inv_i) + e (para todos los bloques i del tablero) es par entonces tiene solución
    // donde e es la fila del bloque vacio
    // inv_i = inversion de orden n: es cuando el cuadrado con numero i aparece antes de n numeros menores a i
    int inv =0;
    forn(e, 16){
      int i = e / 4;
      int j = e % 4;

      if(board[i][j] == 0 || board[i][j] == 1) continue;
      int elem = board[i][j];

      fordn(f, e+1, 16){
        int k = f/4;
        int l = f%4;

        if(board[k][l] == 0) continue;
        if(elem > board[k][l]) inv++;

      }
    }
    //cout << inv << "\n";

    if((inv + (miss_tile_idx.first+1)) % 2 == 1){
      cout << "This puzzle is not solvable.\n";
      continue;
    }

    int res = ida_star();
    if(res == -1){
      cout << "This puzzle is not solvable.\n";
    } else {
      // imprimir movimientos para llegar a la solución
      for(int i=0; i<res; i++){
        cout << p[mov[i]];
      }
      cout << "\n";
    }
  }

  return 0;
}