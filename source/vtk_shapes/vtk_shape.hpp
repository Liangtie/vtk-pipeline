#ifndef VTK_SHAPE_HPP
#define VTK_SHAPE_HPP

#include <qicon.h>

#include "vtk_shapes/vtk_base_shape.hpp"
class VtkShape : public VtkBaseShape
{
  public:
    VtkShape(VtkShapeType type, QString description = {}, QIcon icon = QIcon());

    ~VtkShape() override;

    [[nodiscard]] auto type() const -> VtkShapeType override;

    [[nodiscard]] auto description() const -> QString override;

    [[nodiscard]] auto icon() const -> QIcon override;

    [[nodiscard]] auto hasChildren() const -> bool override;

    [[nodiscard]] auto getChild(int idx) const
        -> std::shared_ptr<VtkBaseShape> override;

    [[nodiscard]] auto childrenCount() const -> int override;
    [[nodiscard]] auto getChildren() const
        -> std::vector<std::shared_ptr<VtkBaseShape>> const& override
    {
        static std::vector<std::shared_ptr<VtkBaseShape>> invalid;
        return invalid;
    }

  private:
    VtkShapeType const _type;
    QString const _description;
    QIcon const _icon;
};

#endif