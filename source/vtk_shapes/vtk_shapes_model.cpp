#include "vtk_shapes_model.hpp"

#include <qabstractitemmodel.h>
VtkShapeMode::VtkShapeMode(QObject* parent)
    : QAbstractItemModel(parent)
{
}

VtkShapeMode::~VtkShapeMode() = default;
