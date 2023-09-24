#pragma once

#include <iostream>
#include <memory>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtWidgets/QLabel>
#include <vtkJPEGReader.h>
#include <vtkNew.h>
#include "vtk_source/GenericSourceReader.hpp"

class vtkJPGReaderDelegate : public GenericSourceReader
{
    Q_OBJECT

  public:
    static constexpr auto class_id = "vtkJPGReader";

    vtkJPGReaderDelegate();
    ~vtkJPGReaderDelegate() override;

  public:
    [[nodiscard]] auto type() const -> VtkShapeType override
    {
        return class_id;
    }

    [[nodiscard]] QString caption() const override
    {
        return {"VTK JPG Source"};
    }

    [[nodiscard]] QString name() const override { return class_id; }

  public:
    [[nodiscard]] QJsonObject save() const override;

    void load(QJsonObject const& p) override;

  public:
    [[nodiscard]] virtual QString modelName() const { return class_id; }

    [[nodiscard]] NodeDataType dataType(
        PortType const portType, PortIndex const portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex const port) override;

    void setInData(std::shared_ptr<NodeData>,
                   PortIndex const portIndex) override;

    QWidget* embeddedWidget() override { return {}; }

  private:
    vtkNew<vtkJPEGReader> _reader;
};
