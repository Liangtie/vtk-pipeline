#ifndef VTK_BASE_SHAPE_HPP
#define VTK_BASE_SHAPE_HPP
#include <QString>
#include <vector>

#include <qicon.h>

#include "vtk_shape_type.hpp"

class VtkBaseShape
{
  public:
    virtual ~VtkBaseShape() = default;

    [[nodiscard]] virtual auto type() const -> VtkShapeType = 0;

    [[nodiscard]] virtual auto title() const -> QString = 0;

    [[nodiscard]] virtual auto icon() const -> QIcon = 0;

    [[nodiscard]] virtual auto hasChildren() const -> bool = 0;

    [[nodiscard]] virtual auto childrenCount() const -> int = 0;

    [[nodiscard]] virtual auto getChild(int idx) const
        -> std::shared_ptr<VtkBaseShape> = 0;

    [[nodiscard]] virtual auto getChildren() const
        -> std::vector<std::shared_ptr<VtkBaseShape>> const& = 0;
};

#endif