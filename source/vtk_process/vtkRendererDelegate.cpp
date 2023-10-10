#include <QFile>
#include <memory>

#include "vtkRendererDelegate.hpp"

#include <qcolor.h>
#include <qrgb.h>
#include <vcruntime_string.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkContourFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataNormals.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkRendererDelegate.hpp"
#include "vtk_mapper/vtkMapperData.hpp"
#include "vtk_process/vtkActorData.hpp"
#include "vtk_process/vtkRendererData.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/color/ColorData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    COLOR,
    ACTOR_ONE,
    ACTOR_TWO,

    INPUT_COUNT,
};

enum
{
    R,
    G,
    B,
};

vtkRendererDelegate::vtkRendererDelegate()
    : VtkShape(class_id)
{
}

vtkRendererDelegate::~vtkRendererDelegate() {}

QJsonObject vtkRendererDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["_color"] = static_cast<int>(_color.rgb());
    return modelJson;
}

void vtkRendererDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_color"];

        if (!v.isUndefined()) {
            _color = QColor(v.toInt());
        }
    }
}

unsigned int vtkRendererDelegate::nPorts(PortType portType) const
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

NodeDataType vtkRendererDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case COLOR:
                    return ColorData().type();
                case ACTOR_ONE:
                    return vtkActorData().type();
                case ACTOR_TWO:
                    return vtkActorData().type();
            }
        case QtNodes::PortType::Out:
            return vtkRendererData().type();
        case QtNodes::PortType::None:
            break;
    }

    return {};
}

std::shared_ptr<NodeData> vtkRendererDelegate::outData(PortIndex)
{
    return std::make_shared<vtkRendererData>(_filter.Get());
}

void vtkRendererDelegate::setInData(std::shared_ptr<NodeData> data,
                                    PortIndex idx)
{
    double rgb[3] {};
    memcpy(rgb, _filter->GetBackground(), 3);
    _filter = vtkNew<vtkRenderer>();
    switch (idx) {
        case COLOR:
            if (auto c = std::dynamic_pointer_cast<ColorData>(data)) {
                const auto col = c->getColor();
                rgb[R] = col.red();
                rgb[G] = col.green();
                rgb[B] = col.blue();
            }
            break;
        case ACTOR_ONE:
            if (auto d = std::dynamic_pointer_cast<vtkActorData>(data))
                _actors.insert(d->getActor());
            break;
        case ACTOR_TWO:
            if (auto d = std::dynamic_pointer_cast<vtkActorData>(data))
                _actors.insert(d->getActor());
            break;
    }

    _filter->SetBackground(rgb);
    for (const auto& v : _actors) {
        _filter->AddActor(v);
    }

    if (_actors.size()) {
        _Camera = vtkNew<vtkCamera>();
        _Camera->SetViewUp(0, 0, -1);
        _Camera->SetPosition(0, 1, 0);
        _Camera->SetFocalPoint(0, 0, 0);
        _Camera->ComputeViewPlaneNormal();
        _Camera->Azimuth(30.0);
        _Camera->Elevation(30.0);
        _filter->SetActiveCamera(_Camera);
        _filter->ResetCamera();
        _Camera->Dolly(1.5);
        _filter->ResetCameraClippingRange();
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkRendererDelegate::embeddedWidget()
{
    return {};
}
