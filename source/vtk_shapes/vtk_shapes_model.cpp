#include "vtk_shapes_model.hpp"

#include <qabstractitemmodel.h>
VtkShapeModel::VtkShapeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
}

VtkShapeModel::~VtkShapeModel() = default;
