#ifndef STREAMINFO_H
#define STREAMINFO_H

#include <QQmlListProperty>

#include "StreamDetail.h"

extern "C"
{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

struct StreamInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(QString codec READ codec CONSTANT)
    Q_PROPERTY(QList<QObject*> details READ details CONSTANT)

public:
    explicit StreamInfo(QObject *a_parent = nullptr);
    explicit StreamInfo(AVStream *a_stream, QObject *a_parent = nullptr);

    QString type() const;
    void setType(const AVMediaType &a_type);

    QString codec() const;
    void setCodec(AVCodecID a_codecId);

    QList<QObject*> details();
    void addDetail(StreamDetail::Property a_property, const QVariant& a_value);

private:
    AVMediaType     m_type;
    AVCodecID       m_codecId;
    QList<QObject*> m_details;
};



#endif // STREAMINFO_H
