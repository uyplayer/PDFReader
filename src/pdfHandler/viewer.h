//
// Created by uyplayer on 2024-06-08.
//

#ifndef VIEWER_H
#define VIEWER_H

#include <QVBoxLayout>
#include <iostream>
#include <QFileDialog>
#include <QtPdfWidgets/QPdfView>
#include <QSplitter>
#include "contents.h"
#include <QWheelEvent>

class Viewer : public QWidget {
Q_OBJECT

public:
    explicit Viewer(QWidget *parent);
    Viewer(const Viewer &other) = delete;
    Viewer &operator=(const Viewer &other) = delete;
    ~Viewer() override;
private:
    QPdfDocument *pdfDocument;
    QPdfView *pdfView;
    QVBoxLayout *layout{};

public slots:
    void zoomInClicked() const ;
    void zoomOutClicked() const ;
    void openPdfFile(QSplitter *splitter);
};


#endif //VIEWER_H
