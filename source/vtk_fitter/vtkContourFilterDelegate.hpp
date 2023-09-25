#pragma once

#include <iostream>

#include <vtkContourFilter.h>
#include <vtkNew.h>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>

#include "vtk_shapes/vtk_shape.hpp"

class VtkAlgorithmOutputData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class vtkContourFilterDelegate
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkContourFilter";
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    vtkContourFilterDelegate();

    ~vtkContourFilterDelegate() override;

  public:
    [[nodiscard]] QString caption() const override
    {
        return QStringLiteral("vtkContourFilter");
    }

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
    vtkNew<vtkContourFilter> _filter;
    vtkAlgorithmOutput* _last_in {};
    double _value = 500;
};
