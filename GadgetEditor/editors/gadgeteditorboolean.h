#ifndef GADGETEDITORBOOLEAN_H
#define GADGETEDITORBOOLEAN_H

#include "editors/gadgeteditor.h"
#include "editors/framegrided.h"

class GadgetEditorBoolean : public GadgetEditor
{
    Q_OBJECT
public:
    explicit GadgetEditorBoolean(void *gadget, const QMetaProperty property, FrameGrided *parent = nullptr);
protected:
    void createWidgetEditor() override;
protected slots:
    void onEditorDataChanged(bool value);
};

#endif // GADGETEDITORBOOLEAN_H
