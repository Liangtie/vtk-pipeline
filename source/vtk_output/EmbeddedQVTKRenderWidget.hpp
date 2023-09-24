#ifndef EMBEDDEDQVTKRENDERWIDGET_HPP
#define EMBEDDEDQVTKRENDERWIDGET_HPP

#include <QVTKOpenGLNativeWidget.h>
#include <qwidget.h>
class EmbeddedQVTKRenderWidget : public QVTKOpenGLNativeWidget
{
  public:
    EmbeddedQVTKRenderWidget(QWidget* parent = nullptr);
    ~EmbeddedQVTKRenderWidget() override;
};

#endif