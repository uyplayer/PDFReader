//
// Created by uyplayer on 2024-06-27.
#ifndef PDFGLIMPSE_CRYPTOLOGY_H
#define PDFGLIMPSE_CRYPTOLOGY_H

#include <iostream>
#include <string>


class Cryptology {
public:
    Cryptology() = default;
private:
     const std::string publicPemPath{"/resources/keys/public.pem"};
     const std::string privateKeyPath{"/resources/keys/private.key"};

     const std::string readPem();
     const std::string readPrivateKey();
};



#endif //PDFGLIMPSE_CRYPTOLOGY_H

