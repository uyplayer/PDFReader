//
// Created by uyplayer on 2024-06-01.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"


mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow), splitter(nullptr) {
    ui->setupUi(this);
    this->setWindowTitle("PDF Viewer");
    this->setWindowIcon(QIcon(":/icon/icon/app_books.png"));
    contents = new Contents(this);
    viewer = new Viewer(this);
    splitter = new QSplitter(Qt::Orientation::Horizontal, this);
    splitter->setOpaqueResize(false);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setStyleSheet("QSplitter:handle{background-color:grey}");
    splitter->addWidget(contents);
    splitter->addWidget(viewer);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    splitter->hide();
    setCentralWidget(splitter);
    connect(ui->OpenFile, &QAction::triggered, this, [=]() { viewer->openPdfFile(splitter); });
    this->setStyleSheet("border: 1px solid rgb(210, 210, 210);");
    hdInfoHandle = new HdInfoHandle();
    connect(ui->Generate, &QAction::triggered, this, [=]() { hdInfoHandle->generate(); });


}

mainWindow::~mainWindow() {
    delete ui;
    delete viewer;
    delete contents;
    delete splitter;
    delete hdInfoHandle;
}
