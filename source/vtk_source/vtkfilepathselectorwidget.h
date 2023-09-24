#ifndef VTKFILEPATHSELECTORWIDGET_H
#define VTKFILEPATHSELECTORWIDGET_H

#include <QWidget>

#include <qtmetamacros.h>

namespace Ui
{
class VtkFilePathSelectorWidget;
}

class VtkFilePathSelectorWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit VtkFilePathSelectorWidget(QWidget* parent = nullptr);
    ~VtkFilePathSelectorWidget();

    void setText(QString const& t);

  private:
    Ui::VtkFilePathSelectorWidget* ui;

  signals:

    void filePathSelected(QString const&);
};

#endif  // VTKFILEPATHSELECTORWIDGET_H
