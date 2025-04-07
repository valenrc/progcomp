///////////////////////
// UVA 11212 - Editing a book
using namespace std;

#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <cstdio>     // printf, scanf
#include <cstring>    // memset, strcpy, strcmp, strlen
#include <utility>    // pair, make_pair, swap, min, max
#include <sstream>    // stringstream, istringstream, ostringstream
#include <iomanip>    // setprecision, fixed, showpoint
#include <cstdint>    // int64_t, uint64_t

// Data structures
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>

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

// la operacion de cut/paste es, dada la lista L={p1,p2,...pn} un rango [i,j] y un entero k, se corta el rango [i,j] y se pega antes del paragraph k
// luego, busco el minimo de operaciones para que la lista quede ordenada. 
// cada nivel del arbol representa una operacion de cut/paste, por lo tanto los hijos de un nodo L son todas las listas que resultan de aplicar una operacion de cut/paste a L.
// el recorrido con bfs me garantiza el camino minimo :).

struct vector8_hash {
  // funcion de hash para vectores de uint8_t
  size_t operator()(const vector<uint8_t>& v) const {
    size_t hash = 0;
    for (uint8_t i : v) {
      hash = hash * 31 + i;
    }
    return hash;
  }
};

unordered_map<vector<uint8_t>, int, vector8_hash> distancefwd, distancebwd;

void bfs(queue<vector<uint8_t>>& q,
  unordered_map<vector<uint8_t>, int, vector8_hash>& distance,
  unordered_map<vector<uint8_t>, int, vector8_hash>& distance2,
  int n,
  int& found){
  
  int qsize = (int)(q.size());

  for(int it=1; it<=qsize; it++){
    vector<uint8_t> current = q.front();
    q.pop();

    // generar todos los estados hijos
    forn(i, n){
      fordn(j, i, n){
        vector<uint8_t> cut(current.begin()+i, current.begin()+j+1); // este es el corte [i,j]
        vector<uint8_t> aux = current; // copiar el estado actual
        aux.erase(aux.begin()+i, aux.begin()+j+1); // cortar el rango [i,j]

        forn(k, aux.size()){
          // hacer otra copia del vector aux para generar las permutaciones
          vector<uint8_t> nextperm = aux;
          nextperm.insert(nextperm.begin()+k, cut.begin(), cut.end()); // pegar el rango [i,j] en la posicion k

          if(distance2.find(nextperm) != distance2.end()){
            // meet in the middle
            found = distance[current] + distance2[nextperm] + 1;
            return;
          }

          // verificar si la nueva permutacion ya fue visitada
          if(distance.find(nextperm) == distance.end()){
            distance[nextperm] = distance[current] + 1;
            q.push(nextperm); // agregar el nuevo estado a la cola
          }
        }
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  int c = 0;
  while(cin >> n && n){
    uint8_t x;
    vector<uint8_t> paragraphs(n);
    vector<uint8_t> sorted(n);

    forn(i, n){
      cin >> x;
      paragraphs[i] = x;
    }

    sorted = paragraphs;
    sort(sorted.begin(), sorted.end());
    //print_container(paragraphs);
    //print_container(sorted); 

    // two-directional bfs
    queue<vector<uint8_t>> qfwd, qbwd;

    qfwd.push(paragraphs);
    qbwd.push(sorted);

    distancefwd[paragraphs] = 0;
    distancebwd[sorted] = 0;

    int found = -1;

    // chequear si el vector ya esta ordenado
    if(paragraphs == sorted){
      cout << "Case " << ++c << ": " << 0 << "\n";
      continue;
    }

    while(found == -1){
      bfs(qfwd, distancefwd, distancebwd, n, found);
      if(found != -1) break;
      bfs(qbwd, distancebwd, distancefwd, n, found);
    }

    if(found == -1) cout << "Case " << ++c << ": " << 0 << "\n";
    else cout << "Case " << ++c << ": " << found << "\n";

    // limpiar los mapas de distancias
    distancefwd.clear();
    distancebwd.clear();

  }

  return 0;
}