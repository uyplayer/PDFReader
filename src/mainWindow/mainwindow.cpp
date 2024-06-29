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

    QIcon zoomInIcon(":/icon/icon/zoomin.png");
    zoom_in = new QPushButton(zoomInIcon, "", this);
    zoom_in->setFixedSize(30, 30);
    QIcon zoomOutIcon(":/icon/icon/zoomout.png");
    zoom_out = new QPushButton(zoomOutIcon, "", this);
    zoom_out->setFixedSize(30, 30);
    toolBar = new QToolBar(this);
    toolBar->setMovable(false);
    spacerWidgetTop = new QWidget(this);
    spacerWidgetTop->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolBar->addWidget(spacerWidgetTop);
    spacerWidgetTop->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolBar->addWidget(spacerWidgetTop);
    toolBar->addWidget(zoom_in);
    toolBar->addWidget(zoom_out);
    addToolBar(Qt::LeftToolBarArea, toolBar);




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
    // open pdf file
    connect(ui->OpenFile, &QAction::triggered, this, [=]() { viewer->openPdfFile(splitter); });
    this->setStyleSheet("border: 1px solid rgb(210, 210, 210);");
    // hardwar info
    hdInfoHandle = new HdInfoHandle();
    connect(ui->Generate, &QAction::triggered, this, [=]() { hdInfoHandle->generate(); });
    // zoom in and zoom out
    connect(zoom_in, &QPushButton::clicked, viewer, &Viewer::zoomInClicked);
    connect(zoom_out, &QPushButton::clicked, viewer, &Viewer::zoomOutClicked);


}

mainWindow::~mainWindow() {
    delete ui;
    delete viewer;
    delete contents;
    delete splitter;
    delete hdInfoHandle;
    delete zoom_in;
    delete zoom_out;
    delete toolBar;
    delete spacerWidgetTop;
}
