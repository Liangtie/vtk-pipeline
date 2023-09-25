#include <QFile>

#include "vtkColorPicker.hpp"

#include <qabstractbutton.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qicon.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qwidget.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "ColorData.hpp"
#include "utils/flat_style.hpp"
#include "vtkColorPicker.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/color/ColorData.hpp"

vtkColorPicker::vtkColorPicker()
    : VtkShape(class_id)
    , _file_path(std::make_shared<ColorData>())
    , _lineEdit {nullptr}
{
}

vtkColorPicker::~vtkColorPicker()
{
    if (_lineEdit)
        delete _lineEdit;
}

QJsonObject vtkColorPicker::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["color"] = static_cast<int>(_file_path->getColor().rgb());
    return modelJson;
}

void vtkColorPicker::load(QJsonObject const& p)
{
    QJsonValue v = p["color"];

    if (!v.isUndefined()) {
        _file_path->setColor(QColor(v.toInt()));
    }
}

unsigned int vtkColorPicker::nPorts(PortType portType) const
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

void vtkColorPicker::onColorChanged(QColor const& c)

{
    _file_path = std::make_shared<ColorData>(c);
    Q_EMIT dataUpdated(0);
}

NodeDataType vtkColorPicker::dataType(PortType, PortIndex) const
{
    return ColorData().type();
}

std::shared_ptr<NodeData> vtkColorPicker::outData(PortIndex)
{
    return _file_path;
}

QWidget* vtkColorPicker::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QColorDialog();

        _lineEdit->setMaximumSize(_lineEdit->sizeHint());
        _lineEdit->setCurrentColor(_file_path->getColor());

        connect(_lineEdit,
                &QColorDialog::currentColorChanged,
                this,
                &vtkColorPicker::onColorChanged);
    }
    if (!_btn) {
        _btn = new QToolButton();
        _btn->setIcon(QIcon(":/style/icon/pick_color.png"));
        setupFlatStyle(_btn);
        connect(
            _btn, &QAbstractButton::clicked, _lineEdit, &QColorDialog::exec);
    }

    return _btn;
}
