#ifndef GADGETEDITORINTEGER_H
#define GADGETEDITORINTEGER_H

#include "editors/gadgeteditor.h"

class GadgetEditorInteger : public GadgetEditor
{
    Q_OBJECT
public:
    explicit GadgetEditorInteger(void *gadget, const QMetaProperty property, FrameGrided *parent = nullptr);
protected:
    void createWidgetEditor() override;
protected slots:
    void onEditorDataChanged(int value);
};

#endif // GADGETEDITORINTEGER_H
