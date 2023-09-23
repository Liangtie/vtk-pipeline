#ifndef VTK_SHAPES_MODEL_HPP
#define VTK_SHAPES_MODEL_HPP

#include <qabstractitemmodel.h>
#include <qobject.h>
class VtkShapeMode : public QAbstractItemModel
{
  public:
    VtkShapeMode(QObject* parent = nullptr);
    ~VtkShapeMode() override;
};

#endif