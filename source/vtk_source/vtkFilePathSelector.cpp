#include <QFile>

#include "vtkFilePathSelector.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/FilePathData.hpp"

vtkFilePathSelector::vtkFilePathSelector()
    : VtkShape(class_id)
    , _text(std::make_shared<FilePathData>(""))
    , _lineEdit {nullptr}
{
}

QJsonObject vtkFilePathSelector::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["file_path"] = _text->filePath();

    return modelJson;
}

void vtkFilePathSelector::load(QJsonObject const& p)
{
    QJsonValue v = p["file_path"];

    if (!v.isUndefined()) {
        QString str = v.toString();

        if (QFile::exists(str)) {
            _text = std::make_shared<FilePathData>(str);

            if (_lineEdit)
                _lineEdit->setText(str);
        }
    }
}

unsigned int vtkFilePathSelector::nPorts(PortType portType) const
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

void vtkFilePathSelector::onTextEdited(QString const& str)
{
    if (QFile::exists(str)) {
        _text = std::make_shared<FilePathData>(str);
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType vtkFilePathSelector::dataType(PortType, PortIndex) const
{
    return FilePathData().type();
}

std::shared_ptr<NodeData> vtkFilePathSelector::outData(PortIndex)
{
    return _text;
}

QWidget* vtkFilePathSelector::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit();

        _lineEdit->setMaximumSize(_lineEdit->sizeHint());

        connect(_lineEdit,
                &QLineEdit::textChanged,
                this,
                &vtkFilePathSelector::onTextEdited);

        _lineEdit->setText(_text->filePath());
    }

    return _lineEdit;
}

void vtkFilePathSelector::setText(double n)
{
    _text = std::make_shared<FilePathData>(n);

    Q_EMIT dataUpdated(0);

    if (_lineEdit)
        _lineEdit->setText(_text->filePath());
}
