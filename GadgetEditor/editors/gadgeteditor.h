#ifndef GADGETEDITOR_H
#define GADGETEDITOR_H

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>

class FrameGrided;

/*!
 * \brief The GadgetEditor class is an abstract class to edit all different types of items
 *
 *   Each editable property from a Gadget object will have sub class of GadgetEditor assigned to each.
 *
 *   The editor() method returns the widget suitable for each property.
 *
 *   Subclasses are responsible to write the data from editor() into the gadget.
 *
 *   Both label() and editor() widgets are put together on a FrameGrided widget
 */
class GadgetEditor : public QObject
{
    Q_OBJECT

public:
    explicit GadgetEditor(void *gadget, const QMetaProperty property, FrameGrided *parentWidget = nullptr);
    ~GadgetEditor();
    QWidget*      label() const;
    QWidget*      editor() const;
    FrameGrided*  parentWidget() const;
    const char *  name() const;
    virtual QVariant read() const;
protected:    
    void write(const QVariant& data);
    /*!
     * \brief createEditor this is the Widget for data editing
     */
    virtual void createWidgetEditor() = 0;
    /*!
     * \brief createLabel creates the widget containg the label of the item
     */
    virtual void createLabel();
signals:
    void dataChanged(); // emitted after write operations
protected:
    QWidget * m_label = nullptr;
    QWidget * m_editor = nullptr;
    FrameGrided * m_parentWidget;
    const QMetaProperty m_property;
    void*  m_gadget;
};



#endif // GADGETEDITOR_H
