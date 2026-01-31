#include "Utils.hpp"          

long long Utils::nCr(int n, int r) {
    // Heuristic to avoid large multiplications (Avoid overflow)
    // TODO: Look for a BigInteger analogous in cpp 
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;
    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

