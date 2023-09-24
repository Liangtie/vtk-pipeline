#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>

#include "vtk_shapes/vtk_shape.hpp"

class FilePathData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class VtkFilePathSelectorWidget;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class vtkFilePathSelector
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkFilePathSelector";
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    vtkFilePathSelector();

    ~vtkFilePathSelector() override;

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

  public:
    void setText(QString);

  private Q_SLOTS:

    void onTextEdited(QString const& string);

  private:
    std::shared_ptr<FilePathData> _file_path;

    VtkFilePathSelectorWidget* _lineEdit;
};
