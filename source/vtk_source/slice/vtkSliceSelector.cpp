#include <QFile>

#include "vtkSliceSelector.hpp"

#include <qdir.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkSliceSelector.hpp"
#include "vtkSliceSelectorwidget.h"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/slice/SliceData.hpp"

vtkSliceSelector::vtkSliceSelector()
    : VtkShape(class_id)
    , _slice_data(std::make_shared<SliceData>())
    , _slice_selector {nullptr}
{
}

vtkSliceSelector::~vtkSliceSelector() {}

QJsonObject vtkSliceSelector::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["_dir"] = _slice_selector->getDir();
    modelJson["_prefix"] = _slice_selector->getPrefix();
    modelJson["_start_idx"] = _slice_selector->getStartIdx();
    modelJson["_end_idx"] = _slice_selector->getEndIdx();

    return modelJson;
}

void vtkSliceSelector::load(QJsonObject const& p)
{
    if (_slice_selector) {
        {
            QJsonValue v = p["_dir"];
            if (!v.isUndefined()) {
                _slice_selector->setDir(v.toString());
            }
        }
        {
            QJsonValue v = p["_prefix"];
            if (!v.isUndefined()) {
                _slice_selector->setPrefix(v.toString());
            }
        }
        {
            QJsonValue v = p["_start_idx"];
            if (!v.isUndefined()) {
                _slice_selector->setStartIdx(v.toInt());
            }
        }
        {
            QJsonValue v = p["_end_idx"];
            if (!v.isUndefined()) {
                _slice_selector->setEndIdx(v.toInt());
            }
        }
    }
}

unsigned int vtkSliceSelector::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = 0;
            break;

        case PortType::Out:
            result = 1;

        default:
            break;
    }

    return result;
}

void vtkSliceSelector::onDataChanged()

{
    _slice_data->_dir = _slice_selector->getDir();
    _slice_data->_prefix = _slice_selector->getPrefix();
    _slice_data->_start_idx = _slice_selector->getStartIdx();
    _slice_data->_end_idx = _slice_selector->getEndIdx();
    Q_EMIT dataUpdated(0);
}

NodeDataType vtkSliceSelector::dataType(PortType, PortIndex) const
{
    return SliceData().type();
}

std::shared_ptr<NodeData> vtkSliceSelector::outData(PortIndex)
{
    return _slice_data;
}

QWidget* vtkSliceSelector::embeddedWidget()
{
    if (!_slice_selector) {
        _slice_selector = new vtkSliceSelectorWidget();
        connect(_slice_selector,
                &vtkSliceSelectorWidget::data_changed,
                this,
                &vtkSliceSelector::onDataChanged);
    }

    return _slice_selector;
}
