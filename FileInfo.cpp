#include "FileInfo.h"

FileInfo::FileInfo(QObject *a_parent) : QObject(a_parent)
{
}

FileInfo::FileInfo(AVFormatContext *a_fmtCtx, QObject *a_parent): QObject(a_parent)
{
    for(uint i=0; i<a_fmtCtx->nb_streams; i++)
        addStream(new StreamInfo(a_fmtCtx->streams[i], this));
}

QList<QObject*> FileInfo::streams()
{
    return m_streams;
}

void FileInfo::addStream(StreamInfo *a_stream)
{
    m_streams << a_stream;

    QString strType(a_stream->type());

    if (m_strTypeNumbers.contains(strType))
        m_strTypeNumbers[strType] = m_strTypeNumbers.value(strType).toInt() + 1;

    else
        m_strTypeNumbers[strType] = 1;
}
