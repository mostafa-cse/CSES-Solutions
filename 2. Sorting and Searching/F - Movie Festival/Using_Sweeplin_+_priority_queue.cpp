#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<pair<int, int>> I(n);
    for (int i = 0; i < n; i++) {
        cin >> I[i].first >> I[i].second;
    }

    vector<pair<int,int>> events;
    for(auto &iv: I) {
        events.emplace_back(iv.first, +iv.second);  // start event encodes end in value
        events.emplace_back(iv.second, -iv.second); // end event
    }
    sort(events.begin(), events.end(), [](auto &a, auto &b){
        if(a.first!=b.first) return a.first<b.first;
        return a.second < b.second; // end (-) before start (+)
    });
    priority_queue<int, vector<int>, greater<int>> pq;
    int cnt=0;
    for(auto &e: events) {
        if(e.second>0) {
            pq.push(e.second);
        } else {
            int endt = -e.second;
            if(!pq.empty() && pq.top()==endt) {
                cnt++;
                pq.pop();
            }
        }
    }
    cout << cnt;
    return 0;
}