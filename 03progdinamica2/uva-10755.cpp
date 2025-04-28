// UVa 10755 - Garbage Heap
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
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);cin.tie(0);
  int tt; cin >> tt;
  int a,b,c;
  forn(_,tt){
    cin >> a >> b >> c;
    vector< vector< vector<ll> > > h(a, vector< vector<ll> >(b, vector<ll>(c, 0))); // paralelepipedo de a*b*c

    // computo los prefijos usando inclusion-exclusion
    // h[i][j][k] : suma de todos los valores de h[0][0][0] a h[i][j][k]
    forn(i,a){
      forn(j,b){
        forn(k,c) cin >> h[i][j][k];

        forn(k,c){
          if(i > 0) h[i][j][k] += h[i-1][j][k];
          if(j > 0) h[i][j][k] += h[i][j-1][k];
          if(k > 0) h[i][j][k] += h[i][j][k-1];
          if(i > 0 && j > 0) h[i][j][k] -= h[i-1][j-1][k];
          if(i > 0 && k > 0) h[i][j][k] -= h[i-1][j][k-1];
          if(j > 0 && k > 0) h[i][j][k] -= h[i][j-1][k-1];
          if(i > 0 && j > 0 && k > 0) h[i][j][k] += h[i-1][j-1][k-1];
        }
      }
    }

    ll best = h[a-1][b-1][c-1]; // suma de todo el paralelepipedo

    // obtengo las sumas de los sub-paralelepipedos
    forn(x1,a){
      fordn(x2,x1,a){
        forn(y1,b){
          fordn(y2,y1,b){
            forn(z1,c){
              fordn(z2,z1,c){
                ll sum=h[x2][y2][z2];
                if(x1 > 0) sum -= h[x1-1][y2][z2];
                if(y1 > 0) sum -= h[x2][y1-1][z2];
                if(z1 > 0) sum -= h[x2][y2][z1-1];
                if(x1 > 0 && y1 > 0) sum+= h[x1-1][y1-1][z2];
                if(x1 > 0 && z1 > 0) sum += h[x1-1][y2][z1-1];
                if(y1 > 0 && z1 > 0) sum += h[x2][y1-1][z1-1];
                if(x1>0 && y1>0 && z1>0) sum -= h[x1-1][y1-1][z1-1];

                if(sum > best) best = sum;
              }
            }
          }
        }
      }
    }
    // no estoy para nada orgulloso de esta solucion
    // quiero hacerlo con kadane 3D pero bueno, skill issue
    cout << best << "\n";
    if(_ < tt-1) cout << "\n";
  }
  return 0;
}