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
                     QString title,
                     QIcon icon,
                     std::vector<std::shared_ptr<VtkBaseShape>> shapes);

    ~VtkShapeCategory() override;

    [[nodiscard]] auto type() const -> VtkShapeType override;

    [[nodiscard]] auto title() const -> QString override;

    [[nodiscard]] auto icon() const -> QIcon override;

    [[nodiscard]] auto hasChildren() const -> bool override;

    [[nodiscard]] auto childrenCount() const -> int override;

    [[nodiscard]] auto getChild(int idx) const
        -> std::shared_ptr<VtkBaseShape> override;

  private:
    VtkShapeType const _type;
    QString const _title;
    QIcon const _icon;
    std::vector<std::shared_ptr<VtkBaseShape>> const _shapes;
};

#endif