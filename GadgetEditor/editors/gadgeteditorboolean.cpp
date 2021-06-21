#include "editors/gadgeteditorboolean.h"
#include <QCheckBox>

GadgetEditorBoolean::GadgetEditorBoolean(void *gadget, const QMetaProperty property, FrameGrided *parent)
    : GadgetEditor(gadget, property, parent)
{
    createWidgetEditor();
}

void GadgetEditorBoolean::createWidgetEditor()
{
    auto check = new QCheckBox(parentWidget());
    auto current = read();
    check->setChecked(current.toBool());
    connect(check, SIGNAL(toggled(bool)),
            this,  SLOT(onEditorDataChanged(bool)));
    m_editor = check;
}

void GadgetEditorBoolean::onEditorDataChanged(bool value)
{
    write(value);
}
