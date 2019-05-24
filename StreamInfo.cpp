#include "StreamInfo.h"

StreamInfo::StreamInfo(QObject *a_parent /*= nullptr*/)
    :QObject (a_parent)
{

}

StreamInfo::StreamInfo(AVStream *a_stream, QObject *a_parent /*= nullptr*/):
    QObject (a_parent),
    m_type (a_stream->codecpar->codec_type),
    m_codecId (a_stream->codecpar->codec_id)
{
    AVCodecParameters *codecPar = a_stream->codecpar;

    // ================================== Video: ==================================

    if (m_type == AVMediaType::AVMEDIA_TYPE_VIDEO)
    {
        // =================== Frame rate: ===================
        if (a_stream->avg_frame_rate.den) {
            double frameRate = av_q2d(a_stream->r_frame_rate);
            addDetail(StreamDetail::FPS, QString::number(frameRate, 'g', 2));
        }

        // =================== Resolution: ===================
        QString resolution("%1 x %2");
        resolution = resolution.arg(codecPar->width).arg(codecPar->height);
        addDetail(StreamDetail::Resolution, resolution);

        // =================== format: ===================
        addDetail(StreamDetail::PictureFormat, codecPar->format);
    }

    // ================================== Audio: ==================================

    else if (m_type == AVMediaType::AVMEDIA_TYPE_AUDIO)
    {
        // =================== Channels: ===================
        int nbChannels = codecPar->channels;

        QString strChannels;
        switch (nbChannels) {
        case 1:
            strChannels = "Mono";   break;
        case 2:
            strChannels = "Stereo"; break;
        default:
            strChannels = "Other";
        }
        addDetail(StreamDetail::Channels, strChannels);

        // =================== Sample rate: ===================
        addDetail(StreamDetail::SampleRate, codecPar->sample_rate);
    }
}

QString StreamInfo::type() const
{
    return QString(av_get_media_type_string(m_type));
}

void StreamInfo::setType(const AVMediaType &a_type)
{
    m_type = a_type;
}

QString StreamInfo::codec() const
{
    return avcodec_get_name(m_codecId);
}

void StreamInfo::setCodec(enum AVCodecID a_codecId)
{
    m_codecId = a_codecId;
}

QList<QObject*> StreamInfo::details()
{
    return m_details;
}

void StreamInfo::addDetail(StreamDetail::Property a_property, const QVariant &a_value)
{
    m_details.append(new StreamDetail(a_property, a_value, this));
}

