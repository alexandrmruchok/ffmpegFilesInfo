#include "StreamDetail.h"

const QMap<StreamDetail::Property, QString> StreamDetail::PropertyString {
    {FPS            ,  "Frame rate (FPS)"       },
    {Resolution     ,  "Resolution"      },
    {PictureFormat  ,  "Picture format"   },
    {Channels       ,  "Channels"        },
    {SampleRate     ,  "Sample rate (Hz)" }
};

StreamDetail::StreamDetail(StreamDetail::Property a_property, const QVariant &a_value, QObject *a_parent)
    :QObject (a_parent),
      m_property (a_property),
      m_value (a_value)
{
}

QString StreamDetail::property() const
{
    return PropertyString[m_property];
}

void StreamDetail::setProperty(const Property &property)
{
    m_property = property;
}

QVariant StreamDetail::value() const
{
    return m_value;
}

void StreamDetail::setValue(const QVariant &value)
{
    m_value = value;
}
