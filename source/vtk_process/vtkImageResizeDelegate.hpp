#pragma once

#include <iostream>

#include <vtkImageResize.h>
#include <vtkNew.h>

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
class vtkImageResizeDelegate
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkImageResize";
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    vtkImageResizeDelegate();

    ~vtkImageResizeDelegate() override;

  public:
    [[nodiscard]] QString caption() const override { return class_id; }

    [[nodiscard]] bool captionVisible() const override { return true; }

    [[nodiscard]] QString name() const override { return class_id; }

  public:
    [[nodiscard]] QJsonObject save() const override;

    void load(QJsonObject const& p) override;

  public:
    [[nodiscard]] unsigned int nPorts(PortType portType) const override;

    [[nodiscard]] NodeDataType dataType(PortType portType,
                                        PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override;

    QWidget* embeddedWidget() override;

  private:
    vtkNew<vtkImageResize> _image_resize;
    vtkAlgorithmOutput* _last_in {};
};
