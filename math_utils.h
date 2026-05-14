#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Proje föyünde istenen algoritmaların prototipleri
long long gcd(long long a, long long b);
long long power_mod(long long taban, long long us, long long mod);
int is_prime(long long n);
long long mod_inverse(long long a, long long m, int *hata_var_mi);
long long euler_phi(long long n);

#endif