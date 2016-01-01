#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

vector<Point> ConvexHull(vector<Point> &p) {
    swap(*p.begin(), *min_element(p.begin(), p.end()));
    auto ccw = [](Point const &a, Point const &b, Point const &c) {
        return a.first * b.second + b.first * c.second + c.first * a.second
             - b.first * a.second - c.first * b.second - a.first * c.second;
    };
    sort(p.begin() + 1, p.end(), [&](Point const &a, Point const &b) {
        return ccw(*p.begin(), a, b) > 0;
    });
    vector<Point> ch(p.begin(), p.begin() + 2);
    for (auto it = p.begin() + 2; it != p.end(); ++it) {
        while (ch.size() >= 2 && ccw(*(ch.end() - 2), *(ch.end() - 1), *it) <= 0)
            ch.pop_back();
        ch.push_back(*it);
    }
    while (ch.size() >= 2 && ccw(*(ch.end() - 2), *(ch.end() - 1), *p.begin()) <= 0)
        ch.pop_back();
    return ch;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<Point> p;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        p.push_back(Point(x, y));
    }
    vector<Point> ch = ConvexHull(p);
    printf("%lu", ch.size());
    return 0;
}
