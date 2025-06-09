// ...existing code...
//
// Solución para CSES 1160 - Planet Queries II:
// El problema pide encontrar la distancia (número de saltos) desde un planeta 'u' a un planeta 'v'.
// El grafo de planetas es funcional: cada planeta tiene exactamente un destino.
// Esto implica que desde cualquier planeta, eventualmente se llega a un ciclo.
//
// La solución se basa en dos fases principales de precalculo:
// 1. Binary Lifting:
//    - Se precalcula una tabla `up[k][i]` que almacena el 2^k-ésimo sucesor del planeta `i`.
//    - `up[0][i]` es el destino directo de `i`.
//    - `up[k][i] = up[k-1][up[k-1][i]]`.
//    - Esto permite encontrar el M-ésimo sucesor de un nodo en O(log M) tiempo.
//
// 2. Precalculo de Información de Ciclos y Caminos:
//    - Se realiza un recorrido (similar a DFS) por todos los nodos para identificar componentes.
//    - Para cada nodo `i`, se determina:
//        - `cycle_id[i]`: Un ID único para el ciclo al que `i` pertenece o lleva.
//        - `dist_to_cycle[i]`: Distancia desde `i` hasta el primer nodo del ciclo. (0 si `i` está en el ciclo).
//        - `cycle_head_node[i]`: Un nodo representante del ciclo de `i`.
//        - `pos_in_cycle[i]`: Si `i` está en un ciclo, su posición (0 a L-1) relativa al `cycle_head_node`.
//        - `len_of_cycle[i]`: La longitud del ciclo de `i`.
//    - Este precalculo se hace en O(N).
//
// Procesamiento de Consultas (u, v):
// 1. Verificación Inicial: Si `u` y `v` no pertenecen al mismo sistema de ciclo (`cycle_id[u] != cycle_id[v]`),
//    la respuesta es -1.
// 2. Caso 1: `v` está en el camino directo desde `u` hacia el ciclo de `u`.
//    - Esto ocurre si `dist_to_cycle[u] >= dist_to_cycle[v]`.
//    - La distancia candidata es `k = dist_to_cycle[u] - dist_to_cycle[v]`.
//    - Se verifica si `jump(u, k) == v`. Si es así, `k` es la respuesta.
// 3. Caso 2: `u` debe alcanzar su ciclo y luego viajar por el ciclo hasta `v`.
//    - Esto se considera si el Caso 1 no dio resultado y `v` está en el ciclo (`dist_to_cycle[v] == 0`).
//    - Se calcula `u_on_cycle = jump(u, dist_to_cycle[u])`, el nodo donde `u` entra al ciclo.
//    - Se calcula la distancia en el ciclo desde `pos_in_cycle[u_on_cycle]` hasta `pos_in_cycle[v]`.
//    - La respuesta es `dist_to_cycle[u] + (distancia en el ciclo)`.
// 4. Si ninguno de los casos anteriores aplica, la respuesta es -1.
//
// Complejidad: O(N log N) para precalculo de binary lifting, O(N) para precalculo de ciclos,
// y O(Q log N) para las consultas.
//