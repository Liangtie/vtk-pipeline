#include "EmbeddedQVTKRenderWidget.hpp"
EmbeddedQVTKRenderWidget::EmbeddedQVTKRenderWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    enum
    {
        WIDTH = 192 / 4,
        HEIGHT = 108 / 4,
    };

    setFixedSize({WIDTH, HEIGHT});
}

EmbeddedQVTKRenderWidget::~EmbeddedQVTKRenderWidget() {}
