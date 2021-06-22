#include "scrollarea.h"
#include "gadgets/p2d.h"
#include "gadgets/player.h"

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>


void setMainWindow(QMainWindow* window, ScrollArea * mainWidget)
{
    window->setContentsMargins(8, 30, 8, 8);
    auto menubar = new QMenuBar(window);
    menubar->setGeometry(QRect(0, 0, 800, 30));
    auto menuFile = menubar->addMenu("&File");
    auto saveAction = new QAction("Save as Json ..", menubar);
    menuFile->addAction(saveAction);
    QObject::connect(saveAction, SIGNAL(triggered(bool)),
                     mainWidget, SLOT(saveJsonFile(bool)));
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Player>("Player");
    qRegisterMetaType<P2D>("P2D");
    QMainWindow  window;
    ScrollArea w(&window);
    window.setCentralWidget(&w);
    setMainWindow(&window, &w);
    Player playeObject;
    w.createMetaEditor(&playeObject,
                       const_cast<QMetaObject*> (&Player::staticMetaObject),
                       const_cast<QMetaObject*> (&P2D::staticMetaObject));
    window.show();
    return a.exec();
}
