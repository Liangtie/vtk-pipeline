#include <QFile>

#include "vtkImageViewerDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"

vtkImageViewerDelegate::vtkImageViewerDelegate()
    : VtkShape(class_id)
    , _text(std::make_shared<FilePathData>(""))
    , _lineEdit {nullptr}
{
}

QJsonObject vtkImageViewerDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    return modelJson;
}

void vtkImageViewerDelegate::load(QJsonObject const& p)
{
    Q_UNUSED(p)
}

unsigned int vtkImageViewerDelegate::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = 1;
            break;

        case PortType::Out:
            result = 0;

        default:
            break;
    }

    return result;
}

void vtkImageViewerDelegate::onTextEdited(QString const& str)
{
    if (QFile::exists(str)) {
        _text = std::make_shared<FilePathData>(str);
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType vtkImageViewerDelegate::dataType(PortType, PortIndex) const
{
    return VtkAlgorithmOutputData().type();
}

std::shared_ptr<NodeData> vtkImageViewerDelegate::outData(PortIndex)
{
    return _text;
}

QWidget* vtkImageViewerDelegate::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit();

        _lineEdit->setMaximumSize(_lineEdit->sizeHint());

        connect(_lineEdit,
                &QLineEdit::textChanged,
                this,
                &vtkImageViewerDelegate::onTextEdited);

        _lineEdit->setText(_text->filePath());
    }

    return _lineEdit;
}
