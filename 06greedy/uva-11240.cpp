// UVA 11240 - Antimonotonicity
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

  forn(t, tt){
    int n; cin >> n;
    vi a(n);

    //n = 5;
    //a = {5, 2, 8, 1, 9};

    forn(i, n) cin >> a[i];

    int last = -1; int max_subseq = 0;
    bool op = true; // 1 = decreasing, 0 = increasing

    forn(i, n){
      if(op){
        if(a[i] > last){
          last = a[i];
          max_subseq++;
          op = false;
        }else{
          if(a[i] < last) last = a[i];
        }
      }else{
        if(a[i] < last){
          last = a[i];
          max_subseq++;
          op = true;
        }else{
          if(a[i] > last) last = a[i];
        }
      }
    }

    cout << max_subseq << "\n";
  }
  return 0;
}