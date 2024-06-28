#ifndef PDFGLIMPSE_CRYPTOLOGY_H
#define PDFGLIMPSE_CRYPTOLOGY_H

#include <iostream>
#include <string>
#include <rsa.h>

class Cryptology {
public:
    Cryptology() = default;

    static std::string encrypt(const std::string &plaintext);
    static std::string decrypt(const std::string &ciphertext);

private:
    static const std::string publicPemPath;
    static const std::string privateKeyPath;

    static void loadPublicKey(CryptoPP::RSA::PublicKey &key);
    static void loadPrivateKey(CryptoPP::RSA::PrivateKey &key);
};

#endif // PDFGLIMPSE_CRYPTOLOGY_H
