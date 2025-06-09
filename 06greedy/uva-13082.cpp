// UVA 13082 - High school assembly
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
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; cin >> tt;
  int t = 0;
  int n;
  while(t < tt){
    cin >> n;
    vi a(n);
    vi b(n);

    forn(i, n){
      cin >> a[i];
      b[i] = a[i];
    }

    // ordeno el array y busco en a los elementos que no hace falta mover
    sort(b.begin(), b.end());
    int id = 0;

    forn(i, n) if(b[id] == a[i]) id++;

    cout << "Case " << t + 1 << ": " << n - id << "\n";
    t++;
  }
  return 0;
}