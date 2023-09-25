#include <memory>

#include "vtkVolume16ReaderDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/slice/SliceData.hpp"
#include "vtk_source/vtkAlgorithmOutputData.hpp"

vtkVolume16ReaderDelegate::vtkVolume16ReaderDelegate()
    : GenericSourceReader(class_id)
    , _reader({})
{
}

vtkVolume16ReaderDelegate::~vtkVolume16ReaderDelegate() {}

unsigned int vtkVolume16ReaderDelegate::nPorts(PortType portType) const
{
    switch (portType) {
        case QtNodes::PortType::In:
            return 1;
        case QtNodes::PortType::Out:
            return 3;
        case QtNodes::PortType::None:
            break;
    }
}

QJsonObject vtkVolume16ReaderDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["fp_prefix"] = _reader->GetFilePrefix();

    return modelJson;
}

void vtkVolume16ReaderDelegate::load(QJsonObject const& p)
{
    QJsonValue v = p["fp_prefix"];

    if (!v.isUndefined()) {
        QString str = v.toString();
        _reader->SetFilePrefix(str.toStdString().c_str());
    }
}

NodeDataType vtkVolume16ReaderDelegate::dataType(PortType const t,
                                                 PortIndex const) const
{
    switch (t) {
        case QtNodes::PortType::In:
            return SliceData().type();
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();
            break;
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

std::shared_ptr<NodeData> vtkVolume16ReaderDelegate::outData(PortIndex idx)
{
    Q_UNUSED(idx)
    if (_reader->GetInput()) {
        _reader->Update();
        return std::make_shared<VtkAlgorithmOutputData>(
            _reader->GetOutputPort());
    }
    return {};
}

void vtkVolume16ReaderDelegate::setInData(std::shared_ptr<NodeData> data,
                                          PortIndex const portIndex)
{
    Q_UNUSED(portIndex)
    if (auto slice = std::dynamic_pointer_cast<SliceData>(data)) {
        _reader = vtkNew<vtkVolume16Reader>();
        _reader->SetFilePrefix(slice->getPrefix().toStdString().data());
        _reader->SetImageRange(slice->_start_idx, slice->_end_idx);
        _reader->SetDataDimensions(64, 64);
        _reader->SetDataByteOrderToLittleEndian();
        _reader->SetDataSpacing(3.2, 3.2, 1.5);
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}
