// UVA 1229 - Sub-dictionary
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
#include <unordered_set>
#include <queue>
#include <stack>
#include <set>
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
void print_map_str(const unordered_map<string, unordered_set<string>>& m) {
  for (auto const& kv : m) {
    cout << kv.first << ": {";
    bool first = true;
    for (const auto& s : kv.second) {
      if (!first) cout << ", ";
      cout << s;
      first = false;
    }
    cout << "}\n";
  }
}

vi ids;
vi low;
vb on_stack;
stack<int> stk;
int timer_tarjan;
int scc_count;
vvi sccs_list;
vi node_to_scc_id;
int num_nodes;

void print_container(const vvi& c){
  for(const auto& row : c) {
    for(const auto& elem : row) {
      cout << elem << " ";
    }
    cout << "\n";
  }
}

int get_id(
  const string& s,
  unordered_map<string, int>& mapwrd,
  vector<string>& words,
  int& x,
  vvi& adj
){
  if(mapwrd.find(s) == mapwrd.end()){
    mapwrd[s] = x;
    words.pb(s);
    adj.pb(vi());
    return x++;
  }
  return mapwrd[s];
}

void dfs_tarjan(int u, const vvi& adj){
  stk.push(u);
  on_stack[u] = true;
  ids[u] = low[u] = timer_tarjan++;

  forall(v, adj[u]){
    if(ids[v] == -1){
      dfs_tarjan(v, adj);
      low[u] = min(low[u], low[v]);
    }else{
      if(on_stack[v]){
        low[u] = min(low[u], ids[v]);
      }
    }
  }

  if(ids[u] == low[u]){
    vi current_cc;
    while(true){
      int node_scc = stk.top();
      stk.pop();
      on_stack[node_scc] = false;

      current_cc.pb(node_scc);
      node_to_scc_id[node_scc] = scc_count;

      if(node_scc == u) break;
    }

    scc_count++;
    sccs_list.pb(current_cc);
  }
}

void scc_tarjan(const vvi& adj){
  ids.assign(num_nodes, -1);
  low.assign(num_nodes, 0);
  on_stack.assign(num_nodes, false);
  while(!stk.empty()) stk.pop();
  timer_tarjan = 0;
  scc_count = 0;
  sccs_list.clear();
  node_to_scc_id.assign(num_nodes, -1);

  forn(i, num_nodes){
    if(ids[i] == -1){
      dfs_tarjan(i, adj);
    }
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int tt; // cantidad de palabras en el diccionario
  while(cin >> tt && tt!=0){
    vvi adj;
    int x = 0;
    vector<string> words;
    unordered_map<string, int> mapwrd;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    forn(i, tt){
      string line;
      getline(cin, line);

      istringstream iss(line);
      string w, s;

      if(iss >> w){
        int w_id = get_id(w, mapwrd, words, x, adj);

        while(iss >> s){
          int s_id = get_id(s, mapwrd, words, x, adj);
          adj[w_id].pb(s_id);
        }
      }
    }

    num_nodes = x;
    
    // ordenar y eliminar repetidos
    for(int i=0; i<(int)(adj.size()); i++){
      sort(adj[i].begin(), adj[i].end());
      adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }

    // buscar SCCs con algoritmo de Tarjan
    // La respuesta sera la SCC con menor cantidad de palabras que cumpla con la condicion de ser sub-diccionario
    scc_tarjan(adj);

    set<ll> te;
    forall(scc, sccs_list){
      if(scc.size() <= 1) continue;

      forall(v, scc){
        forall(u, adj[v]) te.insert(u);
      }
    }

    set<string> ans;
    forall(v, te){
      forall(u, adj[v]) ans.insert(words[u]);
    }

    // convert set to vector and sort
    vector<string> result(ans.begin(), ans.end());
    sort(result.begin(), result.end());
    
    cout << result.size() << "\n";
    forall(s, result){
      cout << s << " ";
    }
    cout << "\n";

  }

  return 0;
}