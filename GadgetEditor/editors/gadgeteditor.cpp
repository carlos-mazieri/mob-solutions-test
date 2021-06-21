#include "editors/gadgeteditor.h"
#include "editors/framegrided.h"
#include <QWidget>
#include <QMetaType>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

GadgetEditor::GadgetEditor(void *gadget, const QMetaProperty property, FrameGrided *parentWidget)
    : QObject(parentWidget)
    , m_property(property)
    , m_parentWidget(parentWidget)
    , m_gadget(gadget)
{
    createLabel();
}

GadgetEditor::~GadgetEditor()
{
    qDebug("%s this=%p", Q_FUNC_INFO, this);
}

QWidget *GadgetEditor::label() const
{
    return m_label;
}

QWidget *GadgetEditor::editor() const
{
    return m_editor;
}

FrameGrided *GadgetEditor::parentWidget() const
{
    return m_parentWidget;
}

QVariant GadgetEditor::read() const
{
    return m_property.readOnGadget(m_gadget);
}

void GadgetEditor::write(const QVariant &data)
{
    m_property.writeOnGadget(m_gadget, data);
    emit dataChanged();
}

void GadgetEditor::createLabel()
{
    m_label = new QLabel(m_property.name(), parentWidget());
    m_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
}


