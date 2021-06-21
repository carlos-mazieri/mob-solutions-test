#ifndef GADGETEDITORSTRUCT_H
#define GADGETEDITORSTRUCT_H

#include "editors/gadgeteditor.h"
#include <QObject>

class GadgetEditorStruct : public GadgetEditor
{
    Q_OBJECT
public:
    explicit GadgetEditorStruct(void *gadget, const QMetaProperty property, FrameGrided *parent = nullptr);
public slots:
    void onRefreshed();
protected:
    void createWidgetEditor() override;
};

#endif // GADGETEDITORSTRUCT_H
