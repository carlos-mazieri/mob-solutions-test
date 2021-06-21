#ifndef GADGETEDITORFACTORY_H
#define GADGETEDITORFACTORY_H

#include <editors/gadgeteditor.h>

#include <QObject>
#include <QVector>

class GadgetEditor;
class FrameGrided;
class GadgetEditorStruct;

class GadgetEditorFactory : public QObject
{
    Q_OBJECT
public:
    GadgetEditorFactory(FrameGrided *parent,
                        void *mainGadget,
                        QMetaObject* metaGadgetObject,
                        QMetaObject *metaStructGadge);
    ~GadgetEditorFactory();
private slots:
     void onCounterItemsChanged();
private:
     void createMainEditors(FrameGrided *parent, void* mainGadget, QMetaObject* metaGadgetObject);

     void createStructEditorItem(int index);
     /*!
      * \brief putMainItemEditorOnParent makes the editor visible on its parent
      */
     void putMainItemEditorOnParent(GadgetEditor* editorObject);
     void putMainStructEditorOnParent(QWidget *customLabel, FrameGrided *subFrame);
     void *getStructObjectAddr(int index) const;
     void removeLastStructEditorItem();
private:
    GadgetEditor* privateCreateEditor(FrameGrided* parent, void *gadget, QMetaProperty property);
    GadgetEditor*       m_editorCounter = nullptr;  // this is the counter
    GadgetEditorStruct* m_editorStruct  = nullptr;  // this is the array struct
    QString       m_labelStructItem;    // default label plus a counter for each object on struct
    QMetaObject * m_metaGadgetStruct;   // meta Object to create
    FrameGrided * m_frameStruct = nullptr;
    // keep internal counter as QLayoutGrid::rowCounter() seems to always start with 1
    int           m_itemsOnGrid = 0;
};

#endif // GADGETEDITORFACTORY_H

