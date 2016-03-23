#include <unistd.h>
class FastIO {
    int fd, bufsz;
    char *buf, *cur, *end;
public:
    FastIO(int _fd = 0, int _bufsz = 1 << 20) : fd(_fd), bufsz(_bufsz) {
        buf = cur = end = new char[bufsz];
    }
    ~FastIO() {
        delete[] buf;
    }
    void readbuf() {
        cur = buf;
        end = buf + bufsz;
        while (true) {
            int res = read(fd, cur, end - cur);
            if (res == 0) break;
            if (res > 0)
                cur += res;
        }
        end = cur;
        cur = buf;
    }
    int readint() {
        while (true) {
            if (cur == end) readbuf();
            if (*cur >= '0') break;
            ++cur;
        }
        int ret = 0;
        while (true) {
            if (cur == end) readbuf();
            if (*cur < '0') break;
            ret = ret * 10 + *cur - '0';
            ++cur;
        }
        return ret;
    }
};
