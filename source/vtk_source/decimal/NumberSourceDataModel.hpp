#pragma once

#include <iostream>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>

#include "vtk_shapes/vtk_shape.hpp"

class DecimalData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class QLineEdit;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class NumberSourceDataModel
    : public NodeDelegateModel
    , public VtkShape

{
    Q_OBJECT

  public:
    NumberSourceDataModel();

    virtual ~NumberSourceDataModel() {}

  public:
    QString caption() const override { return QStringLiteral("decimal"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("decimal"); }

  public:
    QJsonObject save() const override;

    void load(QJsonObject const& p) override;

  public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType,
                          PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}

    QWidget* embeddedWidget() override;

  public:
    void setNumber(double number);

  private Q_SLOTS:

    void onTextEdited(QString const& string);

  private:
    std::shared_ptr<DecimalData> _number;

    QLineEdit* _lineEdit;
};
