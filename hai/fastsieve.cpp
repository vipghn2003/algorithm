#include <bits/stdc++.h>
#include <chrono>
using namespace std;
 
namespace segmented_sieve_wheel {
const int MAX = 1000000000LL;
const int WHEEL = 3 * 5 * 7 * 11 * 13;
const int N_SMALL_PRIMES = 6536;
const int SIEVE_SPAN = WHEEL * 64;
const int SIEVE_SIZE = SIEVE_SPAN / 128 + 1;
const long long SUM_PRIMES = 24739512092254535LL;
 
uint64_t ONES[64];
int small_primes[N_SMALL_PRIMES];
 
 
uint64_t si[SIEVE_SIZE];
 
uint64_t pattern[WHEEL];
 
inline void mark(uint64_t* s, int o) { s[o >> 6] |= ONES[o & 63]; }
inline int test(uint64_t* s, int o) { return (s[o >> 6] & ONES[o & 63]) == 0; }
 
vector<int>primes;
 
void update_sieve(int offset) {
    for (int i = 0, k; i < SIEVE_SIZE; i += k) {
        k = std::min(WHEEL, SIEVE_SIZE - i);
        memcpy(si + i, pattern, sizeof(*pattern) * k);
    }
 
    if (offset == 0) {
        si[0] |= ONES[0];
        si[0] &= ~(ONES[1] | ONES[2] | ONES[3] | ONES[5] | ONES[6]);
    }
 
    for (int i = 0; i < N_SMALL_PRIMES; ++i) {
        int j = small_primes[i] * small_primes[i];
        if (j > offset + SIEVE_SPAN - 1) break;
        if (j > offset) j = (j - offset) >> 1;
        else {
            j = small_primes[i] - offset % small_primes[i];
            if ((j & 1) == 0) j += small_primes[i];
            j >>= 1;
        }
        while (j < SIEVE_SPAN / 2) {
            mark(si, j);
            j += small_primes[i];
        }
    }
}
 
void sieve() {
 
    for (int i = 0; i < 64; ++i) ONES[i] = 1ULL << i;
 
    for (int i = 3; i < 256; i += 2) {
        if (test(si, i >> 1)) {
            for (int j = i*i / 2; j < 32768; j += i) mark(si, j);
        }
    }
 
    int m = 0;
    for (int i = 8; i < 32768; ++i) {
        if (test(si, i)) small_primes[m++] = i*2 + 1;
    }
    assert(m == N_SMALL_PRIMES);
 
    for (int i = 1; i < WHEEL * 64; i += 3) mark(pattern, i);
    for (int i = 2; i < WHEEL * 64; i += 5) mark(pattern, i);
    for (int i = 3; i < WHEEL * 64; i += 7) mark(pattern, i);
    for (int i = 5; i < WHEEL * 64; i += 11) mark(pattern, i);
    for (int i = 6; i < WHEEL * 64; i += 13) mark(pattern, i);
 
    long long sum_primes = 2;
    for (int offset = 0; offset < MAX; offset += SIEVE_SPAN) {
        update_sieve(offset);
 
        for (uint32_t j = 0; j < SIEVE_SIZE; j++){
            uint64_t x = ~si[j];
            while (x){
                uint32_t p = offset + (j << 7) + (__builtin_ctzll(x) << 1) + 1;
                if (p > offset + SIEVE_SPAN - 1) break;
                if (p <= MAX) {
                    sum_primes += p;
                    primes.push_back(p);
                }
                x ^= (-x & x);
            }
        }
    }
    assert(sum_primes == SUM_PRIMES);
}
}
// }}}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    segmented_sieve_wheel::sieve();
    vector<int> a = segmented_sieve_wheel::primes;
}
 