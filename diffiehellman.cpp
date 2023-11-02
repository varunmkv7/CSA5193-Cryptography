#include <stdio.h>
#include <math.h>

long long mod_pow(long long a, long long b, long long p) {
    if (b == 0) return 1;
    long long t = mod_pow(a, b / 2, p);
    t = (t * t) % p;
    if (b % 2 == 1) t = (t * a) % p;
    return t;
}

int main() {
    long long g, p, a, b, A, B, secretA, secretB;

    p = 23;
    g = 5;
    a = 6;
    b = 15; 
    A = mod_pow(g, a, p);
    B = mod_pow(g, b, p);
    secretA = mod_pow(B, a, p);
    secretB = mod_pow(A, b, p);

    printf("Shared Secret Key for Alice: %lld\n", secretA);
    printf("Shared Secret Key for Bob: %lld\n", secretB);

    return 0;
}
