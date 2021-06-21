#include "scrollarea.h"
#include "gadgets/p2d.h"
#include "gadgets/player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Player>("Player");
    qRegisterMetaType<P2D>("P2D");
    ScrollArea w;
    Player playeObject;
    w.createMetaEditor(&playeObject,
                       const_cast<QMetaObject*> (&Player::staticMetaObject),
                       const_cast<QMetaObject*> (&P2D::staticMetaObject));
    w.show();
    return a.exec();
}
