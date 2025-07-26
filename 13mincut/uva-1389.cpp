// Hard life
// max-density subgraph
#include <iostream>   // cout, cin
#include <algorithm>  // sort, binary_search, lower_bound, upper_bound
#include <cmath>      // sqrt, pow, abs, ceil, floor
#include <utility>    // pair, make_pair, swap, min, max
#include <iomanip>    // setprecision, fixed, showpoint
// Data structures
#include <vector>
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
typedef vector<vi>     vvi;
typedef vector<ii>     vii;
// Macros
#define forn(i,n)     for(int i=0; i<(int)(n); i++)
#define fordn(i,d,n)  for(int i=(int)(d); i<(int)(n); i++)
#define forall(i, c)  for(auto& i : (c))
#define pb push_back

#ifndef ONLINE_JUDGE
#include "dinics.h"
#else
/**
 * Author: Francisco Soulignac
 * 
 * Preparado para copy-paste en codigo de entrenamiento.  Para competencia, probablemente
 * convenga tener preparado un codigo compacto que sea facil de copiar.
 */

#ifndef DINICS_H
#define DINICS_H

#include <vector>
#include <deque>
#include <limits>
#include <cmath>
#include <iostream>
#include <functional>

typedef unsigned int uint;
typedef unsigned long ulong;

namespace dinics {
double EPS = 1e-9;  //modificar para ajustar

// Comparacion con tolerancia: especializacion para enteros

// Comparacion con tolerancia: especializacion para doubles
bool epsilon_equal(double a, double b) {return fabs(a-b) < EPS;}
bool epsilon_bigger(double a, double b) {return a > b+EPS;}
bool epsilon_smaller(double a, double b) {return a+EPS < b;}
inline bool epsilon_smaller_equal(double a, double b) {return a <= b+EPS;}
inline bool epsilon_bigger_equal(double a, double b) {return a+EPS >= b;}

namespace {

constexpr uint noparent = std::numeric_limits<uint>::max();

template<class T>
using digraph = vector<vector<T>>;

std::pair<uint, uint> null_edge = {std::numeric_limits<uint>::max(), std::numeric_limits<uint>::max()};

}

template<
    class FlowType = long long,
    typename std::enable_if<std::is_same<FlowType, long long>{} or std::is_same<FlowType, double>{}, bool>::type = true
>
class flowgraph {
public:
    using Vertex = ulong;
    using Capacity = FlowType;
    using Flow = FlowType;
    using Index = size_t;

    struct edge {
        Vertex      from,         //vertice del que parte la arista; solo por simetria y para simplificar, se puede sacar
                    to;           //vertice al que llega la arista
        Capacity    capacity;     //capacidad de la arista
        Flow        flow;         //flujo de la arista, el residual es capacity - flow
        Index       reverse;      //indice a la arista reversa en el grafo residual
    };
    using edge_handle = pair<Vertex, Index>;

private:
    digraph<edge> residual;        // grafo input con skew symmetry, i.e., grafo residual.

    inline edge& reverse(const edge& e) {
        return residual[e.to][e.reverse];
    }
    digraph<Index> find_level_graph(Vertex source) {
        digraph<Index> level_graph(residual.size());
        vector<uint> level(residual.size(), noparent);
        deque<Vertex> q(1, source);
        level[source] = 0;
        
        while(not q.empty()) {
            auto v = q.front(); q.pop_front();
            for(auto idx = 0u; idx < residual[v].size(); ++idx) {
                auto& e = residual[v][idx];
                if(epsilon_equal(e.flow, e.capacity)) continue;
                if(level[e.to] == noparent) {
                    q.push_back(e.to);
                    level[e.to] = level[v] + 1;
                }
                if(level[e.to] > level[v]) level_graph[v].push_back(idx);
            }
        }
        return level_graph;
    }
    Flow find_augmenting_path(digraph<Index>* level_graph, Vertex from, Vertex sink, vector<Vertex>* parent, vector<Index>* index) {
        auto& L = *level_graph;
        while(not L[from].empty()) {
            auto& e = residual[from][L[from].back()];
            auto success = e.capacity-e.flow;
            if(epsilon_bigger(success, 0) and e.to != sink) 
                success = min(success, find_augmenting_path(level_graph, e.to, sink, parent, index));
            if(epsilon_equal(success, 0)) {
                //arista saturada! o dead end!
                L[from].pop_back();
                continue;
            }
            //camino encontrado.  Guardamos la informacion y retornamos el flujo
            (*parent)[e.to] = e.from;
            (*index)[e.to] = L[from].back();
            return min(success, e.capacity - e.flow);
        }
        //no habia augmenting path
        return 0;
    }
    Flow find_blocking_flow(Vertex source, Vertex sink) {
        auto level_graph = find_level_graph(source);
        
        vector<Vertex> parent(residual.size(), noparent);
        vector<Index> index(residual.size(), 0);
        Flow ans=0, volume;
        
        while(volume = find_augmenting_path(&level_graph, source, sink, &parent, &index), epsilon_bigger(volume, 0)) {
            for(auto to = sink; parent[to] != noparent; to = parent[to]) {
                auto& e = residual[parent[to]][index[to]];
                e.flow += volume; 
                reverse(e).flow -= volume;
            }
            ans += volume;
        }
        return ans;
    }
    
    
public:
    flowgraph() = default;
    flowgraph(ulong n) :
        residual(n)    
    {}
    edge_handle add_edge(Vertex from, Vertex to, Capacity capacity) {
        if(epsilon_smaller_equal(capacity, 0)) 
            return {numeric_limits<Vertex>::max(), numeric_limits<Index>::max()};

        auto idxfrom = residual[from].size(), idxto = residual[to].size();
        residual[from].push_back(edge{from, to, capacity, 0, idxto});
        residual[to].push_back(edge{to, from, 0, 0, idxfrom});
        return {from, residual[from].size()-1};
    }
    Flow maxflow(Vertex source, Vertex sink) {
        Flow res = 0, step;        
        while(step = find_blocking_flow(source, sink), epsilon_bigger(step, 0)) 
            res += step;
        return res;
    }
    void flush() {
        for(auto& N : residual) 
        for(auto& e : N) e.flow = 0;
    }
    std::vector<bool> st_cut(Vertex source, Vertex sink) const {

        std::vector<bool> res(residual.size());
        std::function<void(Vertex)> dfs = [&](Vertex from) -> void {
            if(res[from]) return;

            res[from] = true;
            for(auto& e : residual[from])
            //if(epsilon_bigger(e.capacity, 0))
            if(epsilon_smaller(e.flow, e.capacity))
                dfs(e.to);
        };

        dfs(source);
        return res;
    }
    std::vector<edge> st_cut_edges(Vertex source, Vertex sink) {
        std::vector<edge> res;

        auto cut = st_cut(source, sink);
        for(auto& N : residual)
        for(auto& e : N)
        if(epsilon_bigger(e.capacity, 0))
        if(cut[e.from] and not cut[e.to])
            res.push_back(e);

        return res;
    }
    void print(ostream& out) {
        for(auto f = 0ul; f < residual.size(); ++f) {
            cout << f << ": ";
            for(auto e : residual[f]) {
                auto& rev = reverse(e);
                out << "(" << e.from << "," << e.to << "," << e.capacity << "," << e.flow << ") {" 
                    << rev.from << "," << rev.to << ","  << rev.capacity << "," << rev.flow << "}  -  ";
            }
            cout << endl;
        }
    }
    inline const digraph<edge>& get_residual() const {
        return residual;
    }
    inline const vector<edge>& get_residual_edges_of(Vertex v) const {
        return residual[v];
    }
    vector<edge> get_saturated_edges() const {
        vector<edge> res;
        for(auto& N : residual)
        for(auto& e : N)
        if(epsilon_bigger(e.capacity, 0))
        if(epsilon_equal(e.flow, e.capacity))
            res.push_back(e);
        return res;
    }
    vector<edge> get_saturated_edges_of(Vertex v) const {
        vector<edge> res;
        for(auto& e : residual[v])
        if(epsilon_bigger(e.capacity, 0))
        if(epsilon_equal(e.flow, e.capacity))
            res.push_back(e);
        return res;
    }
    inline const edge& get_edge(edge_handle e) const {
        return residual[e.first][e.second];
    }
};

template<class T>
std::ostream& operator<<(std::ostream& os, dinics::flowgraph<T> G) {
    G.print(os);
    return os;
}
}   // namespace dinics

#endif //DINICS_H
#endif

int n,m;

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  while(cin >> n >> m){
    if(n==0 && m==0) break;
    if(m==0){
      cout << "1\n1\n"; continue;
    }
    dinics::flowgraph<double>::Vertex source = n;
    dinics::flowgraph<double>::Vertex sink   = n+1;

    vi d(n); // degree
    vii edges(m);

    forn(_, m){
      int u, v; cin >> u >> v;
      u--; v--;
      edges[_] = {u, v};

      d[u]++;
      d[v]++;
    }
    
    double l = 0;
    double u = (double)m;
    vector<bool> V_res(n+2, false);
    int V_size_res = 0; 

    while(dinics::epsilon_bigger_equal(u-l, (1/(double)(n*n-n)))){
      double g = (u+l) / 2;

      // armo el grafo N
      dinics::flowgraph<double> N(n+2);
      forall(e, edges){
        N.add_edge(e.first, e.second, 1.0);
        N.add_edge(e.second, e.first, 1.0);
      }

      // para cada vertice v agregar (s,v) y (v,t)
      forn(v, n){
        N.add_edge(source, v, m);
        N.add_edge(v, sink, m+ 2*g - d[v]);
      }

      // calculo maxflow y particiono en mincut s-t
      N.maxflow(source, sink);
      vector<bool> is_in_V = N.st_cut(source, sink);

      int v_size = 0;
      forn(i, is_in_V.size()){
        if(is_in_V[i]) v_size++;
      }

      if(v_size == 1){
        // |V_1| = 0
        u = g;
      }else{
        l = g;
        V_res = is_in_V; // confio en el deep-copy
        V_size_res = v_size;
      }
    }

    if(V_size_res == 0){
      cout << "1\n1\n";
    }else{
      cout << V_size_res-1 << "\n";
      forn(v, n){
        if(V_res[v]) cout << v+1 << "\n";
      }
    }
    cout << "\n";
  }

  return 0;
}