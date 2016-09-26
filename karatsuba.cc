#include <vector>
#include <algorithm>
using namespace std;
template <typename T>
class Karatsuba {
  typedef typename vector<T>::iterator vTi;
  int cut;
  void convolve_naive(vTi a, vTi b, vTi c, int n) {
    int n2 = n * 2;
    for (int i = 0; i < n2; ++i)
      c[i] = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        c[i + j] += a[i] * b[j];
  }
  /*
   * v----d----v                                       v-dh-v
   * -------------------------------------------------------------
   * | al * bl | ah * bh | as * bs |         |         | as | bs |
   * -------------------------------------------------------------
   * ^x0  ^xh  ^x1       ^x2
   */
  void karatsuba(vTi a, vTi b, vTi c, int n) {
    if(n <= cut) {
      convolve_naive(a, b, c, n);
      return;
    }
    int nh = n / 2;
    vTi al = a, ah = a + nh, as = c + nh * 10;
    vTi bl = b, bh = b + nh, bs = c + nh * 11;
    vTi x0 = c, x1 = c + n, x2 = c + n * 2, xh = c + nh;
    for (int i = 0; i < nh; ++i) {
      as[i] = al[i] + ah[i];
      bs[i] = bl[i] + bh[i];
    }
    karatsuba(al, bl, x0, nh);
    karatsuba(ah, bh, x1, nh);
    karatsuba(as, bs, x2, nh);
    for (int i = 0; i < n; ++i) x2[i] -= x0[i] + x1[i];
    for (int i = 0; i < n; ++i) xh[i] += x2[i];
  }
public:
  Karatsuba(int _cut = 1 << 5) : cut(_cut) {}
  vector<T> convolve(vector<T> &_a, vector<T> &_b) {
    vector<T> a = _a, b = _b, c;
    int sz = max(a.size(), b.size()), sz2;
    for (sz2 = 1; sz2 < sz; sz2 *= 2);
    a.resize(sz2); b.resize(sz2); c.resize(sz2 * 6);
    karatsuba(a.begin(), b.begin(), c.begin(), sz2);
    c.resize(_a.size() + _b.size() - 1);
    return c;
  }
};

#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  Karatsuba<int> kt;
  vector<int> c = kt.convolve(a, b);
  for (int x : c) printf("%d ", x);
  return 0;
}
