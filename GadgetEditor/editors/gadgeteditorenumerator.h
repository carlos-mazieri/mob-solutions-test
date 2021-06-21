#ifndef GADGETEDITORENUMERATOR_H
#define GADGETEDITORENUMERATOR_H

#include "editors/gadgeteditor.h"

class FrameGrided;

class GadgetEditorEnumerator : public GadgetEditor
{
    Q_OBJECT
public:
    explicit GadgetEditorEnumerator(void *gadget, const QMetaProperty property, FrameGrided *parent = nullptr);
protected:
    void createWidgetEditor() override;
protected slots:
    void onEditorDataChanged(const QString& text);
};


#endif // GADGETEDITORENUMERATOR_H
