#include <bits/stdc++.h>
using namespace std;
// #define NDEBUG
// #pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
// #pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")

#define Rn(a, n) a + 1, a + n + 1
auto _r0 = ([]{ return ios :: sync_with_stdio(0), 0; })();

typedef long long ll;
const int N = 13, STA = (1 << N + 1) + 5;
int n, k;
ll f[N][STA][N]; // rowId currentRow placedCount

namespace U {
  inline ll retR() {
    ll ret(0), c(0); bool neg(0); while (!isdigit(c = getchar())) neg = c == '-';
    ret = c - '0'; while (isdigit(c = getchar())) ret *= 10ll, ret += c - '0';
    return neg ? -ret : ret;
  }
  template <typename IntVal>
  inline void refR(IntVal v) { v = retR(); }
}; // Utils
auto R = U::retR;

inline int countOne(int x) {
  int res = 0;
  for (; x; x >>= 1) res += x & 1;
  return res;
}
inline bool motherfucking(int s) {
  for (int i=1; i<=n; i++) {
    if (s & (1 << i-1)) {
      if (s & (1 << i)) return true;
    }
  }
  return false;
}
inline bool canPlace(int ls, int cs) {
  for (int i=1; i<=n; i++) {
    if (cs & (1 << i-1)) {
      if (ls & (1 << i-1)) return false;
      if (ls & (1 << i)) return false;
      if (i > 1 && ls & (1 << i-2)) return false;
    }
  }
  return true;
}

int main() {
  n = R(); k = R();
  int S = 1 << n;
  f[0][0][0] = 1;
  for (int row=1; row<=n+1; ++row) {
    for (int placed=0; placed<=k; ++placed) {
      for (int s=0; s<S; ++s) {
        int remaining = placed - countOne(s);
        if (remaining < 0) continue;
        if (motherfucking(s)) continue;

        ll &F = f[row][s][placed];
        for (int l=0; l<S; ++l) {
          if (motherfucking(l)) continue;
          if (canPlace(l, s) && remaining - countOne(l) >= 0) {
            // printf("FROM: %d %d %d   TO: %d %d %d\n", row - 1, l, remaining, row, s, placed);
            F += f[row - 1][l][remaining];
          }
        }
      }
    }
  }
  cout << f[n+1][0][k] << endl;
  return 0;
}
