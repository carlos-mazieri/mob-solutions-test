#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include "editors/framegrided.h"

class GridWidget : public FrameGrided
{
    Q_OBJECT
public:
    explicit GridWidget(QWidget *parent = nullptr);
};

#endif // GRIDWIDGET_H
