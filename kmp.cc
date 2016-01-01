#include <cstdio>
#include <vector>
using namespace std;
int const NMAX = 1000001;
char a[NMAX], b[NMAX];
int t[NMAX];

int main() {
    gets(a); gets(b);

    int pos = 2, cnd = 0;
    while (b[pos - 1]) {
        if (b[pos - 1] == b[cnd])
            t[pos++] = ++cnd;
        else if (cnd)
            cnd = t[cnd];
        else
            t[pos++] = 0;
    }

    int m = 0, i = 0;
    vector<int> ans;
    while (a[m + i]) {
        if (a[m + i] == b[i]) {
            if (!b[++i]) ans.push_back(m);
        } else if (i) {
            m += i - t[i];
            i = t[i];
        } else {
            ++m;
        }
    }

    printf("%lu\n", ans.size());
    for (int i : ans)
        printf("%d ", i + 1);

    return 0;
}
