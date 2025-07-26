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
 * 
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