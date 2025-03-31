// Libreria con implementaciones y algoritmos de grafos escrita en C++
// C++98 
#ifndef GRAPH_H
#define GRAPH_H
#include "../comp.h"

// Lista de adyacencia con pesos
// Un grafo es un vector de vectores de pares de enteros
// Donde cada par representa el indice de otro nodo en el grafo y el peso de la arista
// Puede ser dirigido o no dirigido
// graph = vector<vector<pair<int,int>>> = vector<vii>
typedef vector<vii> AL;

/**
 * DFS - Depth First Search
 * @param u nodo inicial
 * @param visited vector de booleanos para marcar los nodos visitados
 * @param g grafo representado como lista de adyacencia
 */
void dfs(int u, vector<bool>& visited, AL& g){
  visited[u] = true;
  // -- Procesar el vertice de alguna manera
  cout << u << " ";

  forn(i,g[u].size()){
    int v = g[u][i].first; 
    if(!visited[v]){
      dfs(v, visited, g);
    }
  }
}

/**
 * BFS - Breadth First Search
 * @param u nodo inicial
 * @param visited vector de booleanos para marcar los nodos visitados
 * @param distances distancias desde el nodo inicial (-1: INF)
 * @param g grafo representado como lista de adyacencia
 */
void bfs(int s, vector<int>& distances, AL& g){
  distances[s] = 0;

  queue<int> q;
  q.push(s);

  while(!q.empty()){
    int u = q.front();
    q.pop();

    // -- Procesar el vertice de alguna manera
    cout << u << " ";
    
    forn(i,g[u].size()){
      int v = g[u][i].first;
      if(distances[v] == -1){
        distances[v] = distances[u] + 1;
        q.push(v);
      }
    }
  }
}

/**
 * Busca componentes conexas (Grafo no dirigido)
 * @param u nodo inicial
 * @param visited vector de booleanos para marcar los nodos visitados
 * @param g grafo representado como lista de adyacencia
 */
void connected_components(int u, vector<bool>& visited, AL& g){
  int numCC = 0;  // cantidad de componentes conexas

  forn(u,g.size()){
    if(!visited[u]){
      numCC++;
      // -- Procesar el vertice de la Comp. Conexa de alguna manera
      dfs(u, visited, g);
      cout << endl;
    }
}

// Cycle Check (Directed Graph)
// Busca ciclos de al menos 3 arista en un grafo dirigido

// Lista de adyacencia sin pesos
// Se puede representar con vector<vii> donde el peso de cada arista es 1 o 0.
#endif