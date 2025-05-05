// UVa 1252 - Twenty Questions
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

int n,m;
vvi cnt; vvi dp;

// feat: features preguntadas
// answ: respuesta a la pregunta (0 o 1)
int solve(int feat, int answ){
  int matching_obj = cnt[feat][answ];
  // casos base
  if(matching_obj <= 1) return 0;
  if(matching_obj == 2) return 1;
  if(dp[feat][answ] != -1) return dp[feat][answ];
  
  int res = 1e9;

  forn(f, m){
    // iterar sobre las features no preguntadas
    if(feat & (1<<f)) continue;
    
    int new_feat = feat | (1<<f); // setear(1) la pregunta por f

    int answ_yes = answ | (1<<f); // respuesta afirmativa a la pregunta f
    int answ_no = answ;

    // busco el peor caso entre las dos respuestas posibles
    int worst_case = max(
      solve(new_feat, answ_yes),
      solve(new_feat, answ_no)
    );

    res = min(res, 1+worst_case);
  }

  return dp[feat][answ] = res;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> m >> n;
  while(n != 0 && m != 0){
    vi objects(n);

    forn(i, n) {
      string binary;
      cin >> binary;
      objects[i] = stoi(binary, nullptr, 2); // convertirlo a entero segun repr. en base 2
    }

    // precomputar para cada combinacion de (feat, answ) cuantos objetos cumplen
    cnt.assign((1<<m), vi((1<<m), 0));

    // s genera todos los bitmaps posibles de m bits
    for(int s=0; s < (1<<m); s++){
      forall(i, objects){
        int mask = s & i;
        cnt[s][mask]++;
      }
    }
    
    dp.assign((1<<m), vi((1<<m), -1));
    int res = solve(0,0);

    //print_container(objects);
    cout << res << "\n";
    cin >> m >> n;
  }

  return 0;
}