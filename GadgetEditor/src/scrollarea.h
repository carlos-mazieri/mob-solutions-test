#ifndef WIDGET_H
#define WIDGET_H

#include <QScrollArea>
class GridWidget;

class ScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea();

    void createMetaEditor(void *gadgetObject,
                          QMetaObject *metaGadgetObject,
                          QMetaObject *metaStructGadget);
public slots:
    void  saveJsonFile(bool ok);
private:
    GridWidget*   m_mainWidget;
};
#endif // WIDGET_H
