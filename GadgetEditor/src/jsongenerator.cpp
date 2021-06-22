#include "jsongenerator.h"
#include "editors/gadgeteditor.h"

#include <QWidget>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QVariant>

JsonGenerator::JsonGenerator()
{

}

JsonGenerator::~JsonGenerator()
{

}

QByteArray JsonGenerator::generate(QWidget *parent)
{
    QJsonDocument doc;
    QJsonObject obj = walkDownWidget(parent, false);
    // m_lasCointaner represents a container that groups all children containers
    if (m_lasCointaner != nullptr)
    {
        QJsonObject array = walkDownWidget(m_lasCointaner);
        obj.insert("Struct", array);
    }
    doc.setObject(obj);
    QByteArray ret = doc.toJson(QJsonDocument::Indented);
    return ret;
}

QJsonObject JsonGenerator::walkDownWidget(QObject* parent, bool recursive)
{
    QJsonObject ret;
    m_lasCointaner = nullptr;
    foreach (auto child, parent->children()) {
       if (isGadgetEditor(child))
       {
           auto editor = qobject_cast<GadgetEditor*>(child);
           QVariant value = editor->read();
           ret.insert(editor->name(), value.toJsonValue());
       }
       else if (isContainerWidget(child))
       {
          if (recursive == true)
          {
          QJsonObject nested = walkDownWidget(child);
          if (nested.count() > 0)
          {
              QByteArray group("Item");
              group += QByteArray::number(++m_group_counter);
              ret.insert(group, nested);
          }
          }
          else
          {
              m_lasCointaner = child;
          }
       }
    }
    return ret;
}

bool JsonGenerator::isContainerWidget(QObject *widget) const
{
    QByteArray container("FrameGrided");
    bool ret = container == widget->metaObject()->className();
    return ret;
}

bool JsonGenerator::isGadgetEditor(QObject *object) const
{
    static QByteArrayList editors = QByteArrayList()
                                << "GadgetEditorEnumerator"
                                << "GadgetEditorDouble"
                                << "GadgetEditorBoolean"
                                << "GadgetEditorInteger"
                                ;
    bool exist = editors.contains(object->metaObject()->className());
    return exist;
}
