#pragma once

#include <QColorDialog>
#include <iostream>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>

#include "vtk_shapes/vtk_shape.hpp"

class ColorData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class VtkFilePathSelectorWidget;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class vtkColorPicker
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkColorPicker";
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    vtkColorPicker();

    ~vtkColorPicker() override;

  public:
    [[nodiscard]] QString caption() const override
    {
        return QStringLiteral("File Path Source");
    }

    [[nodiscard]] bool captionVisible() const override { return false; }

    [[nodiscard]] QString name() const override { return class_id; }

  public:
    [[nodiscard]] QJsonObject save() const override;

    void load(QJsonObject const& p) override;

  public:
    [[nodiscard]] unsigned int nPorts(PortType portType) const override;

    [[nodiscard]] NodeDataType dataType(PortType portType,
                                        PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}

    QWidget* embeddedWidget() override;

  private Q_SLOTS:

    void onColorChanged(QColor const& string);

  private:
    std::shared_ptr<ColorData> _file_path;

    QColorDialog* _lineEdit;
};
