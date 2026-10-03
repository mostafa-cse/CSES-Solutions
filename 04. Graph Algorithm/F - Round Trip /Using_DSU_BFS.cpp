#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
class Dsu {
    vector<int> arr;
    int num_sets;
    
public:
    Dsu(int size) {
        arr = vector<int>(size, -1);
        num_sets = size;
    }
    
    int merge(int a, int b) {
        a = get(a);
        b = get(b);
        
        if(a == b)
            return a;
        
        if(arr[a] > arr[b])
            swap(a, b);
        
        arr[a] += arr[b];
        arr[b] = a;
        num_sets--;
        return a;
    }
    
    int get(int a) {
        if(arr[a] < 0)
            return a;
        arr[a] = get(arr[a]);
        return get(arr[a]);
    }
    
    int get_size(int a) {
        return -arr[get(a)];
    }
    
    int get_num_sets() {
        return num_sets;
    }
};

 
int n, m;
Dsu dsu(100000);
vector<int> nodes[100000];
int dist[100000];
 
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    
    cin >> n >> m;
    int start = -1, end = 0;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if(dsu.get(a) == dsu.get(b)) {
            start = a;
            end = b;
            break;
        }
        dsu.merge(a, b);
        nodes[a].push_back(b);
        nodes[b].push_back(a);
    }
    
    if(start == -1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    
    queue<int> q;
    q.push(start);
    dist[start] = 1;
    
    while(dist[end] == 0) {
        int c = q.front();
        q.pop();
        
        for(int ne : nodes[c]) {
            if(dist[ne] == 0) {
                dist[ne] = dist[c] + 1;
                q.push(ne);
            }
        }
    }
    
    vector<int> r;
    int cdist = dist[end];
    int c = end;
    while(cdist > 0) {
        r.push_back(c);
        cdist--;
        for(int ne : nodes[c])
            if(dist[ne] == cdist)
                c = ne;
    }
    
    cout << r.size() + 1 << endl;
    for(int n : r)
        cout << n + 1 << " ";
    cout << end + 1 << endl;
    
    return 0;
}