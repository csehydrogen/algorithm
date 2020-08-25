#include <vector>
#include <algorithm>
using namespace std;
class MergeTree {
public:
  int n, d;
  vector<vector<int>> vs;
  vector<vector<int>> ss;
  void Build(vector<int> &a) {
    n = a.size();
    d = sizeof(int) * 8 - __builtin_clz(n - 1) + 1; // log2-like; e.g., 7 -> 4, 8 -> 4, 9 -> 5 ...
    vs = vector<vector<int>>(d, vector<int>(n));
    ss = vector<vector<int>>(d, vector<int>(n));
    BuildNode(0, n - 1, 0, a);
  }
  void BuildNode(int s, int e, int d, vector<int> &a) {
    if (s == e) {
      vs[d][s] = a[s];
      return;
    }
    int m = (s + e) / 2;
    BuildNode(s, m, d + 1, a);
    BuildNode(m + 1, e, d + 1, a);
    int l = s, r = m + 1, i = s;
    while (l <= m || r <= e) {
      if (r > e || (l <= m && vs[d + 1][l] < vs[d + 1][r])) {
        vs[d][i] = vs[d + 1][l];
        ss[d][i] = 0;
        ++i; ++l;
      } else {
        vs[d][i] = vs[d + 1][r];
        ss[d][i] = 1;
        ++i; ++r;
      }
    }
    for (int i = s + 1; i <= e; ++i) {
      ss[d][i] += ss[d][i - 1];
    }
  }
  // find largest index i s.t. l <= a[i] < r
  int Query1(int l, int r) {
    return QueryNode1(0, n - 1, 0, l, r);
  }
  int QueryNode1(int s, int e, int d, int l, int r) {
    if (s == e) {
      return s;
    }
    int li = lower_bound(vs[d].begin() + s, vs[d].begin() + e + 1, l) - vs[d].begin();
    if (li == e + 1) return e + 1;
    int ri = lower_bound(vs[d].begin() + li, vs[d].begin() + e + 1, r) - vs[d].begin();
    if (ri == li) return e + 1;
    int sw = ss[d][ri - 1] - (li == s ? 0 : ss[d][li - 1]);
    int m = (s + e) / 2;
    if (sw > 0) return QueryNode1(m + 1, e, d + 1, l, r);
    return QueryNode1(s, m, d + 1, l, r);
  }
  // count i s.t. i >= l and a[i] >= x
  int Query2(int l, int x) {
    return QueryNode2(0, n - 1, 0, l, x);
  }
  int QueryNode2(int s, int e, int d, int l, int x) {
    if (l <= s) {
      int xi = lower_bound(vs[d].begin() + s, vs[d].begin() + e + 1, x) - vs[d].begin();
      return e + 1 - xi;
    }
    if (e < l) return 0;
    int m = (s + e) / 2, r = 0;
    r += QueryNode2(s, m, d + 1, l, x);
    r += QueryNode2(m + 1, e, d + 1, l, x);
    return r;
  }
};
