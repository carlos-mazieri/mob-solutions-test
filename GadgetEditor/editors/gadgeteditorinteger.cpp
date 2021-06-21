#include "editors/gadgeteditorinteger.h"
#include "editors/framegrided.h"
#include <QSpinBox>


GadgetEditorInteger::GadgetEditorInteger(void *gadget, const QMetaProperty property, FrameGrided *parent)
    : GadgetEditor(gadget, property, parent)
{
     createWidgetEditor();
}

void GadgetEditorInteger::createWidgetEditor()
{
    auto spin = new QSpinBox(parentWidget());
    auto current = read();
    spin->setMinimum(0);
    auto size = QMetaType(m_property.userType()).sizeOf();
    auto max  = (2 << (size * 8 - 1)) -1;
    spin->setMaximum(max);
    spin->setValue(current.toDouble());
    m_editor = spin;
    connect(spin, SIGNAL(valueChanged(int)),
            this, SLOT(onEditorDataChanged(int)));
}

void GadgetEditorInteger::onEditorDataChanged(int value)
{
    write(value);
}
