#include <QFile>
#include <memory>

#include "vtkActorDelegate.hpp"

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

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkActorDelegate.hpp"
#include "vtk_mapper/vtkMapperData.hpp"
#include "vtk_process/vtkActorData.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/color/ColorData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    COLOR,
    ACTOR_ONE,

    INPUT_COUNT,
};

enum
{
    R,
    G,
    B,
};

vtkActorDelegate::vtkActorDelegate()
    : VtkShape(class_id)
{
}

vtkActorDelegate::~vtkActorDelegate() {}

QJsonObject vtkActorDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["_color"] = static_cast<int>(_color.rgb());
    return modelJson;
}

void vtkActorDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_color"];

        if (!v.isUndefined()) {
            _color = QColor(v.toInt());
        }
    }
}

unsigned int vtkActorDelegate::nPorts(PortType portType) const
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

NodeDataType vtkActorDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case COLOR:
                    return ColorData().type();
                case ACTOR_ONE:
                    return vtkMapperData().type();
            }
        case QtNodes::PortType::Out:
            return vtkActorData().type();
        case QtNodes::PortType::None:
            break;
    }

    return {};
}

std::shared_ptr<NodeData> vtkActorDelegate::outData(PortIndex)
{
    return std::make_shared<vtkActorData>(_actor.Get());
}

void vtkActorDelegate::setInData(std::shared_ptr<NodeData> data, PortIndex idx)
{
    double rgb[3] {};
    memcpy(rgb, _actor->GetProperty()->GetColor(), 3);
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
            if (auto d = std::dynamic_pointer_cast<vtkMapperData>(data))
                _last_in = d->getValue();
            else
                _last_in = nullptr;
            break;
    }

    _actor->SetMapper(_last_in);
    _actor->GetProperty()->SetColor(rgb);
    if (_last_in) {
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkActorDelegate::embeddedWidget()
{
    return {};
}
