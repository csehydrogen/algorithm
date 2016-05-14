#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

class LCA {
  // b = segment tree base
  int n, b;
  // t[b + i] = (level, #) of ith visited node in euler tour
  vector<pii> t;
  // r[i] = first visit of node i
  vector<int> r;
  // euler tour (graph, current, parent, height, visit index)
  int et(vector<vector<int>> &g, int x, int p = -1, int h = 0, int c = 0) {
    r[x] = c;
    t[b + c++] = pii(h, x);
    for (int y : g[x]) {
      if (y != p) {
        c = et(g, y, x, h + 1, c);
        t[b + c++] = pii(h, x);
      }
    }
    return c;
  }
  // query on segment tree
  int tq(int x, int y) {
    x += b; y += b;
    pii m(t[x]);
    while (x < y) {
      if (x % 2 == 1) m = min(m, t[x++]);
      if (y % 2 == 0) m = min(m, t[y--]);
      x /= 2; y /= 2;
    }
    if (x == y) m = min(m, t[x]);
    return m.second;
  }
public:
  // initialize with graph
  void init(vector<vector<int>> &g) {
    n = g.size();
    // euler tour visits 2n-1 nodes
    for (b = 1; b < 2 * n - 1; b *= 2);
    t = vector<pii>(b * 2);
    r = vector<int>(n);
    et(g, 0);
    // since it's min segment tree, INF padding is needed
    for (int i = b + 2 * n - 1; i < b * 2; ++i) {
      t[i] = pii(n, 0);
    }
    for (int i = b - 1; i > 0; --i) {
      t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
  }
  // query lca of x and y
  int q(int x, int y) {
    x = r[x]; y = r[y];
    return tq(min(x, y), max(x, y));
  }
};

int main() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a; --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  LCA lca;
  lca.init(g);

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int c, d;
    scanf("%d%d", &c, &d);
    --c; --d;
    printf("%d\n", lca.q(c, d) + 1);
  }

  return 0;
}
