#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> cd;

int const NMAX = 1 << 9;
double const PI2 = atan(1.0) * 8;
cd a[NMAX], b[NMAX];

// fft(src, num, stride, dst, nth root of unity)
void fft(cd *a, int n, int s, cd *b, cd unit) {
    if (n == 1) {
        *b = *a;
        return;
    }
    int nh = n / 2;
    fft(a    , nh, s * 2, b     , unit * unit);
    fft(a + s, nh, s * 2, b + nh, unit * unit);
    cd coef = 1;
    for (int i = 0; i < nh; ++i) {
        cd ofs = coef * b[i + nh];
        b[i + nh] = b[i] - ofs;
        b[i]      = b[i] + ofs;
        coef *= unit;
    }
}

int main() {
    // should be power of 2
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        a[i] = cd(t, 0);
    }

    // fft
    fft(a, n, 1, b, polar(1.0, -PI2 / n));
    for (int i = 0; i < n; ++i)
        cout << b[i] << ' ';
    cout << endl;

    // inverse fft
    fft(b, n, 1, a, polar(1.0, PI2 / n));
    for (int i = 0; i < n; ++i)
        a[i] /= n;
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}
