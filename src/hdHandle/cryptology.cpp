#include "cryptology.h"
#include <osrng.h>
#include <filters.h>
#include <files.h>
#include <base64.h>
#include <queue.h>

const std::string Cryptology::publicPemPath = "/resources/keys/public.pem";
const std::string Cryptology::privateKeyPath = "/resources/keys/private.key";

void Cryptology::loadPublicKey(CryptoPP::RSA::PublicKey &key) {
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file((std::string(PROJECT_DIR) + publicPemPath).c_str(), true);
    file.TransferTo(queue);
    queue.MessageEnd();
    key.Load(queue);
}

void Cryptology::loadPrivateKey(CryptoPP::RSA::PrivateKey &key) {
    CryptoPP::ByteQueue queue;
    CryptoPP::FileSource file((std::string(PROJECT_DIR) + privateKeyPath).c_str(), true);
    file.TransferTo(queue);
    queue.MessageEnd();
    key.Load(queue);
}

std::string Cryptology::encrypt(const std::string &plaintext) {
    using namespace CryptoPP;

    // 加载公钥
    RSA::PublicKey publicKey;
    loadPublicKey(publicKey);

    std::string ciphertext;
    AutoSeededRandomPool prng;

    // 使用RSA公钥加密
    try {
        RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
        StringSource ss(plaintext, true,
            new PK_EncryptorFilter(prng, encryptor,
                new StringSink(ciphertext)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    // Base64编码
    std::string encodedCiphertext;
    StringSource(ciphertext, true,
        new Base64Encoder(
            new StringSink(encodedCiphertext)
        )
    );

    return encodedCiphertext;
}

std::string Cryptology::decrypt(const std::string &ciphertext) {
    using namespace CryptoPP;

    // Base64解码
    std::string decodedCiphertext;
    StringSource(ciphertext, true,
        new Base64Decoder(
            new StringSink(decodedCiphertext)
        )
    );

    // 加载私钥
    RSA::PrivateKey privateKey;
    loadPrivateKey(privateKey);

    std::string decryptedText;
    AutoSeededRandomPool prng;

    // 使用RSA私钥解密
    try {
        RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
        StringSource ss(decodedCiphertext, true,
            new PK_DecryptorFilter(prng, decryptor,
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
