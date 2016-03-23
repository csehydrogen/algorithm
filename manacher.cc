#include <cstdio>
#include <algorithm>
using namespace std;
int a[4000], d[4000];
int main() {
    int n;
    scanf("%d", &n);
    n *= 2;
    for (int i = 0; i < n; i += 2)
        scanf("%d", &a[i]);
    int r = -1, p;
    for (int i = 0; i < n; ++i) {
        if (i <= r)
            d[i] = min(r - i, d[p * 2 - i]);
        while (i - d[i] > 0 && a[i - d[i] - 1] == a[i + d[i] + 1])
            ++d[i];
        if (r < i + d[i]) {
            r = i + d[i];
            p = i;
        }
    }
    return 0;
}
