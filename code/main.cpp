#include "RSA.h"
#include <iostream>
#include <cstdlib>
#include <climits>

int main() {
    unsigned long long p, q, n, lambda, d, e, m, c;
    unsigned int seed = 0;

    std::cout << "Enter a seed: ";
    std::cin >> seed;
    srand(seed);

    p = getPrime(UCHAR_MAX, USHRT_MAX);
    q = getPrime(UCHAR_MAX, USHRT_MAX);

    std::cout << "\np: " << p << std::endl;
    std::cout << "q: " << q << std::endl;

    n = p * q;
    std::cout << "n: " << n << std::endl;

    lambda = lcm(p - 1, q - 1);
    std::cout << "lambda: " << lambda << std::endl;

    e = getPrime(2, lambda - 1);

    while (lambda % e == 0) {
        e = getPrime(2, lambda - 1);
    }
    std::cout << "e: " << e << std::endl;

    d = modInverse(e, lambda); 
    std::cout << "d: " << d << std::endl;
    std::cout << "Public key: " << "n = " << n << " e = " << e << std::endl;
    std::cout << "Private key: " << "n =  " << n << " d = " << d << std::endl;

    std::cout << "Enter a positive number less than " << n << ": ";
    std::cin >> m;
    while (m <= 0 || m > n) {
        std::cout << "INVALID! Enter another integer" << std::endl;
        std::cout << "Enter a positive number less than " << n << ": ";
        std::cin >> m;
    }
    c = modExp(m, e, n); 
    std::cout << "\nCipher: " << c << std::endl;
    d = modExp(c, d, n); 
    std::cout << "Decrypted Cipher: " << d << std::endl;

    unsigned long long p_bruteForced, q_bruteForced, lambda2, d_recovered, m_recovered;

    if (factorN(p_bruteForced, q_bruteForced, n)) {
        if (p_bruteForced && q_bruteForced) {

            lambda2 = lcm(p_bruteForced - 1, q_bruteForced - 1);
            d_recovered = modInverse(e, lambda2);
            m_recovered = modExp(c, d_recovered, n);

            std::cout << "P bruteforced: " << p_bruteForced << std::endl;
            std::cout << "Q bruteforced: " << q_bruteForced << std::endl;

            std::cout << "D recovered: " << d_recovered << std::endl;
            std::cout << "Decrypted: " << m_recovered << std::endl;
        }
    }


    return 0;

}


