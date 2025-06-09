// UVA 12321 - Gas stations
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
void print_container(const vector<pair<int,int>>& c) {
  for (auto& p : c) {
    cout << "(" << p.first << "," << p.second << ") ";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int l, g;
  int x, r;

  while(cin >> l >> g && (l || g)){
    vii station(g);
    forn(i, g){
      cin >> x >> r;
      station[i].first  = max(0, x - r); // sin pasarse de 0 
      station[i].second = min(l, x + r); // sin pasarse de l
    }
    sort(station.begin(), station.end(), [](const ii& a, const ii& b) {
      // ordenar por leftmost ascendente y rightmost descendente en caso de empate
      if (a.first == b.first) return a.second > b.second; 
      else return a.first < b.first;
    });
    
    // greedy (interval covering)
    int res = 0;
    int covered = 0;
    bool possible = true;
    for(int i = 0; (i < g)&&possible  ; i++){
      if(covered > l) break;
      if(station[i].second <= covered) continue; // intervalo cubierto por el anterior

      if(station[i].first <= covered){
        // busco el intervalo que cubra lo mas a la derecha posible
        int max_i = i;
        int max_r = station[i].second;

        for(int j = i+1; (j < g) && (station[j].first <= covered); j++){
          if(station[j].second > station[max_i].second){
            max_i = j;
            max_r = station[j].second;
          }
        }

        res++;
        covered = max_r;
        i = max_i; // me salto los intervalos cubiertos
      }else{
        possible = false; 
      }
    }

    cout << (possible && (covered >= l) ? g-res : -1) << "\n";

  }

  return 0;
}