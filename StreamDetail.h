#ifndef STREAMDETAIL_H
#define STREAMDETAIL_H

#include <QVariant>

class StreamDetail: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString property READ property CONSTANT)
    Q_PROPERTY(QVariant value READ value CONSTANT)

public:
    enum Property {
        FPS,
        Resolution,
        PictureFormat,
        Channels,
        SampleRate
    };
    static const QMap<Property, QString> PropertyString;

    explicit StreamDetail(QObject *a_parent = nullptr):QObject (a_parent){}
    explicit StreamDetail(
            Property a_property,
            const QVariant& a_value,
            QObject *a_parent = nullptr);

    QString property() const;
    void setProperty(const Property &property);

    QVariant value() const;
    void setValue(const QVariant &value);

private:
    Property m_property;
    QVariant m_value;
};

#endif // STREAMDETAIL_H
