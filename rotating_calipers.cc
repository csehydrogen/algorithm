void RotatingCalipers(vector<Point> &p) {
    int n = p.size();
    int p0 = min_element(p.begin(), p.end()) - p.begin(), np0 = (p0 + 1) % n;
    int p1 = max_element(p.begin(), p.end()) - p.begin(), np1 = (p1 + 1) % n;
    for (int i = 0; i < n * 2; ++i) {
        ll det = (p[np1].second - p[p1].second) * (p[np0].first - p[p0].first)
               - (p[np0].second - p[p0].second) * (p[np1].first - p[p1].first);
        if (det >= 0) {
            p1 = np1;
            np1 = (np1 + 1) % n;
        }
        if (det <= 0) {
            p0 = np0;
            np0 = (np0 + 1) % n;
        }
        // p[p0] and p[p1] are antipodal, so do sth here
    }
}
