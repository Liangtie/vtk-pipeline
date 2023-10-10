#include <QFile>
#include <memory>

#include "vtkPolyDataNormalsDelegate.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    FEATURE_ANGLE,
    SRC,

    INPUT_COUNT,
};

vtkPolyDataNormalsDelegate::vtkPolyDataNormalsDelegate()
    : VtkShape(class_id)
{
    _filter->SetFeatureAngle(_featureAngle);
}

vtkPolyDataNormalsDelegate::~vtkPolyDataNormalsDelegate() {}

QJsonObject vtkPolyDataNormalsDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["_featureAngle"] = _featureAngle;

    return modelJson;
}

void vtkPolyDataNormalsDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_featureAngle"];

        if (!v.isUndefined()) {
            _featureAngle = v.toDouble();
        }
    }
}

unsigned int vtkPolyDataNormalsDelegate::nPorts(PortType portType) const
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

NodeDataType vtkPolyDataNormalsDelegate::dataType(PortType t,
                                                  PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case FEATURE_ANGLE:
                    return DecimalData("featureAngle").type();
                case SRC:
                    return VtkAlgorithmOutputData().type();
            }
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();
        case QtNodes::PortType::None:
            break;
    }
}

std::shared_ptr<NodeData> vtkPolyDataNormalsDelegate::outData(PortIndex)
{
    if (_filter->GetInput())
        _filter->Update();
    return std::make_shared<VtkAlgorithmOutputData>(_filter->GetOutputPort());
}

void vtkPolyDataNormalsDelegate::setInData(std::shared_ptr<NodeData> data,
                                           PortIndex idx)
{
    auto old = _filter->GetFeatureAngle();

    _filter = vtkNew<vtkPolyDataNormals>();
    switch (idx) {
        case FEATURE_ANGLE:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                old = d->number();
            break;
        case SRC:
            if (auto d =
                    std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
                _last_in = (d->algorithmOutput());
            else
                _last_in = nullptr;
            break;
    }
    _filter->SetInputConnection(_last_in);
    _filter->SetFeatureAngle(old);
    if (_last_in) {
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkPolyDataNormalsDelegate::embeddedWidget()
{
    return {};
}
