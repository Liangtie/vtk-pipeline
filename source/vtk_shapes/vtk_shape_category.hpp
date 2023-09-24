#ifndef VTK_SHAPE_CATEGORY_HPP
#define VTK_SHAPE_CATEGORY_HPP

#include <list>
#include <memory>
#include <vector>

#include "vtk_shapes/vtk_base_shape.hpp"

class VtkShapeCategory : public VtkBaseShape
{
  public:
    VtkShapeCategory(VtkShapeType type,
                     QString description = {},
                     QIcon icon = {},
                     std::vector<std::shared_ptr<VtkBaseShape>> shapes = {});

    ~VtkShapeCategory() override;

    [[nodiscard]] auto type() const -> VtkShapeType override;

    [[nodiscard]] auto description() const -> QString override;

    [[nodiscard]] auto icon() const -> QIcon override;

    [[nodiscard]] auto hasChildren() const -> bool override;

    [[nodiscard]] auto childrenCount() const -> int override;

    [[nodiscard]] auto getChild(int idx) const
        -> std::shared_ptr<VtkBaseShape> override;

    [[nodiscard]] auto getChildren() const
        -> std::vector<std::shared_ptr<VtkBaseShape>> const& override
    {
        return _shapes;
    }

  private:
    VtkShapeType const _type;
    QString const _description;
    QIcon const _icon;
    std::vector<std::shared_ptr<VtkBaseShape>> const _shapes;
};

#endif