// UVA 11935 - Through the desert
// BSTA (Binary Search The Answer)
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

/*
Eventos:
- 0: Fuel consumption
- 1: leak 
- 2: gas station
- 3: mechanic
- 4: end
*/
struct Event{
  int type;
  int km; // distancia en km del evento
  int fuel; // != 0 si type = "Fuel consumption"
};

const double EPS = 1e-9;

void print_events(const vector<Event>& events) {
    for (const auto& e : events) {
        cout << "km: " << e.km << ", type: " << e.type << ", fuel: " << e.fuel << endl;
    }
}

bool solve(double fuel, const vector<Event>& events){
  // simulacion del recorrido
  int km0 = 0; int n = events[0].fuel;
  int delta_k;
  int leak = 0;
  double fuel_res = fuel;

  forall(e, events){
    delta_k = e.km - km0; // distancia recorrida desde la dist. anterior
    km0 += delta_k;

    fuel_res -= (delta_k * n) / 100.0; // combustible consumido en el recorrido
    fuel_res -= delta_k * leak;

    if(fuel_res < 0) return false;

    if(e.type == 0) n = e.fuel;
    if(e.type == 1) leak++;
    if(e.type == 2) fuel_res = fuel;
    if(e.type == 3) leak = 0;
  }

  return (fuel_res >= 0);

}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int km, n;
  string s1, s2;

  while(cin >> km >> s1 >> s2 >> n && (km != 0 || n != 0)){
    vector<Event> events;
    events.pb({0, km, n});

    while(cin >> km >> s1){
      Event ev;
      ev.km = km; ev.fuel = 0;

      if(s1 == "Fuel"){
        cin >> s2 >> n;
        ev.type = 0;
        ev.fuel = n;
      }else if(s1 == "Leak"){
        ev.type = 1;
      }else if(s1 == "Gas"){
        cin >> s2; 
        ev.type = 2;
      }else if(s1 == "Mechanic"){
        ev.type = 3;
      }else if(s1 == "Goal"){
        ev.type = 4;
      }
      events.pb(ev);
      if(ev.type == 4) break;
    }
    //print_events(events);

    // busco la solucion con busqueda binaria
    double l = 0.0, r = 10000.0;
    while(fabs(l-r) > EPS){
      double m = (l+r)/2.0;
      bool res = solve(m, events);

      solve(m, events) ? r = m : l = m;
    }

    cout << fixed << setprecision(3) << r << endl;
  }

  return 0;
}