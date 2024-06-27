//
// Created by uyplayer on 2024-06-27.
//

#include <fstream>
#include "cryptology.h"


const std::string Cryptology::readPem() {

    std::string filePath  = std::string(PROJECT_DIR) + "/" + publicPemPath;
    std::ifstream file(filePath);
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    return content;

}


const std::string Cryptology::readPrivateKey() {

    std::string filePath  = std::string(PROJECT_DIR) + "/" + privateKeyPath;
    std::ifstream file(filePath);
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    return content;

}