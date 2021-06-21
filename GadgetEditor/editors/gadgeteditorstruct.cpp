#include "editors/gadgeteditorstruct.h"
#include "editors/framegrided.h"

GadgetEditorStruct::GadgetEditorStruct(void *gadget, const QMetaProperty property, FrameGrided *parent)
  : GadgetEditor(gadget, property, parent)
{
    createWidgetEditor();
}

void GadgetEditorStruct::onRefreshed()
{

}

void GadgetEditorStruct::createWidgetEditor()
{
    m_editor  = new FrameGrided(parentWidget());
}

