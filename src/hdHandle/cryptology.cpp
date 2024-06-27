#include <fstream>
#include "cryptology.h"


const std::string Cryptology::publicPemPath = "/resources/keys/public.pem";
const std::string Cryptology::privateKeyPath = "/resources/keys/private.key";

std::string Cryptology::readPem() {
    std::string filePath = std::string(PROJECT_DIR) + publicPemPath;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "打开文件失败: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

std::string Cryptology::readPrivateKey() {
    std::string filePath = std::string(PROJECT_DIR) + privateKeyPath;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "打开文件失败: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}
