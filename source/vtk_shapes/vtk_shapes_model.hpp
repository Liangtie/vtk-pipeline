#ifndef VTK_SHAPES_MODEL_HPP
#define VTK_SHAPES_MODEL_HPP

#include <qabstractitemmodel.h>
#include <qobject.h>

class VtkShapeModel : public QAbstractItemModel
{
  public:
    VtkShapeModel(QObject* parent = nullptr);
    ~VtkShapeModel() override;
};

#endif