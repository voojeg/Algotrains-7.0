#include <iostream>
#include <vector>

const int NUMOFBITS = 64;
const unsigned long long ONES = (1ull << NUMOFBITS) - 1;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector x_y(n, std::vector(n, false));
    std::vector x_z(n, std::vector(n / NUMOFBITS + 1, 0ull));
    std::vector y_z(n, std::vector(n / NUMOFBITS + 1, 0ull));

    for (int i = 0; i < k; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        --x;
        --y;
        --z;
        x_y[x][y] = true;
        x_z[x][z / NUMOFBITS] |= (1ull << (z % NUMOFBITS));
        y_z[y][z / NUMOFBITS] |= (1ull << (z % NUMOFBITS));
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (x_y[i][j] == false) {
                for (size_t k = 0; k < n / NUMOFBITS; ++k) {
                    if ((x_z[i][k] | y_z[j][k]) != ONES) {
                        for (size_t l = 0; l < NUMOFBITS; ++l) {
                            if (((x_z[i][k] | y_z[j][k]) & (1ull << l)) == 0) {
                                std::cout << "NO\n";
                                std::cout << i + 1 << " " << j + 1 << " " << k * NUMOFBITS + l + 1 << '\n';
                                return 0;
                            }
                        }
                    }
                }
                int extra_bits = n % NUMOFBITS;
                if (extra_bits) {
                    const size_t idx = n / NUMOFBITS;
                    if ((x_z[i][idx] | y_z[j][idx]) != ((1ull << extra_bits) - 1)) {
                        for (size_t l = 0; l < extra_bits; ++l) {
                            if (((x_z[i][idx] | y_z[j][idx]) & (1ull << l)) == 0) {
                                std::cout << "NO\n";
                                std::cout << i + 1 << " " << j + 1 << " " << idx * NUMOFBITS + l + 1 << '\n';
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "YES\n";
    return 0;
}
