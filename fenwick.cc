#include <vector>
using namespace std;

/*
 * 1-based index
 */
template<typename T>
class Fenwick {
  int n;
  vector<T> a;
public:
  Fenwick(int _n) : n(_n), a(_n + 1) {}
  void update(int p, T x) { for (; p <= n; p += p & (-p)) a[p] += x; }
  T query(int p) { T s = 0; for (; p > 0; p -= p & (-p)) s += a[p]; return s; }
};

/*
 * Point update : a[p] += x
 * Range query : a[s] + ... + a[e]
 */
void update(int p, int x) {
  fw.update(p, x);
}
int query(int s, int e) {
  return fw.query(e) - fw.query(s - 1);
}

/*
 * Range update : a[s] += x, ..., a[e] += x
 * Point query : a[p]
 */
void update(int s, int e, int x) {
  fw.update(s, x);
  fw.update(e + 1, -x);
}
int query(int p) {
  return fw.query(p);
}

/*
 * Range update : a[s] += x, ..., a[e] += x
 * Range query : a[s] + ... + a[e]
 */
void update(int s, int e, int x) {
  fw0.update(s, x);
  fw0.update(e + 1, -x);
  fw1.update(s, x * (s - 1));
  fw1.update(e + 1, -x * e);
}
int query(int p) {
  return fw0.query(p) * p - fw1.query(p);
}
