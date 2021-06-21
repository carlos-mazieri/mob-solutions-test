#ifndef GADGETEDITORDOUBLE_H
#define GADGETEDITORDOUBLE_H

#include "editors/gadgeteditor.h"

class FrameGrided;

class GadgetEditorDouble : public GadgetEditor
{
    Q_OBJECT
public:
    explicit GadgetEditorDouble(void *gadget, const QMetaProperty property, FrameGrided *parent = nullptr);
protected:
    void createWidgetEditor() override;
protected slots:
    void onEditorDataChanged(double value);
};

#endif // GADGETEDITORDOUBLE_H
