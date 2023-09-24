#ifndef VTK_SHAPES_MODEL_HPP
#define VTK_SHAPES_MODEL_HPP

#include <memory>
#include <vector>

#include <qabstractitemmodel.h>
#include <qobject.h>

class VtkBaseShape;
class VtkShapeModel : public QAbstractItemModel
{
  public:
    VtkShapeModel(std::vector<std::shared_ptr<VtkBaseShape>> shapes,
                  QObject* parent = nullptr);
    ~VtkShapeModel() override;

    [[nodiscard]] int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] int columnCount(
        const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] bool hasChildren(const QModelIndex& index) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index,
                                int role = Qt::DisplayRole) const override;

    [[nodiscard]] QModelIndex index(
        int row,
        int column,
        const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex& index) const override;

  private:
    std::map<void*, void*> _childParentMap;
    std::map<void*, int> _childIndexMap;
    std::vector<std::shared_ptr<VtkBaseShape>> _shapes;
};

#endif