#include "editors/gadgeteditordouble.h"
#include "editors/framegrided.h"
#include <QDoubleSpinBox>
#include <QDebug>

GadgetEditorDouble::GadgetEditorDouble(void *gadget, const QMetaProperty property, FrameGrided *parent)
    : GadgetEditor(gadget, property, parent)
{
    createWidgetEditor();
}

void GadgetEditorDouble::createWidgetEditor()
{
    auto spin = new QDoubleSpinBox(parentWidget());
    auto current = read();
    spin->setValue(current.toDouble());
    spin->setStepType(QDoubleSpinBox::AdaptiveDecimalStepType);
    m_editor = spin;
    connect(spin, SIGNAL(valueChanged(double)),
            this, SLOT(onEditorDataChanged(double)));
}

void GadgetEditorDouble::onEditorDataChanged(double value)
{  
    write(value);
}
