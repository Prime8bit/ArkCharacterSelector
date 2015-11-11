#include "selectlistitem.h"

QString SelectListItem::name()
{
    return _object->objectName();
}

void SelectListItem::setName(const QString &newName)
{
    if (_objectPtr != newName)
    {
        _objectPtr->setObjectName(newName);
        emit nameChanged();
    }
}
