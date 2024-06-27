#include <QApplication>
#include "src/mainWindow/mainwindow.h"
#include <iostream>
#include <sha.h>
#include <hex.h>
#include <filters.h>


int main(int argc, char* argv[])
{

    std::cout << "Hello PDFGlimpse !" << std::endl;
    std::cout << "Project dir "<< PROJECT_DIR   << std::endl;

    std::string message = "Hello, PDFGlimpse!";
    std::string digest;
    CryptoPP::SHA256 hash;
    CryptoPP::StringSource(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
    std::cout << "Message: " << message << std::endl;
    std::cout << "SHA-256 Digest: " << digest << std::endl;

    QApplication app(argc, argv);
    mainWindow mainWindow;
    mainWindow.resize(1200, 900);
    mainWindow.show();
    return app.exec();
}
