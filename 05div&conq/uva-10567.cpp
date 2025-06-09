// UVA 10567 - Helping fill bates
// Binary Search
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
template<typename K, typename V>
void print_container(const unordered_map<K, vector<V>>& m) {
  for (auto const& kv : m) {
    cout << kv.first << ": ";
    for (auto const& idx : kv.second) {
      cout << idx << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  string s; int q;
  cin >> s;
  cin >> q;

  unordered_map<char, vector<int>> serial_nums;
  forn(i, s.size()){
    serial_nums[s[i]].push_back(i);
  }

  forn(i,q){
    int first = -1;
    int last = -1;
    bool found = true;
    string ss; cin >> ss;

    forall(c, ss){
      auto find = upper_bound(serial_nums[c].begin(), serial_nums[c].end(), last);

      if(*find <= last){
        cout << "Not matched\n";
        found = false;
        break;
      }else{
        last = *find;
        if(first == -1) first = last;
      }
    }

    if(found) cout << "Matched " << first << ' ' << last << '\n';
  }

  return 0;
}