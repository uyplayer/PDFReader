//
// Created by uyplayer on 2024-06-01.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPdfDocument>
#include <QSplitter>
#include <iostream>
#include "viewer.h"
#include "contents.h"
#include "HdInfoHandle.h"
#include <QPushButton>
#include <QToolBar>


QT_BEGIN_NAMESPACE

namespace Ui {
    class mainWindow;
}

QT_END_NAMESPACE

class mainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);

    ~mainWindow() override;


private:

    Ui::mainWindow *ui;
    QSplitter *splitter;
    Viewer *viewer;
    Contents *contents;
    HdInfoHandle *hdInfoHandle;
    QPushButton *zoom_in;
    QPushButton *zoom_out;
    QToolBar *toolBar;
    QWidget *spacerWidgetTop;
protected:
    void closeEvent(QCloseEvent *event) override {
        QWidget::closeEvent(event);
    }
};

#endif //MAINWINDOW_H
