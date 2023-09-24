#include "vtk_shape.hpp"

#include <qtpreprocessorsupport.h>

VtkShape::VtkShape(VtkShapeType type, QString title, QIcon icon)
    : _type(type)
    , _title(std::move(title))
    , _icon(std::move(icon))
{
}

VtkShape::~VtkShape() = default;

auto VtkShape::type() const -> VtkShapeType
{
    return _type;
}

auto VtkShape::title() const -> QString
{
    return _title;
}

auto VtkShape::icon() const -> QIcon
{
    return _icon;
}

auto VtkShape::hasChildren() const -> bool
{
    return false;
}

auto VtkShape::getChild(int idx) const -> std::shared_ptr<VtkBaseShape>
{
    Q_UNUSED(idx)
    return {};
}

auto VtkShape::childrenCount() const -> int
{
    return 0;
}