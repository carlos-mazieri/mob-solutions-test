#ifndef P2D_H
#define P2D_H

#include <QObject>
#include <QPair>

struct P2D
{
    Q_GADGET
    Q_CLASSINFO("itemName", "coordinate")
 public:
    virtual ~P2D();

    Q_PROPERTY(float x READ xPoint WRITE setXpoint)
    Q_PROPERTY(float y READ yPoint WRITE setYpoint)

    Q_INVOKABLE float xPoint() const;
    Q_INVOKABLE void  setXpoint(float value);
    Q_INVOKABLE float yPoint() const;
    Q_INVOKABLE void  setYpoint(float value);

    float m_x = 0.0;
    float m_y = 0.0;

};
Q_DECLARE_METATYPE(P2D)

#endif // P2D_H
