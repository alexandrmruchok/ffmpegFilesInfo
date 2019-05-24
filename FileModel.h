#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QDebug>

#include "FileInfo.h"

class FileModel : public QFileSystemModel
{
    Q_OBJECT
    Q_PROPERTY(FileInfo* selectedFile READ selectedFile NOTIFY selectedFileChanged)
    Q_PROPERTY(QModelIndex rootIndex READ rootIndex NOTIFY rootPathChanged)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QItemSelectionModel* selection MEMBER m_selectionModel CONSTANT)

public:
    FileModel(QObject *a_parent = nullptr);

    FileInfo *selectedFile() const;
    QModelIndex rootIndex();

    QItemSelectionModel *m_selectionModel;

signals:
    void selectedFileChanged();
    void rootPathChanged();

private:
    QHash<QString, FileInfo*> m_files;
    FileInfo *m_emptyFile;

    AVFormatContext *m_fmtCtx {nullptr};
};

#endif // FILEMODEL_H
