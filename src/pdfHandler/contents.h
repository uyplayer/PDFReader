//
// Created by uyplayer on 2024-06-08.
//

#ifndef CONTENTS_H
#define CONTENTS_H

#include <QPdfDocument>
#include <iostream>
#include <QTreeView>
#include <QVBoxLayout>
#include <QtPdfWidgets/QPdfView>
#include <QPdfPageNavigator>
#include <QPdfBookmarkModel>
#include <QSplitter>


class Contents : public QWidget {
Q_OBJECT

public:
    explicit Contents(QWidget *parent);

    ~Contents() override;

    void loadPdfBookmarks(QPdfDocument *pdfDocument, QPdfView *pdfView, const QSplitter *splitter);

private:
    QTreeView *treeView;
    QVBoxLayout *layout;
    QPdfDocument *pdfDocument;
    QPdfView *pdfView;
    QPdfPageNavigator *pageNavigator;
    QPdfBookmarkModel *model{};

private slots:

    void onBookmarkClicked(const QModelIndex &index) const;
};

#endif //CONTENTS_H
