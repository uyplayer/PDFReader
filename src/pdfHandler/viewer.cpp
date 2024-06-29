//
// Created by uyplayer on 2024-06-08.
//

#include "viewer.h"
#include <QPdfBookmarkModel>


Viewer::Viewer(QWidget *parent) : QWidget(parent), pdfDocument(nullptr), pdfView(nullptr) {
    layout = new QVBoxLayout(this);
    pdfView = new QPdfView(this);
    layout->addWidget(pdfView);
    setLayout(layout);
    this->setStyleSheet("border: none;");
}

Viewer::~Viewer() {
    delete layout;
}

void Viewer::openPdfFile(QSplitter *splitter) {
    QString pdfPath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (pdfPath.isEmpty()) {
        std::cout << "No file selected" << std::endl;
    }else {
        // 设置布局
        splitter->show();
        pdfDocument = new QPdfDocument(this);
        pdfDocument->load(pdfPath);
        pdfView->setPageMode(QPdfView::PageMode::MultiPage);
        pdfView->setDocument(pdfDocument);
        pdfView->setZoomFactor(1);
        auto *contents = qobject_cast<Contents *>(splitter->widget(0));
        contents->loadPdfBookmarks(pdfDocument, pdfView, splitter);

    }

}

void Viewer::zoomInClicked() const {
    if (pdfView && pdfDocument) {
        pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
        qreal currentZoom = pdfView->zoomFactor();
        pdfView->setZoomFactor(currentZoom * 1.1);
    }
}

void Viewer::zoomOutClicked() const  {
    if (pdfView && pdfDocument) {
        pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
        qreal currentZoom = pdfView->zoomFactor();
        pdfView->setZoomFactor(currentZoom / 1.1);
    }
}