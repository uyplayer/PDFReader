#include <QApplication>
#include "src/mainWindow/mainwindow.h"
#include <iostream>
#include <sha.h>
#include <hex.h>
#include <filters.h>

int main(int argc, char* argv[])
{

    std::cout << "Hello PDFGlimpse !" << std::endl;
    std::cout << "Project dir "<< Project_Dir   << std::endl;
    std::string input = "Hello, World!";
    std::string output;

    CryptoPP::SHA256 hash;
    CryptoPP::StringSource ss(input, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(output)
            )
        )
    );

    std::cout << "SHA-256 Hash: " << output << std::endl;

    QApplication app(argc, argv);
    mainWindow mainWindow;
    mainWindow.resize(1200, 900);
    mainWindow.show();
    return app.exec();
}
