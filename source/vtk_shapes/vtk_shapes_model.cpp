#include "vtk_shapes_model.hpp"

#include <qabstractitemmodel.h>

#include "vtk_base_shape.hpp"
#include "vtk_shapes/vtk_base_shape.hpp"
VtkShapeModel::VtkShapeModel(std::vector<std::shared_ptr<VtkBaseShape>> shapes,
                             QObject* parent)
    : QAbstractItemModel(parent)
    , _shapes(std::move(shapes))
{
    auto category_count = 0;
    for (const auto& category : shapes) {
        _childIndexMap.try_emplace(category.get(), category_count);
        auto moduleCount = 0;
        for (const auto& shape : category->getChildren()) {
            _childParentMap.try_emplace(shape.get(), category.get());
            _childIndexMap.try_emplace(shape.get(), moduleCount);
            ++moduleCount;
        }
        ++category_count;
    }
}

int VtkShapeModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return _shapes.size();
    const auto internalPtr =
        static_cast<VtkBaseShape*>(parent.internalPointer());
    return internalPtr->childrenCount();
}

int VtkShapeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

bool VtkShapeModel::hasChildren(const QModelIndex& idx) const
{
    if (!idx.isValid())
        return true;
    return static_cast<VtkBaseShape*>(idx.internalPointer())->hasChildren();
}

QVariant VtkShapeModel::data(const QModelIndex& index, int role) const
{
    const auto base_shape = static_cast<VtkBaseShape*>(index.internalPointer());
    switch (role) {
        case Qt::DisplayRole:
            return base_shape->title();
        case Qt::DecorationRole:
            return base_shape->icon();
            break;
    }

    return {};
}

QModelIndex VtkShapeModel::index(int row,
                                 int column,
                                 const QModelIndex& parent) const
{
    Q_UNUSED(column);
    if (!parent.isValid())
        return createIndex(row, column, _shapes.at(row).get());

    else
        return createIndex(row,
                           column,
                           static_cast<VtkBaseShape*>(parent.internalPointer())
                               ->getChild(row)
                               .get());
}

QModelIndex VtkShapeModel::parent(const QModelIndex& idx) const
{
    if (!idx.isValid()) {
        return {};
    } else {
        const auto ptr = static_cast<VtkBaseShape*>(idx.internalPointer());
        if (!ptr->hasChildren())
            return index(
                _childIndexMap.find(_childParentMap.find(ptr)->second)->second,
                0);
    }
    return {};
}

VtkShapeModel::~VtkShapeModel() = default;
