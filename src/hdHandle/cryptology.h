#ifndef PDFGLIMPSE_CRYPTOLOGY_H
#define PDFGLIMPSE_CRYPTOLOGY_H

#include <iostream>
#include <string>

class Cryptology {
public:
    Cryptology() = default;

    static std::string readPem();

    static std::string readPrivateKey();

    std::string encrypt(const std::string &contecnt);
    std::string dycrypt(const std::string &contecnt);

private:
    static const std::string publicPemPath;
    static const std::string privateKeyPath;
};

#endif // PDFGLIMPSE_CRYPTOLOGY_H
