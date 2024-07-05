//
// Created by uyplayer on 2024-07-05.
//

#ifndef PDFGLIMPSE_KEYINFODIALOG_H
#define PDFGLIMPSE_KEYINFODIALOG_H


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>

class KeyInfoDialog : public QDialog {
Q_OBJECT

public:
    explicit KeyInfoDialog(const std::string &keyInfo, QWidget *parent = nullptr) : QDialog(parent) {
        auto layout = new QVBoxLayout(this);
        auto label = new QLabel(QString::fromStdString(keyInfo), this);
        auto button = new QPushButton("Copy", this);

        // 设置窗口样式
        this->setStyleSheet("background-color: #333; color: #fff;");
        // 设置按钮大小


        // 设置标签样式
        label->setStyleSheet("font-size: 16px; padding: 10px;");

        // 设置按钮样式
        button->setStyleSheet(
                "background-color: #4CAF50; color: white; border: none; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;");

        layout->addWidget(label);
        layout->addWidget(button);

        connect(button, &QPushButton::clicked, this, [this, keyInfo]() {
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(QString::fromStdString(keyInfo));
            this->close();
        });


    }

};

#endif //PDFGLIMPSE_KEYINFODIALOG_H
