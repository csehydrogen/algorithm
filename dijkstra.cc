#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;
typedef pair<int, int> pii;
int const INF = 987654321;
int main() {
    int n, m, a, b, c, s, t;
    scanf("%d%d", &n, &m);
    vector<vector<pii> > g(n);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        --a; --b;
        g[a].push_back(pii(b, c));
    }
    scanf("%d%d", &s, &t);
    --s; --t;
    vector<int> d(n, INF);
    priority_queue<pii, vector<pii>, greater<pii> > q;
    d[s] = 0;
    q.push(pii(0, s));
    while (true) {
        int dist = q.top().first, here = q.top().second;
        if (here == t) break;
        q.pop();
        if (d[here] == dist) {
            for (auto &p : g[here]) {
                int there = p.first, cost = p.second;
                if (d[there] > dist + cost) {
                    d[there] = dist + cost;
                    q.push(pii(d[there], there));
                }
            }
        }
    }
    printf("%d", d[t]);
    return 0;
}
