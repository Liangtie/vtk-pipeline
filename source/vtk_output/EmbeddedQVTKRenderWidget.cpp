#include "EmbeddedQVTKRenderWidget.hpp"
enum
{
    WIDTH = 800 / 2,
    HEIGHT = 600 / 2,
};
EmbeddedQVTKRenderWidget::EmbeddedQVTKRenderWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    setFixedSize({WIDTH, HEIGHT});
    setMinimumSize({WIDTH, HEIGHT});
}

EmbeddedQVTKRenderWidget::~EmbeddedQVTKRenderWidget() {}

QSize EmbeddedQVTKRenderWidget::sizeHint() const
{
    return {WIDTH, HEIGHT};
}
