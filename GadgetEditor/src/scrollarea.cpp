#include "scrollarea.h"
#include "gridwidget.h"
#include "gadgeteditorfactory.h"
#include "gadgets/player.h"
#include "jsongenerator.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>

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


void ScrollArea::saveJsonFile(bool ok)
{
    Q_UNUSED(ok);
    if (m_mainWidget->gridLayout()->count()  == 0)
    {
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as Json"),
                               QDir::homePath(),
                               tr("Json files (*.json"));
    QLatin1String jsonSuffix("json");
    if (QFileInfo(fileName).suffix() != jsonSuffix)
    {
        fileName += QLatin1Char('.') + jsonSuffix;
    }
    if (fileName.isEmpty() == false)
    {
        QFile jsonFile(fileName);
        bool saved = false;
        if (jsonFile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text) == true)
        {
            JsonGenerator json;
            auto data = json.generate(m_mainWidget);
            if (jsonFile.write(data) == data.size())
            {
                saved = true;
                jsonFile.close();
            }
        }
        if ( saved == false)
        {
            QMessageBox::critical(this,
                                  QStringLiteral("Could not create Json file"),
                                  QStringLiteral("Check the disk space and write permissions"));
        }
    }
}
