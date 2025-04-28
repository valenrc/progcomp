// UVa 11790 - murcia's skyline
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// longest increasing subsequence
int lis(vector<int> & s, vector<int> & t){
  // s : altura
  // t : anchos
  int n = s.size();
  // dp[i] = ancho de lis hasta i
  vector<int> dp(n,-1);

  dp[0] = t[0];

  // Busco el dp[k] (0 <= k < i)
  for(int i=1; i<n; i++){
    for(int k=0; k<i; k++){
      // si hay una lis hasta k y s[i] > s[k] entonces puedo agrandar +1 la subseq
      if(s[k] < s[i] && dp[k] + t[i] >= dp[i]) dp[i] = dp[k] + t[i];
    }
    // Si no pudo agregarse a ninguna subseq anterior, entonces lis[i] es t[i]
    if(dp[i] == -1) dp[i] = t[i];
  }

  // Busco el maximo en dp
  int res = *max_element(dp.begin(), dp.end());
  return res;
 
}

// Misma funcion que lis pero busca por orden decreciente.
int lds(vector<int> & s, vector<int> & t){
  // LIS : longest decreasing subsequence
  int n = s.size();
  // dp[i] = ancho de la lds hasta i
  vector<int> dp(n,-1);
  dp[0] = t[0];

  for(int i=1; i<n; i++){
    for(int k=0; k<i; k++){
      if(s[k] > s[i] && dp[k] + t[i] >= dp[i]) dp[i] = dp[k] + t[i];
    }

    if(dp[i] == -1) dp[i] = t[i];
  }

  int res = *max_element(dp.begin(), dp.end());
  return res;
 
}

int main(){
  int test_cases;
  cin >> test_cases;
    
  // Iteramos para cada test case
  for(int t=0; t<test_cases; t++){
    cout << "Case " << t+1 << ".";
    int cant_edificios;
    cin >> cant_edificios;

    vector<int> alturas(cant_edificios);
    vector<int> anchos(cant_edificios);

    // la primer linea es la altura de los edificios
    for(int i=0; i<cant_edificios; i++){
      int alt;
      cin >> alt;
      alturas[i] = alt;
    }

    // la segunda linea es el ancho de los edificios
    for(int j=0; j<cant_edificios; j++){
      int anch;
      cin >> anch;
      anchos[j] = anch;
    }

    // Buscar la lis en el vector de alturas
    int valLIS = lis(alturas, anchos);

    // Buscar la lds (longest decreasing subseq) en el vector de alturas
    int valLDS = lds(alturas, anchos);

    if(valLIS >= valLDS){
      cout << " Increasing (" << valLIS << ").";
      cout << " Decreasing (" << valLDS << ")." << endl;
    }else{
      cout << " Decreasing (" << valLDS << ").";
      cout << " Increasing (" << valLIS << ")." << endl;
    }
  }
  return 0;
}