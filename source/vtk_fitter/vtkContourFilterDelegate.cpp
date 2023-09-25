#include <QFile>
#include <memory>

#include "vtkContourFilterDelegate.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkContourFilterDelegate.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    FEATURE_ANGLE,
    SRC,
    INPUT_COUNT,

    DEFAULT_VALUE = 500
};

vtkContourFilterDelegate::vtkContourFilterDelegate()
    : VtkShape(class_id)
{
    _filter->SetValue(0, DEFAULT_VALUE);
}

vtkContourFilterDelegate::~vtkContourFilterDelegate() {}

QJsonObject vtkContourFilterDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["_value"] = _value;

    return modelJson;
}

void vtkContourFilterDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_value"];

        if (!v.isUndefined()) {
            _value = v.toDouble();
        }
    }
}

unsigned int vtkContourFilterDelegate::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = INPUT_COUNT;
            break;
        case PortType::Out:
            result = 1;
        default:
            break;
    }

    return result;
}

NodeDataType vtkContourFilterDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case FEATURE_ANGLE:
                    return DecimalData("value").type();
                case SRC:
                    return VtkAlgorithmOutputData().type();
            }
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();
        case QtNodes::PortType::None:
            break;
    }
}

std::shared_ptr<NodeData> vtkContourFilterDelegate::outData(PortIndex)
{
    if (_filter->GetInput())
        _filter->Update();
    return std::make_shared<VtkAlgorithmOutputData>(_filter->GetOutputPort());
}

void vtkContourFilterDelegate::setInData(std::shared_ptr<NodeData> data,
                                         PortIndex idx)
{
    auto old = _filter->GetValue(0);

    _filter = vtkNew<vtkContourFilter>();
    switch (idx) {
        case FEATURE_ANGLE:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                old = d->number();
            break;
        case SRC:
            if (auto d =
                    std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
                _filter->SetInputConnection(d->algorithmOutput());
            break;
    }
    _filter->SetInputConnection(_last_in);
    _filter->SetValue(0, old);
    if (_last_in) {
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkContourFilterDelegate::embeddedWidget()
{
    return {};
}
