#include "editors/gadgeteditorenumerator.h"
#include "editors/framegrided.h"
#include <QComboBox>
#include <QMetaEnum>
#include <QVariant>

GadgetEditorEnumerator::GadgetEditorEnumerator(void *gadget, const QMetaProperty property, FrameGrided *parent)
    : GadgetEditor(gadget, property, parent)
{
    createWidgetEditor();
}

QVariant GadgetEditorEnumerator::read() const
{
    int currentIndex = GadgetEditor::read().toInt();
    auto metaEnum = m_property.enumerator();
    QString strValue(metaEnum.key(currentIndex));
    return strValue;
}

void GadgetEditorEnumerator::createWidgetEditor()
{
    auto combo = new QComboBox(parentWidget());
    auto metaEnum = m_property.enumerator();
    QStringList items;
    for(int counter = 0; counter < metaEnum.keyCount(); counter++)
    {
        items.append(metaEnum.key(counter));
    }
    combo->addItems(items);
    QVariant current = read();
    combo->setCurrentText(current.toString());
    m_editor = combo;
    connect(combo, SIGNAL(currentTextChanged(QString)),
            this,  SLOT(onEditorDataChanged(QString)));
}

void GadgetEditorEnumerator::onEditorDataChanged(const QString &text)
{
    write(text);
}
