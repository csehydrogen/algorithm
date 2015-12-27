#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class SuffixArray {
public:
    class Comparator {
        char *s;
    public:
        Comparator(char *_s) : s(_s) {}
        bool operator () (int x, int y) { return s[x] < s[y]; }
    };

    vector<int> sa;
    vector<int> lcp;

    SuffixArray(int n, char *s) {
        vector<int> g(n + 1); // group
        vector<int> g2(n); // auxiliary
        vector<int> gpos(n); // position for bucket sort
        sa = vector<int>(n); // suffix array
        vector<int> sa2(n); // auxiliary
        lcp = vector<int>(n); // lcp array

        // init sa, g, and gpos
        for (int i = 0; i < n; ++i) sa[i] = i;
        sort(sa.begin(), sa.end(), Comparator(s));
        int gn = 0;
        g[sa[0]] = gn; gpos[gn] = 0;
        for (int i = 1; i < n; ++i) {
            if (s[sa[i - 1]] != s[sa[i]])
                gpos[++gn] = i;
            g[sa[i]] = gn;
        }
        // this prevents index go beyond n, during comparison
        g[n] = -1;

        // condition g[sa[n - 1]] < n - 1 greatly reduces running time
        for (int d = 1; g[sa[n - 1]] < n - 1; d *= 2) {
            // characters beyond n - d have nothing to append, so just put it
            for (int i = n - d; i < n; ++i)
                sa2[gpos[g[i]]++] = i;
            // otherwise, append [sa[i], sa[i] + d) to [sa[i] - d, sa[i])
            for (int i = 0; i < n; ++i)
                if (sa[i] >= d)
                    sa2[gpos[g[sa[i] - d]]++] = sa[i] - d;

            // copying sa2 to sa, update new group number on g2, and init gpos
            gn = 0;
            sa[0] = sa2[0]; g2[sa[0]] = gn; gpos[gn] = 0;
            for (int i = 1; i < n; ++i) {
                if (g[sa2[i - 1]] != g[sa2[i]] || g[sa2[i - 1] + d] != g[sa2[i] + d])
                    gpos[++gn] = i;
                sa[i] = sa2[i];
                g2[sa[i]] = gn;
            }
            // copying g2 to g
            for (int i = 0; i < n; ++i)
                g[i] = g2[i];
        }

        // lcp construct
        for (int i = 0, k = 0; i < n; ++i) {
            if (g[i] > 0) {
                for (int j = sa[g[i] - 1]; s[i + k] == s[j + k]; ++k);
                lcp[g[i]] = k;
                // next substring will have at least k - 1 length CP
                // so don't need to reset, just decrease by 1
                if (k) --k;
            }
        }
    }
};

char s[1001];
int main() {
    scanf("%s", s);
    int n = strlen(s);
    SuffixArray sa(n, s);
    for (int i = 0; i < n; ++i)
        printf("%s\n", s + sa.sa[i]);
    return 0;
}
