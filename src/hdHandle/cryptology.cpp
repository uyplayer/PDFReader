#include "cryptology.h"
#include <aes.h>
#include <rsa.h>
#include <osrng.h>
#include <modes.h>
#include <filters.h>
#include <files.h>
#include <base64.h>

const std::string Cryptology::publicPemPath = "/resources/keys/public.pem";
const std::string Cryptology::privateKeyPath = "/resources/keys/private.key";


void Cryptology::loadPublicKey(const std::string &filename, CryptoPP::RSA::PublicKey &key) {
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file(filename.c_str(), true);
    file.TransferTo(queue);
    queue.MessageEnd();
    key.Load(queue);
}

void Cryptology::loadPrivateKey(const std::string &filename, CryptoPP::RSA::PrivateKey &key) {
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file(filename.c_str(), true);
    file.TransferTo(queue);
    queue.MessageEnd();
    key.Load(queue);
}

std::string Cryptology::encrypt(const std::string &plaintext) {
    using namespace CryptoPP;

    // 生成对称密钥和IV
    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(key, key.size());
    byte iv[AES::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

    std::string ciphertext;
    // 使用AES加密
    try {
        CBC_Mode<AES>::Encryption encryptor(key, key.size(), iv);
        StringSource ss(plaintext, true,
            new StreamTransformationFilter(encryptor,
                new StringSink(ciphertext)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // 使用RSA公钥加密对称密钥
    RSA::PublicKey publicKey;
    loadPublicKey(std::string(PROJECT_DIR) + publicPemPath, publicKey);
    std::string encryptedKey;
    try {
        RSAES_OAEP_SHA_Encryptor rsaEncryptor(publicKey);
        StringSource ss(key, key.size(), true,
            new PK_EncryptorFilter(prng, rsaEncryptor,
                new StringSink(encryptedKey)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // Base64编码
    std::string encodedIV, encodedCiphertext, encodedEncryptedKey;
    StringSource(iv, sizeof(iv), true,
        new Base64Encoder(
            new StringSink(encodedIV)
        )
    );
    StringSource(ciphertext, true,
        new Base64Encoder(
            new StringSink(encodedCiphertext)
        )
    );
    StringSource(encryptedKey, true,
        new Base64Encoder(
            new StringSink(encodedEncryptedKey)
        )
    );

    // 返回加密的对称密钥和加密的内容（可以拼接或分别返回）
    return encodedIV + encodedEncryptedKey + encodedCiphertext;
}

std::string Cryptology::decrypt(const std::string &encryptedContent) {
    using namespace CryptoPP;

    AutoSeededRandomPool prng;

    // 分离出 IV, encryptedKey 和 ciphertext
    std::string encodedIV = encryptedContent.substr(0, 24);
    std::string encodedEncryptedKey = encryptedContent.substr(24, 172);
    std::string encodedCiphertext = encryptedContent.substr(196);

    // 解码Base64
    std::string decodedIV, decodedCiphertext, decodedEncryptedKey;
    StringSource(encodedIV, true,
        new Base64Decoder(
            new StringSink(decodedIV)
        )
    );
    StringSource(encodedEncryptedKey, true,
        new Base64Decoder(
            new StringSink(decodedEncryptedKey)
        )
    );
    StringSource(encodedCiphertext, true,
        new Base64Decoder(
            new StringSink(decodedCiphertext)
        )
    );

    // 使用RSA私钥解密对称密钥
    RSA::PrivateKey privateKey;
    loadPrivateKey(std::string(PROJECT_DIR) + privateKeyPath, privateKey);
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    try {
        RSAES_OAEP_SHA_Decryptor rsaDecryptor(privateKey);
        StringSource ss(decodedEncryptedKey, true,
            new PK_DecryptorFilter(prng, rsaDecryptor,
                new ArraySink(key, key.size())
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // 使用AES解密
    std::string decryptedText;
    try {
        CBC_Mode<AES>::Decryption decryptor(key, key.size(), (byte*)decodedIV.data());
        StringSource ss(decodedCiphertext, true,
            new StreamTransformationFilter(decryptor,
                new StringSink(decryptedText)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return decryptedText;
}
