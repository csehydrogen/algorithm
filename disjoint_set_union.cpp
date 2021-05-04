#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
 
using namespace std;

struct DSU {
	vector<int> S, rank;

	DSU(int n) {
		S.resize(n); rank.resize(n,1);
		for(int i=0 ; i<n ; i++) S[i]=i;
	}

	int find_root(int x) {
		if(S[x]==x) return x;
		else return S[x]=find_root(S[x]);
	}

	void union_set(int _x, int _y) {
		int x = find_root(_x), y = find_root(_y);

		if(x==y) return;
		if(rank[x]>rank[y]) swap(x,y);
		if(rank[x]==rank[y]) rank[y]++;

		S[x] = y;
		return;
	}
};
 
int main() {
	// https://www.acmicpc.net/problem/1717
 
    int n,m;
    cin>>n>>m;
 
    DSU dsu(n+1);
 
    for(int i=0 ; i<m ; i++) {
        int type, a, b;
        scanf("%d %d %d", &type, &a, &b);
 
        if(type==0) dsu.union_set(a,b);
        else {
            if(dsu.find_root(a) == dsu.find_root(b)) printf("YES\n");
            else printf("NO\n");
        }
    }
 
    return 0;
}