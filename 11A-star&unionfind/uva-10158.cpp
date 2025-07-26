// War
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
typedef unsigned int uint;
typedef unsigned long ulong;
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
  cout << "\n";
}

#ifndef ONLINE_JUDGE
#include "dsu.h"
#else
#ifndef DSU_H
#define DSU_H

#include <vector>
#include <numeric>

namespace dsu {

/**
 * @brief Implementación de la estructura de datos Disjoint Set Union (DSU) o Union-Find.
 * 
 * Esta estructura mantiene una colección de conjuntos disjuntos y proporciona
 * operaciones para unirlos y determinar si dos elementos están en el mismo conjunto.
 * 
 * Utiliza las optimizaciones de "unión por tamaño" y "compresión de caminos".
 * - Unión por tamaño (Union by size): Al unir dos conjuntos, el árbol más pequeño
 *   se convierte en un subárbol del más grande. Esto mantiene los árboles planos.
 * - Compresión de caminos (Path compression): Al buscar el representante de un
 *   elemento, se hace que todos los nodos en el camino apunten directamente a la raíz.
 *   Esto acelera futuras búsquedas.
 * 
 * La complejidad de las operaciones find y unite es casi constante, O(α(n)), donde
 * α(n) es la inversa de la función de Ackermann, que es extremadamente lenta en crecer.
 */
class disjoint_set_union {
private:
  std::vector<int> parent;
  std::vector<int> sz; // sz[i] es el tamaño del conjunto si i es una raíz
  int num_sets;

public:
  /**
   * @brief Construye una estructura DSU con n elementos.
   * 
   * Inicialmente, cada elemento está en su propio conjunto de tamaño 1.
   * Los elementos se numeran de 0 a n-1.
   * @param n El número de elementos.
   */
  disjoint_set_union(int n) : parent(n), sz(n, 1), num_sets(n) {
    std::iota(parent.begin(), parent.end(), 0); // Asigna parent[i] = i
  }

  /**
   * @brief Encuentra el representante (raíz) del conjunto que contiene al elemento i.
   * 
   * Aplica la optimización de compresión de caminos.
   * @param i El elemento a buscar.
   * @return El representante del conjunto de i.
   */
  int find(int i) {
    if (parent[i] == i) {
      return i;
    }
    // Compresión de caminos: asigna el padre de i directamente a la raíz.
    return parent[i] = find(parent[i]);
  }

  /**
   * @brief Une los conjuntos que contienen a los elementos i y j.
   * 
   * Utiliza la optimización de unión por tamaño. Si ya están en el mismo
   * conjunto, no hace nada.
   * @param i Un elemento del primer conjunto.
   * @param j Un elemento del segundo conjunto.
   */
  void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      // Unión por tamaño: el más pequeño se une al más grande.
      if (sz[root_i] < sz[root_j]) {
        std::swap(root_i, root_j);
      }
      parent[root_j] = root_i;
      sz[root_i] += sz[root_j];
      num_sets--;
    }
  }

  /**
   * @brief Comprueba si dos elementos están en el mismo conjunto.
   * @param i Un elemento.
   * @param j Otro elemento.
   * @return true si i y j están en el mismo conjunto, false en caso contrario.
   */
  bool same_set(int i, int j) {
    return find(i) == find(j);
  }

  /**
   * @brief Devuelve el tamaño del conjunto que contiene al elemento i.
   * @param i El elemento.
   * @return El tamaño del conjunto.
   */
  int size(int i) {
    return sz[find(i)];
  }

  /**
  * @brief Devuelve el número de conjuntos disjuntos actuales.
  * @return El número de conjuntos.
  */
  int count() const {
    return num_sets;
  }
};

} // namespace dsu

#endif //DSU_H
#endif

int n;

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  cin >> n;

  // si find(i) = find(j) entonces i~j
  // si find(i) = find(j+n) entonces i*j
  dsu::disjoint_set_union dsu(2*n);

  // 1: setFriends; 2: setEnemies; 3: areFriends?; 4: areEnemies?
  int c, x, y;
  while((cin >> c >> x >> y) && (c || x || y)){
    switch(c){
      case 1:
        // falla si x y son enemigos
        if(dsu.same_set(x, y+n) || dsu.same_set(y, x+n)){
          cout << "-1\n";
          continue;
        }
        dsu.unite(x, y);
        dsu.unite(x + n, y + n);
      break;
      case 2:
        // falla si x y son amigos
        if(dsu.same_set(x, y) || dsu.same_set(y+n, x+n)){
          cout << "-1\n";
          continue;
        }
        dsu.unite(x, y+n);
        dsu.unite(x+n, y);
      break;
      case 3:
        if(dsu.same_set(x, y)) cout << "1\n"; else cout << "0\n";
      break;
      case 4:
        if(dsu.same_set(x, y+n) || dsu.same_set(y, x+n)) cout << "1\n";
        else cout << "0\n";
      break;
    }
  }

  return 0;
}