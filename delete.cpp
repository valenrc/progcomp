#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#define ll long long
#define endl '\n'
#define vl vector<ll>
#define vvl vector<vl>


ll timer;
vvl adj, comps;
vl in_stack, low, dfsn;
stack<ll> stk;

void setup_tarjan(ll n){
  timer = 1;
  adj = vvl(n+2);
  comps.clear();
  while(stk.size()) stk.pop();
  in_stack = low = dfsn = vl(n+2);
}

void tarjan(ll node, ll par=-1){
  // stack of ancestors
  stk.push(node), in_stack[node] = 1, low[node] = dfsn[node] = timer++;

  for(auto next: adj[node]){
    if(!dfsn[next]){
      tarjan(next, node);
      low[node] = min(low[node], low[next]);
    } else if(in_stack[next]) {
      low[node] = min(low[node], dfsn[next]);
    }
  }

  // not head of SCC
  if(low[node] != dfsn[node]) return;

  comps.push_back({});
  ll x = -1;
  while(x!= node){
    x = stk.top(), stk.pop(), in_stack[x] = 0;
    comps.back().push_back(x);
  }
}

void print_set(set<string>& st){
  int z = st.size();
  cout << z << endl;

  string s;
  for(auto& t: st){
    s+=t, s+= " ";
  }

  s.pop_back();

  cout << s << endl;
}

int main(){
  ios ::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  while(cin >> n && n){
    cin.ignore();

    setup_tarjan(n);
    ll idc = 1;
    map<string, ll> id;
    map<ll, string> name;

    for(int i=1; i<=n; i++){
      string line, s;
      getline(cin, line);

      stringstream inp(line);
      vector<string>v;
      while(inp >> s) v.emplace_back(s);

      for(auto x:v) if(id.find(x) == id.end()){
        id[x] = idc;
        name[idc] = x;
        idc++;
      }

      set<ll> st;
      for(int j=1; j<v.size(); j++) st.insert(id[v[j]]);
      for(ll x:st) adj[id[v[0]]].emplace_back(x);
    }

    for(int i=1; i<=n; i++) if(!dfsn[i]) tarjan(i);

    set<ll> te;
    for(auto &v: comps){
      if(v.size() <= 1) continue;
      for(ll x:v){
        for(ll y:adj[x]) te.insert(y);
      }
    }

    set<string> ans;
    for(ll x:te){
      for(ll y:adj[x]) ans.insert(name[y]);
    }

    print_set(ans);
  }


}