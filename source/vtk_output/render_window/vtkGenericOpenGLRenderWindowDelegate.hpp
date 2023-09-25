#pragma once

#include <iostream>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGLTFImporter.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageViewer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkRenderer.h>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>

#include "vtk_shapes/vtk_shape.hpp"

class FilePathData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class EmbeddedQVTKRenderWidget;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class vtkGenericOpenGLRenderWindowDelegate
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkGenericOpenGLRenderWindow";
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    vtkGenericOpenGLRenderWindowDelegate();

    ~vtkGenericOpenGLRenderWindowDelegate() override;

  public:
    [[nodiscard]] QString caption() const override
    {
        return QStringLiteral("vtkGenericOpenGLRenderWindow");
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

    void setInData(std::shared_ptr<NodeData>, PortIndex) override;
    std::shared_ptr<NodeData> outData(PortIndex const) override { return {}; }

    QWidget* embeddedWidget() override;

  private:
    vtkNew<vtkGenericOpenGLRenderWindow> _renWin;
    EmbeddedQVTKRenderWidget* _vtk_widget;
    vtkNew<vtkRenderWindowInteractor> _renderWindowInteractor;
};
