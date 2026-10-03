#include<bits/stdc++.h>
using namespace std ;
const int N = 5e5+10 ;
int n , id[N] ;
char c[N] , t[N] ;
int son[N][30] , idx , cnt[N] , ne[N] ;
int pos[N] , len[N] ;
int insert(char *c){
    int p = 0 ;
    for(int i = 0 ; c[i] ; i++){
        if (!son[p][c[i] - 'a'])
            son[p][c[i] - 'a'] = ++idx;
        p = son[p][c[i]-'a'] ;
    }
    return cnt[p]++ , p ;
}
void build(){
    queue<int> q ;
    for(int i = 0 ; i < 26 ; i++){
        if (son[0][i]) {
            q.push(son[0][i]);
        }
    }
    while(q.size()){
        int u = q.front() ; q.pop() ;
        for(int i = 0 ; i < 26 ; i++){
            int v = son[u][i] ;
            if(v) ne[v] = son[ne[u]][i] , q.push(v) ;
            else son[u][i] = son[ne[u]][i] ;
        }
    }
}
void query(char *c){
    for(int i = 0 , k = 0 ; c[k] ; k++){
        i = son[i][c[k]-'a'] ;
        for(int j = i ; j && pos[j] == -1 ; j = ne[j]){
            pos[j] = k ;
        }
    }
}
int main(){
    memset(pos , -1 , sizeof(pos)) ;
    cin >> c >> n ;
    for(int i = 1 ; i <= n ; i++){
        cin >> t ; id[i] = insert(t) , len[i] = strlen(t) ;
    }
    build() ;
    query(c) ;
    for(int i = 1 ; i <= n ; i++){
        int tmp = pos[id[i]] ;
        printf("%d\n", (~tmp ? tmp+2-len[i] : -1)) ;
    }
    return 0 ;
}
