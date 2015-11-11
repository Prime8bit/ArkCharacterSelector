#ifndef SELECTLISTITEM_H
#define SELECTLISTITEM_H

#include <QObject>

class SelectListItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit SelectListItem(QObject *object)
        : _objectPtr(object)
        , name(object->objectName())
    {}

    QString name();
    void setName(const QString &newName);

signals:
    void nameChanged();

private:
    QObject* _objectPtr;
};

#endif // SELECTLISTITEM_H
