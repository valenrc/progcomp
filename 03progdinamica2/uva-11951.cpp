// Area UVA-11951
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <limits>    // INT_MAX, INT_MIN, LONG_MAX, LONG_MIN
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

int INF = 1000001; //10^6+1

int main(){
  int tt; //test cases
  cin >> tt;
  forn(t, tt){
    int n,m,K;
    cin >> n >> m >> K;
    vector<vector<int>> v(n, vector<int>(m,0));
    //int vmax = -INF;

    forn(j,n){
      forn(k,m){
        cin >> v[j][k];
        //v[j][k] *= -1;
        //if(vmax < v[j][k]) vmax = v[j][k];
      }
      // paso para preprocessing
      // a[j][k] sum de la submatriz de 0,0 a j,k
      forn(k,m){
        if(k>0) v[j][k] += v[j][k-1];
        if(j>0) v[j][k] += v[j-1][k];
        if(j>0 && k>0) v[j][k] -= v[j-1][k-1];
      }
    }

    /*
    forn(j,n){
      forn(k,m){
        cout << v[j][k] << " "; 
      }
      cout << endl;
    }
    */

    int maxarea = 0;
    int minprice = 0;
    forn(f1,n){
      fordn(f2,f1,n){
        forn(c1,m){
          fordn(c2,c1,m){
            //cout << f1 << " " << f2 << " " << c1 << " " << c2 << endl;
            int area = (f2-f1+1)*(c2-c1+1);
            int sum = v[f2][c2];
            if(f1>0) sum -= v[f1-1][c2];
            if(c1>0) sum -= v[f2][c1-1];
            if(f1>0 && c1>0) sum += v[f1-1][c1-1];
            
            if(sum <= K){
              if(area > maxarea){
                maxarea = area;
                minprice = sum;
              }else if(area == maxarea){
                if(sum < minprice){
                  minprice = sum;
                }
              }
            }
          }
        }
      }
    }
    cout << "Case #" << t+1 << ": " << maxarea << " " << minprice << "\n";
  }
  return 0;
}