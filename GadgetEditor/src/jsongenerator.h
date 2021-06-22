#ifndef JSONGENERATOR_H
#define JSONGENERATOR_H

#include <QJsonObject>
class QWidget;

class JsonGenerator
{
public:
    struct NestedGadget
    {
        NestedGadget()
        {
            wdget = nullptr;
        }
        QObject *wdget;
        QJsonObject  content;
    };
    JsonGenerator();    
    virtual ~JsonGenerator();
public:
    QByteArray  generate(QWidget *parent);
private:
    QJsonObject  walkDownWidget(QObject *parent, bool recursive = true);
    bool         isContainerWidget(QObject *widget) const;
    bool         isGadgetEditor(QObject *object) const;
    QObject  *   m_lasCointaner = nullptr;
    int          m_group_counter = 0;
};

#endif // JSONGENERATOR_H
