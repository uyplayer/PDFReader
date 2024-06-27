#include <QApplication>
#include "src/mainWindow/mainwindow.h"
#include <iostream>


int main(int argc, char* argv[])
{

    std::cout << "Hello PDFGlimpse !" << std::endl;
    std::cout << "Project dir "<< PROJECT_DIR   << std::endl;

    QApplication app(argc, argv);
    mainWindow mainWindow;
    mainWindow.resize(1200, 900);
    mainWindow.show();
    return app.exec();
}
