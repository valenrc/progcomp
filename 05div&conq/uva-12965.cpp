// UVA 12965 - Angry bids
// D&C Binary Search
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
  forn(_, tt){
    int p, c; cin >> p >> c;

    vi prod(p); vi cons(c);

    forn(i, p) cin >> prod[i];
    forn(i, c) cin >> cons[i];

    sort(prod.begin(), prod.end());
    sort(cons.begin(), cons.end());

    // inicializo un estado inicial con bid=0
    int ang_min = p; 
    int res = 0; // el precio final (bid)

    forn(i, p){
      int val = prod[i];
      int it = upper_bound(cons.begin(), cons.end(), val) - cons.begin();
      
      int angry = it + (p-1-i);
      if (angry < ang_min){
        ang_min = angry;
        res = val;
      } else if (angry == ang_min){
        res = min(res, val);
      }
    }

    forn(i, c){
      int val = cons[i];
      int it = upper_bound(prod.begin(), prod.end(), val) - prod.begin();

      int angry = i + (p-it);
      if (angry < ang_min){
        ang_min = angry;
        res = val;
      } else if (angry == ang_min){
        res = min(res, val);
      }
    }

    cout << res << " " << ang_min << "\n";
  }

  return 0;
}