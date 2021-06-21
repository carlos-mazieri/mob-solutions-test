#include "gridwidget.h"
#include <QGridLayout>

GridWidget::GridWidget(QWidget *parent) : FrameGrided(parent)
{   
    setFrameStyle(QFrame::NoFrame);
    setLineWidth(0);
}
