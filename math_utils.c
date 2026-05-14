/*
 * Ad , Soyad: Batuhan Ceyhan , Yunus Emre Karaslan
 * Numara: 434368 , 434391
 */

#include "math_utils.h"

// EBOB - O(log(min(a,b))) karmaşıklığında Öklid Algoritması
long long gcd(long long a, long long b) {
    long long gecici;
    while (b != 0) {
        gecici = b;
        b = a % b; 
        a = gecici;
    }
    return a;
}

// İkili Üs Alma (Binary Exponentiation) - O(log b) karmaşıklığında
long long power_mod(long long taban, long long us, long long mod) {
    long long sonuc = 1;
    taban = taban % mod; 
    
    while (us > 0) {
        if (us % 2 == 1) { 
            sonuc = (sonuc * taban) % mod;
        }
        us = us / 2; 
        taban = (taban * taban) % mod; 
    }
    return sonuc;
}

// Asallık Testi - O(sqrt(N)) karmaşıklığında
int is_prime(long long n) {
    if (n <= 1) return 0; 
    if (n == 2 || n == 3) return 1; 
    if (n % 2 == 0 || n % 3 == 0) return 0; 
    
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0; 
        }
    }
    return 1;
}

// Modüler Ters (Genişletilmiş Öklid) - O(log(min(a,m)))
long long mod_inverse(long long a, long long m, int *hata_var_mi) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1 || gcd(a, m) != 1) {
        *hata_var_mi = 1; 
        return 0;
    }

    *hata_var_mi = 0;
    while (a > 1) {
        q = a / m; 
        t = m;
        m = a % m; 
        a = t;
        
        t = x0;
        x0 = x1 - q * x0; 
        x1 = t;
    }

    if (x1 < 0) {
        x1 = (x1 % m0 + m0) % m0;
    }
    return x1;
}

// Euler Totient (PHI) - O(sqrt(N))
long long euler_phi(long long n) {
    long long sonuc = n;
    
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p; 
            }
            sonuc = sonuc - (sonuc / p); 
        }
    }
    if (n > 1) {
        sonuc = sonuc - (sonuc / n);
    }
    return sonuc;
}