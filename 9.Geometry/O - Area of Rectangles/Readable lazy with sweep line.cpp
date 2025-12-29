#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct MinCount {
    ll mn;     // minimum cover count in this node
    ll cnt;    // total length (not number of points) where that minimum occurs
};

static MinCount mergeNode(const MinCount& a, const MinCount& b) {
    if (a.mn == b.mn) return {a.mn, a.cnt + b.cnt};
    return (a.mn < b.mn ? a : b);
}

/*
  Segment tree over elementary y-intervals:
  After coordinate compression, the leaves represent intervals:
    [ys[i], ys[i+1]) for i = 0..m-2
  Each leaf has a "length" = ys[i+1]-ys[i].

  We maintain:
    - mn: minimum cover count in the segment
    - cnt: total length inside the segment that attains mn
  Then:
    uncovered_length = (mn==0 ? cnt : 0)
    covered_length   = total_length - uncovered_length
*/
struct LazySegTreeMinCount {
    int m;                    // number of y coordinates
    vector<int> ys;           // sorted unique y coords
    vector<MinCount> st;
    vector<ll> lazy;

    LazySegTreeMinCount(const vector<int>& ys_) : ys(ys_) {
        m = (int)ys.size();
        // We build on interval indices [0 .. m-2] (there are m-1 elementary intervals)
        int nLeaves = max(0, m - 1);
        st.assign(4 * max(1, nLeaves), {0, 0});
        lazy.assign(4 * max(1, nLeaves), 0);
        if (nLeaves > 0) build(1, 0, nLeaves - 1);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            ll len = (ll)ys[l + 1] - ys[l];
            st[id] = {0, len};
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        st[id] = mergeNode(st[id * 2], st[id * 2 + 1]);
    }

    void apply(int id, ll add) {
        st[id].mn += add;
        lazy[id] += add;
    }

    void push(int id) {
        if (lazy[id] == 0) return;
        apply(id * 2, lazy[id]);
        apply(id * 2 + 1, lazy[id]);
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(id, val);
            return;
        }
        push(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, ql, qr, val);
        update(id * 2 + 1, mid + 1, r, ql, qr, val);
        st[id] = mergeNode(st[id * 2], st[id * 2 + 1]);
    }

    // update elementary interval indices in [l, r] inclusive
    void update(int l, int r, ll val) {
        int nLeaves = m - 1;
        if (nLeaves <= 0 || l > r) return;
        update(1, 0, nLeaves - 1, l, r, val);
    }

    // uncovered length (cover count == 0) across the full y-range
    ll uncoveredLength() const {
        int nLeaves = m - 1;
        if (nLeaves <= 0) return 0;
        if (st[1].mn == 0) return st[1].cnt;
        return 0;
    }

    ll totalLength() const {
        if (m <= 1) return 0;
        return (ll)ys.back() - ys.front();
    }
};

struct Event {
    int x;
    int y1i, y2i; // indices in ys: [y1i, y2i) in real coordinates
    int delta;    // +1 add, -1 remove
    bool operator<(const Event& other) const { return x < other.x; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<array<int, 4>> rect(n);
    vector<int> ys;
    ys.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        rect[i] = {x1, y1, x2, y2};
        ys.push_back(y1);
        ys.push_back(y2);
    }

    // Coordinate compression on y (needed to avoid building up to 2e6 leaves). [web:5][web:8]
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getY = [&](int y) {
        return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin());
    };

    vector<Event> events;
    events.reserve(2 * n);
    for (auto &r : rect) {
        int x1 = r[0], y1 = r[1], x2 = r[2], y2 = r[3];
        int cy1 = getY(y1);
        int cy2 = getY(y2);
        // convert [cy1, cy2) in y-points to elementary interval indices:
        // leaf i represents [ys[i], ys[i+1]) => update i in [cy1, cy2-1]
        events.push_back({x1, cy1, cy2, +1});
        events.push_back({x2, cy1, cy2, -1});
    }
    sort(events.begin(), events.end());

    LazySegTreeMinCount st(ys);

    ll area = 0;
    for (int i = 0; i + 1 < (int)events.size(); i++) {
        // apply current event
        int y1i = events[i].y1i;
        int y2i = events[i].y2i;
        st.update(y1i, y2i - 1, events[i].delta);

        // area contribution until next x
        ll dx = (ll)events[i + 1].x - events[i].x;
        ll coveredY = st.totalLength() - st.uncoveredLength(); // min==0 trick [web:18]
        area += coveredY * dx;
    }

    cout << area << "\n";
    return 0;
}
