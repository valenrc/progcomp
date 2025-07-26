// ACORN
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

int acorn(vector<vector<int>> mat, int t, int h, int f){
    vector<vector<int>> dp(t, vector<int> (h, 0));
    vector<int> max_por_altura(h,-1);

    // Completar los demas casos base. Empiezo desde la máxima altura (h-1) y voy bajando.
    // Hay en total f casos base
    // Completo el primer nivel (altura h-1) - O(t)
    for(int i=0; i<t; i++){
        dp[i][h-1] = mat[i][h-1];

        if(dp[i][h-1] > max_por_altura[h-1]){
            max_por_altura[h-1] = dp[i][h-1]; 
        }
    }
    //Si f>h entonces solo puedo bajar en linea recta
    if(f>h){
        for(int j=h-2; j>=0; j--){
            for(int i=0; i<t; i++){
                dp[i][j] = dp[i][j+1] + mat[i][j];
            }
        }
        int res = dp[0][0];
        for(int r=0; r<t; r++){
            if(dp[r][0] > res){
                res = dp[r][0];
            }
        }
        return res;
    }
    // Completo los demas casos base empezando desde h-2 hasta h-f - O(f)
    for(int cb=2; cb<=f; cb++){
        //altura h-cb
        for(int i=0; i<t; i++){
            dp[i][h-cb] = dp[i][h-cb+1] + mat[i][h-cb];

            if(dp[i][h-cb] > max_por_altura[h-cb]){
                max_por_altura[h-cb] = dp[i][h-cb];
            }
        }
    }
    // Ahora utilizo dp para resolver los demas casos utilizando los casos anteriores
    for(int j=h-f-1; j>=0; j--){            //O(h*t^2)
        for(int i=0; i<t; i++){
            int max = dp[i][j+1];
            // dp[i][j] = max{dp[k][j+f], dp[i][j+1]} con 0<=k<t y k!=i
            /* for(int k=0; k<t; k++){
                if(k!=i){
                    if(dp[k][j+f] > max){
                        max = dp[k][j+f];
                    }
                }
            } */
            // Busco el maximo en la altura j+f y me fijo si es mayor a max, en ese caso reemplazo max 
            if(max_por_altura[j+f] > max){
                max = max_por_altura[j+f];
            }

            dp[i][j] = max + mat[i][j];

            if(dp[i][j] > max_por_altura[j]){
                max_por_altura[j] = dp[i][j];
            }
        }
        // Cuando termino tengo que actualizar max_por_altura[j] 
    }
    // El resultado es el valor maximo de todos los arboles para la altura 0
    // res = max{dp[0][j]} para 0<=j<t
    int res = dp[0][0];
    for(int r=0; r<t; r++){
        if(dp[r][0] > res){
            res = dp[r][0];
        }
    }
    return res;
}

int main(){
    int test_cases;
    cin >> test_cases;

    for(int test=0; test<test_cases; test++){
        int t, h, f;
        cin >> t >> h >> f;

        // Inicializo los parametros de entrada como una matriz mat : t x h
        vector<vector<int>> mat(t, vector<int> (h, 0));

        // Llenar la matriz con los datos de entrada
        for(int tree=0; tree < t; tree++){
            // Fila 'tree' de la matriz
            int cant_bellotas;
            cin >> cant_bellotas;
            for(int b=0; b<cant_bellotas; b++){
                // alt_b es la altura de la bellota correspondiente
                int alt_b;
                cin >> alt_b;

                mat[tree][alt_b-1] = mat[tree][alt_b-1] + 1;
            }
        }
        
        int res;
        res = acorn(mat, t, h, f);
        cout << res << endl;
    }
    return 0;
}