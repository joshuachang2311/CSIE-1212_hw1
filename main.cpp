#include "BigInt.h"

#include <iostream>
#include <algorithm>

namespace ben_birdland {
template <typename IntegerType>
IntegerType GreatestCommonDivisor(IntegerType n, IntegerType m) {
    while (true) {
        if (n < m) {
            std::swap(n, m);
        }

        if (m == 0) {
            return n;
        } else {
            n = n % m;
        }
    }
}
}

int main() {
    std::string a, b;
    std::cin >> a >> b;
    ben_birdland::BigInt n(a), m(b);
    std::cout << ben_birdland::GreatestCommonDivisor(n, m);

    return 0;
}
