//
// Created by  on 2024-06-08.
//

#include "viewer.h"
#include <QPdfBookmarkModel>
#include <QCryptographicHash>
#include "HdInfoHandle.h"
#include <thread>
#include <QTemporaryFile>

Viewer::Viewer(QWidget *parent) : QWidget(parent), pdfDocument(nullptr), pdfView(nullptr) {
    layout = new QVBoxLayout(this);
    pdfView = new QPdfView(this);
    layout->addWidget(pdfView);
    setLayout(layout);
    this->setStyleSheet("border: none;");



    msgBox = new QMessageBox(this);
    msgBox->setStyleSheet("QMessageBox {"
        "    background-color: #f0f0f0;"
        "    border: 2px solid darkkhaki;"
        "}"
        "QMessageBox QLabel {"
        "    color: #333333;"
        "}"
        "QMessageBox QPushButton {"
        "    background-color: #cccccc;"
        "    border: 1px solid #999999;"
        "    padding: 5px;"
        "    margin: 5px;"
        "}"
        "QMessageBox QPushButton:hover {"
        "    background-color: #dddddd;"
        "}");

    // uuid
    QString key_info = QString::fromStdString(HdInfoHandle::get_key_info());
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(key_info.toUtf8(), key_info.length());
    QByteArray hashResult = hash.result();
    uuid = QString(hashResult.toHex());
    pdfDocument = new QPdfDocument(this);
}


Viewer::~Viewer() {
    delete layout;
    delete pdfDocument;
    delete pdfView;
    delete msgBox;
}

void Viewer::openPdfFile(QSplitter *splitter) {
    QString pdfPath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("PDF Files (*.pdf);;All Files (*)"));
    if (pdfPath.isEmpty()) {
        std::cout << "No file selected" << std::endl;
        return;
    }

    QByteArray decryptedData = decryptPDFFiles(pdfPath);

    // 将解密后的数据写入临时文件
    QTemporaryFile tempFile;
    if (!tempFile.open()) {
        std::cout << "Failed to create temporary file" << std::endl;
        return;
    }
    tempFile.write(decryptedData);
    tempFile.close();

    // 设置布局
    splitter->show();
    pdfDocument->load(tempFile.fileName());
    pdfView->setPageMode(QPdfView::PageMode::MultiPage);
    pdfView->setDocument(pdfDocument);
    pdfView->setZoomFactor(1);
    auto *contents = qobject_cast<Contents *>(splitter->widget(0));
    contents->loadPdfBookmarks(pdfDocument, pdfView, splitter);
    if (contents) {
        contents->loadPdfBookmarks(pdfDocument, pdfView, splitter);
    }
    tempFile.remove();
}


void Viewer::zoomInClicked() const {
    if (pdfView && pdfDocument) {
        pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
        qreal currentZoom = pdfView->zoomFactor();
        qreal newZoom = currentZoom * 1.1;
        qreal maxZoomFactor = 2.5;
        if (newZoom > maxZoomFactor) {
            newZoom = maxZoomFactor;
        }
        pdfView->setZoomFactor(newZoom);
    }
}


void Viewer::zoomOutClicked() const {
    if (pdfView && pdfDocument) {
        pdfView->setZoomMode(QPdfView::ZoomMode::Custom);
        qreal currentZoom = pdfView->zoomFactor();
        qreal minZoomFactor = 0.5;
        if (currentZoom / 1.1 > minZoomFactor) {
            pdfView->setZoomFactor(currentZoom / 1.1);
        } else {
            pdfView->setZoomFactor(minZoomFactor);
        }
    }
}



void xorDecryptChunk(QByteArray &chunk, const QByteArray &key, int chunkIndex) {
    int keySize = key.size();
    for (int i = 0; i < chunk.size(); ++i) {
        chunk[i] = chunk[i] ^ key[(i + chunkIndex) % keySize];
    }
}

QByteArray Viewer::decryptPDFFiles(const QString &encryptedPdfFile) {
    std::cout << "uuid : " << uuid.toStdString()  << std::endl;
    std::cout << "keys : " << keys.toStdString()  << std::endl;
    QString new_uuid = uuid + keys;
    std::cout << "new_uuid: " << new_uuid.toStdString() << std::endl;
    if (uuid.isEmpty()) {
        msgBox->warning(this, "Warning", "UUID is empty");
        return{};
    }
    QFile file(encryptedPdfFile);
    if (!file.open(QIODevice::ReadOnly)) {
        msgBox->warning(this, "Warning", "Cannot open encrypted PDF file for reading");
        return {};
    }

    QByteArray encryptedData = file.readAll();
    file.close();

    QByteArray key = QCryptographicHash::hash(new_uuid.toUtf8(), QCryptographicHash::Sha256);

    int chunkSize = 1024 * 1024; // 1 MB
    int numChunks = encryptedData.size() / chunkSize + (encryptedData.size() % chunkSize == 0 ? 0 : 1);
    std::vector<QByteArray> chunks(numChunks);

    for (int i = 0; i < numChunks; ++i) {
        chunks[i] = encryptedData.mid(i * chunkSize, chunkSize);
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < numChunks; ++i) {
        threads.emplace_back(xorDecryptChunk, std::ref(chunks[i]), std::ref(key), i * chunkSize);
    }

    for (auto &t : threads) {
        t.join();
    }

    // 合并解密后的块
    QByteArray decryptedData;
    for (const auto &chunk : chunks) {
        decryptedData.append(chunk);
    }
    return decryptedData;
}
