#ifndef vtkPNGReaderDelegateDELEGATE_HPP
#define vtkPNGReaderDelegateDELEGATE_HPP

#include <iostream>
#include <memory>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtWidgets/QLabel>

#include "vtkPNGReader.h"
#include "vtk_shapes/vtk_shape.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;
class VtkAlgorithmOutputData;

class vtkPNGReaderDelegate
    : public NodeDelegateModel
    , public VtkShape
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkPNGReader";

    vtkPNGReaderDelegate();
    ~vtkPNGReaderDelegate() override;

  public:
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    [[nodiscard]] QString caption() const override
    {
        return {"VTK PNG Source"};
    }

    [[nodiscard]] QString name() const override { return class_id; }

  public:
    [[nodiscard]] QJsonObject save() const override;

    void load(QJsonObject const& p) override;

  public:
    [[nodiscard]] virtual QString modelName() const { return class_id; }

    [[nodiscard]] unsigned int nPorts(PortType const portType) const override;

    [[nodiscard]] NodeDataType dataType(
        PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>,
                   PortIndex const portIndex) override;

    QWidget* embeddedWidget() override { return {}; }

    [[nodiscard]] bool resizable() const override { return true; }

  private:
    vtkNew<vtkPNGReader> _reader;
};
#endif