#ifndef VTKSLICESELECTORWIDGET_H
#define VTKSLICESELECTORWIDGET_H

#include <QWidget>

#include <qtmetamacros.h>

namespace Ui
{
class vtkSliceSelectorWidget;
}

class vtkSliceSelectorWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit vtkSliceSelectorWidget(QWidget* parent = nullptr);
    ~vtkSliceSelectorWidget();

    void setDir(QString const& str);

    void setPrefix(QString const& str);

    void setStartIdx(int idx);

    void setEndIdx(int idx);

    [[nodiscard]] QString getDir() const;

    [[nodiscard]] QString getPrefix() const;

    [[nodiscard]] int getStartIdx() const;

    [[nodiscard]] int getEndIdx() const;

  private:
    Ui::vtkSliceSelectorWidget* ui;

  signals:

    void data_changed();
};

#endif  // VTKSLICESELECTORWIDGET_H
