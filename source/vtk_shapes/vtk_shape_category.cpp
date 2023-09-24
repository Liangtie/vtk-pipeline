#include <utility>

#include "vtk_shape_category.hpp"

VtkShapeCategory::VtkShapeCategory(
    VtkShapeType type,
    QString description,
    QIcon icon,
    std::vector<std::shared_ptr<VtkBaseShape>> shapes)
    : _type(std::move(type))
    , _description(std::move(description))
    , _icon(std::move(icon))
    , _shapes(std::move(shapes))
{
}

VtkShapeCategory::~VtkShapeCategory() = default;

auto VtkShapeCategory::type() const -> VtkShapeType
{
    return _type;
}

auto VtkShapeCategory::description() const -> QString
{
    return _description;
}

auto VtkShapeCategory::icon() const -> QIcon
{
    return _icon;
}

auto VtkShapeCategory::hasChildren() const -> bool
{
    return true;
}

auto VtkShapeCategory::childrenCount() const -> int
{
    return _shapes.size();
}

auto VtkShapeCategory::getChild(int idx) const -> std::shared_ptr<VtkBaseShape>
{
    if (idx < _shapes.size())
        return _shapes[idx];
    return {};
}
