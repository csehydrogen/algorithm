#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct HK {
    int n, m, dd;
    vector<vector<int> > g;
    vector<int> xy, yx, d;

    HK(int n, int m) : n(n), m(m), g(n), xy(n), yx(m), d(n) {}

    bool bfs() {
        queue<int> q;
        for(int x = 0; x < n; ++x) {
            if(xy[x] == -1) {
                d[x] = 0;
                q.push(x);
            } else {
                d[x] = -1;
            }
        }
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int y : g[x]) {
                if(yx[y] == -1) {
                    dd = d[x];
                    return true;
                }
                if(d[yx[y]] == -1) {
                    d[yx[y]] = d[x] + 1;
                    q.push(yx[y]);
                }
            }
        }
        return false;
    }

    bool dfs(int x) {
        for(int y : g[x]) {
            if((yx[y] == -1 && dd == d[x]) || (d[yx[y]] == d[x] + 1 && dfs(yx[y]))) {
                xy[x] = y;
                yx[y] = x;
                return true;
            }
        }
        d[x] = -1;
        return false;
    }

    int match() {
        fill(xy.begin(), xy.end(), -1);
        fill(yx.begin(), yx.end(), -1);
        int matched = 0;
        while(bfs())
            for(int x = 0; x < n; ++x)
                if(xy[x] == -1 && dfs(x))
                    ++matched;
        return matched;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    HK hk(n, m);
    int e;
    scanf("%d", &e);
    for(int i = 0; i < e; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        hk.g[x].push_back(y);
    }
    printf("%d", hk.match());
    return 0;
}
