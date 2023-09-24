#ifndef FLAT_STYLE_HPP
#define FLAT_STYLE_HPP

#include <QObject>
#include <QVariant>

#include <qobject.h>

inline auto setupFlatStyle(QObject* obj)
{
    obj->setProperty("flat", true);
}

#endif