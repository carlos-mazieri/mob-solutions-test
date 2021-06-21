#include "scrollarea.h"
#include "gridwidget.h"
#include "gadgeteditorfactory.h"
#include "gadgets/player.h"

#include <QGridLayout>
#include <QMessageBox>

ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea(parent)
{    
    m_mainWidget = new GridWidget(this);

    setWidgetResizable(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setWidget(m_mainWidget);
}

ScrollArea::~ScrollArea()
{

}

void ScrollArea::createMetaEditor(void* gadgetObject,
                                  QMetaObject* metaGadgetObject,
                                  QMetaObject* metaStructGadget)
{
    // GadgetEditorFactory does everything
    new GadgetEditorFactory(m_mainWidget,
                            gadgetObject,
                            metaGadgetObject,
                            metaStructGadget);

    // check if there are items available
    if (m_mainWidget->gridLayout()->count() == 0)
    {
        QMessageBox::critical(this,
                              QStringLiteral("Imposible to create the Editor for he Gadget"),
                              QStringLiteral("Perhaps missing to register the data type"));
    }
}
