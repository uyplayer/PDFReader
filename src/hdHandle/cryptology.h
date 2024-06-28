#ifndef PDFGLIMPSE_CRYPTOLOGY_H
#define PDFGLIMPSE_CRYPTOLOGY_H

#include <iostream>
#include <string>
#include "rsa.h"

class Cryptology {
public:
    Cryptology() = default;

    // 加密和解密
    std::string encrypt(const std::string &content);
    std::string decrypt(const std::string &encryptedContent);

private:
    static const std::string publicPemPath;
    static const std::string privateKeyPath;

    void loadPublicKey(const std::string &filename, CryptoPP::RSA::PublicKey &key);
    void loadPrivateKey(const std::string &filename, CryptoPP::RSA::PrivateKey &key);
};

#endif // PDFGLIMPSE_CRYPTOLOGY_H
