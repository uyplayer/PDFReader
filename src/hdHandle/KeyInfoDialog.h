//
// Created by  on 2024-07-05.
//

#ifndef PDFGLIMPSE_KEYINFODIALOG_H
#define PDFGLIMPSE_KEYINFODIALOG_H


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QClipboard>
#include <QApplication>
#include <cryptology.h>
#include <QCryptographicHash>
#include <QScreen>

class KeyInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit KeyInfoDialog(const std::string &keyInfo, QWidget *parent = nullptr) : QDialog(parent) {
        QCryptographicHash hash(QCryptographicHash::Sha256);
        hash.addData(keyInfo.c_str(), keyInfo.length());
        QByteArray hashResult = hash.result();
        auto hash_uuid = QString(hashResult.toHex());

        setWindowTitle("UUID");
        setWindowIcon(QIcon(":/icon/icon/app_books.png"));

        // 获取屏幕几何信息
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();

        // 计算窗口居中位置
        int x = screenGeometry.center().x() - width() / 2;
        int y = screenGeometry.center().y() - height() / 2;

        // 设置窗口初始大小和位置
        setGeometry(x, y, 600, 200);

        auto layout = new QVBoxLayout(this);
        auto label = new QLabel(hash_uuid, this);

        auto button = new QPushButton("Copy UUID", this);
        setStyleSheet("background-color: #333; color: #fff;");
        label->setStyleSheet("font-size: 16px; padding: 10px;");
        button->setStyleSheet(
            "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 5px 10px; font-size: 16px; }"
            "QPushButton:hover { background-color: #45a049; }"
        );
        button->setFixedSize(150, 50);

        auto hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget(button);
        hLayout->addStretch();

        layout->addWidget(label);
        layout->addLayout(hLayout);


        std::cout << "UUID: " << hash_uuid.toStdString() << std::endl;

        connect(button, &QPushButton::clicked, this, [this,hash_uuid]() {
            QApplication::clipboard()->setText(hash_uuid);
            this->close();
        });
    }
};

#endif //PDFGLIMPSE_KEYINFODIALOG_H
