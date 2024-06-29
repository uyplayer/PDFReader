//
// Created by uyplayer on 2024-06-08.
//

#include "contents.h"
#include <iostream>

Contents::Contents(QWidget *parent)
        : QWidget(parent), treeView(new QTreeView(this)), layout(new QVBoxLayout(this)), pdfDocument(nullptr),
          pdfView(nullptr), pageNavigator(nullptr) {
    layout->addWidget(treeView);
    setLayout(layout);
    this->setStyleSheet("border: none;");
    pageNavigator = new QPdfPageNavigator(pdfDocument);
    connect(treeView, &QTreeView::clicked, this, &Contents::onBookmarkClicked);
}

Contents::~Contents() {
    delete pdfDocument;
    delete pageNavigator;
    delete model;
    delete treeView;
    delete layout;
    delete pdfView;
}

void Contents::loadPdfBookmarks(QPdfDocument *pdfDocument, QPdfView *pdfView, const QSplitter *splitter) {
    this->pdfDocument = pdfDocument;
    this->pdfView = pdfView;


    if (!pdfDocument) {
        std::cerr << "Error: pdfDocument is null." << std::endl;
        return;
    }

    model = new QPdfBookmarkModel(this);
    model->setDocument(pdfDocument);
    treeView->setModel(model);
    auto *contents = qobject_cast<Contents *>(splitter->widget(0));
    if (model->rowCount() > 0) {
        treeView->setHeaderHidden(true);
        treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        contents->show();
    } else {
        contents->hide();
    }
}

void Contents::onBookmarkClicked(const QModelIndex &index) const {
    if (!index.isValid() || !pdfDocument) {
        return;
    }
    if (!index.isValid())
        return;
    const int page = index.data(int(QPdfBookmarkModel::Role::Page)).toInt();
    const qreal zoomLevel = index.data(int(QPdfBookmarkModel::Role::Level)).toReal();
    this->pdfView->pageNavigator()->jump(page, {}, zoomLevel);
}

