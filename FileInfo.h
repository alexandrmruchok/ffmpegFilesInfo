#ifndef FILEINFO_H
#define FILEINFO_H

#include <QVariantMap>

#include "StreamInfo.h"

class FileInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> streams READ streams CONSTANT)
    Q_PROPERTY(QVariantMap streamTypeNumbers MEMBER m_strTypeNumbers CONSTANT)

public:
    explicit FileInfo(QObject *parent = nullptr);
    explicit FileInfo(AVFormatContext *a_fmtCtx, QObject *a_parent = nullptr);

    QList<QObject*> streams();

    void addStream(StreamInfo *a_stream);

    QVariantMap m_strTypeNumbers;

private:
    QList<QObject*> m_streams;

};

Q_DECLARE_METATYPE(FileInfo*)

#endif // FILEINFO_H
