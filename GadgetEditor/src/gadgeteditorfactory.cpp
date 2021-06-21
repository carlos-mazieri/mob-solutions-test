#include "gadgeteditorfactory.h"

#include "editors/framegrided.h"
#include "editors/gadgeteditorstruct.h"
#include "editors/gadgeteditorenumerator.h"
#include "editors/gadgeteditordouble.h"
#include "editors/gadgeteditorinteger.h"
#include "editors/gadgeteditorboolean.h"

#include <QWidget>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>


GadgetEditorFactory::GadgetEditorFactory(FrameGrided *parent,
                                         void *mainGadget,
                                         QMetaObject* metaGadgetObject,
                                         QMetaObject *metaStructGadge)
    : QObject(parent)
    , m_labelStructItem("Item")
    , m_metaGadgetStruct(metaStructGadge)
{
    createMainEditors(parent, mainGadget, metaGadgetObject);
    if (m_metaGadgetStruct)
    {
        // set common label
        for (int counter = m_metaGadgetStruct->classInfoOffset();
                           counter < m_metaGadgetStruct->classInfoCount(); ++counter)
        {
            QString info(m_metaGadgetStruct->classInfo(counter).name());
            if (info.contains(QLatin1String("name"), Qt::CaseInsensitive) == true)
            {
                m_labelStructItem = m_metaGadgetStruct->classInfo(counter).value();
                break;
            }
        }
        // set High level frame
        m_frameStruct = qobject_cast<FrameGrided*>(m_editorStruct->editor());
        // connect signals
        connect(m_editorCounter, SIGNAL(dataChanged()),
                this, SLOT(onCounterItemsChanged()));
    }
    // refresh first time
    onCounterItemsChanged();
}

GadgetEditorFactory::~GadgetEditorFactory()
{

}

void GadgetEditorFactory::onCounterItemsChanged()
{
    auto itemsOnGadgetStruct = m_editorCounter->read().toInt();
    // add if necessary
    for(; m_itemsOnGrid < itemsOnGadgetStruct; m_itemsOnGrid++)
    {
        createStructEditorItem(m_itemsOnGrid);
    }
    // remove if necessary
    for(; m_itemsOnGrid > itemsOnGadgetStruct; m_itemsOnGrid--)
    {
        removeLastStructEditorItem();
    }
}


void GadgetEditorFactory::createMainEditors(FrameGrided *parent, void *mainGadget, QMetaObject *metaGadgetObject)
{
    GadgetEditor* prevoiusEditor = nullptr;
    for (int counter = metaGadgetObject->propertyOffset();
             counter < metaGadgetObject->propertyCount(); ++counter)
    {
        QMetaProperty property = metaGadgetObject->property(counter);
        GadgetEditor* editor = privateCreateEditor(parent, mainGadget, property);
        if (editor != nullptr)
        {   // will manage adding/removing
            if (editor->inherits("GadgetEditorStruct"))
            {
                m_editorCounter = prevoiusEditor;
                m_editorStruct  = static_cast<GadgetEditorStruct*> (editor);
            }
            prevoiusEditor = editor;
            putMainItemEditorOnParent(editor);
        }
    }
}

/*!
 * \brief GadgetEditorFactory::createStructEditorItem
 * \param index  index of gadget object
 */
void GadgetEditorFactory::createStructEditorItem(int index)
{
    // create label for the item
    auto label = new QLabel(m_labelStructItem + QString::number(index+1), m_frameStruct);
    // sub frame
    auto subFrame = new FrameGrided(m_frameStruct);
    // get right gadget object
    auto gadget_item = getStructObjectAddr(index);

    for (int counter = m_metaGadgetStruct->propertyOffset();
             counter < m_metaGadgetStruct->propertyCount(); ++counter)
    {
        auto property = m_metaGadgetStruct->property(counter);
        auto editor = privateCreateEditor(subFrame, gadget_item, property);
        if (editor != nullptr)
        {
            putMainItemEditorOnParent(editor);
        }
    }
    putMainStructEditorOnParent(label, subFrame);
}

void GadgetEditorFactory::putMainItemEditorOnParent(GadgetEditor *editorObject)
{
   auto grid = editorObject->parentWidget()->gridLayout();
   auto row = grid->rowCount();
   grid->addWidget(editorObject->label(),  row, 0, Qt::AlignRight | Qt::AlignTop);
   grid->addWidget(editorObject->editor(), row, 1);
}


void GadgetEditorFactory::putMainStructEditorOnParent(QWidget *customLabel, FrameGrided *subFrame)
{
   auto grid = m_frameStruct->gridLayout();
   auto row  = grid->rowCount();
   grid->addWidget(customLabel,  row, 0, Qt::AlignRight | Qt::AlignTop);
   grid->addWidget(subFrame, row, 1);
}


void * GadgetEditorFactory::getStructObjectAddr(int index) const
{
    auto   addrItem = m_editorStruct->read();
    char ** pointer_arimetic  = reinterpret_cast<char**>(addrItem.value<void*>());
    void *  gadget_struct_obj = static_cast<void*> (pointer_arimetic[index]);
    return gadget_struct_obj;
}

void GadgetEditorFactory::removeLastStructEditorItem()
{
    auto grid  = m_frameStruct->gridLayout();
    auto counter = grid->count();

    auto dataItem  = grid->takeAt(counter -1);
    auto labelItem = grid->takeAt(counter -2);

//    qDebug() << Q_FUNC_INFO  << "count:"<< grid->count();
//    qDebug("%s label=%p widget=%p", Q_FUNC_INFO, labelItem->widget(), dataItem->widget());
//    qDebug() << "total height" << m_frameStruct->height()  << "item heigh" << itemHeigth << "label heigth" << labelItem->widget()->height();

    delete labelItem->widget();
    delete labelItem;
    delete dataItem->widget();
    delete dataItem;

}

GadgetEditor* GadgetEditorFactory::privateCreateEditor(FrameGrided *parent, void *gadget, QMetaProperty property)
{    
    GadgetEditor* editor = nullptr;

    if (property.isEnumType() == true) // enumerator type
    {
        editor = new GadgetEditorEnumerator(gadget, property, parent);
    }
    else
    {    // normal items
        switch(property.userType())
        {
            case QMetaType::VoidStar:
                 editor = new GadgetEditorStruct(gadget, property, parent);
            break;
            case QMetaType::Bool:
                 editor = new GadgetEditorBoolean(gadget, property, parent);
            break;
            case QMetaType::Float:     // create float type
            case QMetaType::Double:
                 editor = new GadgetEditorDouble(gadget, property, parent);
            break;
            case QMetaType::UInt:
            case QMetaType::Int:
            case QMetaType::Char:
            case QMetaType::UChar:
            case QMetaType::SChar:
            case QMetaType::Short:
            case QMetaType::UShort:
                  editor = new GadgetEditorInteger(gadget, property, parent);
            default:  // create integer editor;
            break;
        }
    }
    return editor;
}
