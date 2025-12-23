#include <iostream>
#include <cstdlib>
#include <ctime>
#include "RSA.h"

bool isPrime(unsigned long long n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    for (unsigned long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

unsigned long long getPrime(unsigned long long min, unsigned long long max) {
    unsigned long long num = rand() % (max - min + 1) + min;
    while (isPrime(num) == false) {
        num = rand() % (max - min + 1) + min;
    }
    return num;
}

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    while (y != 0) {
        unsigned long long temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

unsigned long long lcm(unsigned long long x, unsigned long long y) {
    return (x * y) / gcd(x, y);
}

unsigned long long modInverse(unsigned long long e, unsigned long long lam) {
    for (unsigned long long d = 1; d < lam; d++) {
        if ((e * d) % lam == 1)
            return d;
    }
    return 0;
}

unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long n) {
    unsigned long long answer = 1;
    for (unsigned long long i = 0; i < exp; i++)
        answer = (answer * base) % n;
    return answer;
}

bool factorN(unsigned long long &p_bruteForced, unsigned long long &q_bruteForced, unsigned long long n) {  //bruteforcing encryption
    for (int i = UCHAR_MAX; i < USHRT_MAX; i++) { 
        if (n % i == 0) {                      
            unsigned long long tempVar = n / i;
            if (isPrime(i) && isPrime(tempVar)) {
                p_bruteForced = i;
                q_bruteForced = tempVar;
                return true;
            }
        }
    }
    return false;
}
