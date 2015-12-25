/* Extended Euclidean Algorithm
 * find x, y s.t. ax+by=gcd(a,b)
 */
void eea(int a, int b, int &x, int &y) {
    int r[3] = {a, b}, s[3] = {1, 0}, t[3] = {0, 1};
    while (r[1]) {
        int q = r[0] / r[1];
        r[2] = r[0] - q * r[1];
        s[2] = s[0] - q * s[1];
        t[2] = t[0] - q * t[1];;
        r[0] = r[1]; r[1] = r[2];
        s[0] = s[1]; s[1] = s[2];
        t[0] = t[1]; t[1] = t[2];
    }
    x = s[0]; y = t[0];
}

/* Chinese Remainder Theorem
 * find x s.t. x = a[i] mod b[i]
 */
int crt(int *a, int *b, int n) {
    int B = 1;
    for (int i = 0; i < n; ++i)
        B *= b[i];
    int x = 0;
    for (int i = 0; i < n; ++i) {
        int c, d;
        eea(b[i], B / b[i], c, d);
        x = (x + B / b[i] * d * a[i]) % B;
    }
    x = (x + B) % B;
    return x;
}
