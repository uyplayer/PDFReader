#include <QApplication>
#include "src/mainWindow/mainwindow.h"
#include "src/hdHandle/HdInfoHandle.h"
#include <iostream>
#include <sha.h>
#include <hex.h>
#include <filters.h>


int main(int argc, char* argv[])
{

    std::cout << "Hello PDFGlimpse !" << std::endl;
    std::cout << "Project dir "<< PROJECT_DIR   << std::endl;
    // 形成硬件信息
//    HdInfoHandle::generate();
    QApplication app(argc, argv);
    mainWindow mainWindow;
    mainWindow.resize(1200, 900);
    mainWindow.show();
    return app.exec();
}
