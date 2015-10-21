#include <cstdio>

int const NMAX = 1 << 9, CUT = 1 << 4;
int a[NMAX], b[NMAX], ret[NMAX * 6];

void naive_mul(int *a, int *b, int *ret, int d) {
    int d2 = d * 2;
    for (int i = 0; i < d2; ++i)
        ret[i] = 0;
    for (int i = 0; i < d; ++i)
        for (int j = 0; j < d; ++j)
            ret[i + j] += a[i] * b[j];
}

/*
 * v----d----v                                       v-dh-v
 * -------------------------------------------------------------
 * | al * bl | ah * bh | as * bs |         |         | as | bs |
 * -------------------------------------------------------------
 * ^x0  ^xh  ^x1       ^x2
 */
void karatsuba(int *a, int *b, int *ret, int d) {
    if(d <= CUT) {
        naive_mul(a, b, ret, d);
        return;
    }

    int dh = d / 2;
    int *al = a;
    int *bl = b;
    int *ah = a + dh;
    int *bh = b + dh;
    int *as = ret + d * 5;
    int *bs = ret + d * 5 + dh;
    int *x0 = ret;
    int *x1 = ret + d;
    int *x2 = ret + d * 2;
    int *xh = ret + dh;

    for (int i = 0; i < dh; ++i) {
        as[i] = al[i] + ah[i];
        bs[i] = bl[i] + bh[i];
    }

    karatsuba(al, bl, x0, dh);
    karatsuba(ah, bh, x1, dh);
    karatsuba(as, bs, x2, dh);

    for (int i = 0; i < d; ++i) x2[i] -= x0[i] + x1[i];
    for (int i = 0; i < d; ++i) xh[i] += x2[i];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < n; ++i)
        scanf("%d", b + i);
    karatsuba(a, b, ret, NMAX);
    for (int i = 0; i < n * 2; ++i)
        printf("%d ", ret[i]);
    return 0;
}
