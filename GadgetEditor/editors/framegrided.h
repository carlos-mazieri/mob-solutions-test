#ifndef FRAMEGRIDED_H
#define FRAMEGRIDED_H

#include <QFrame>
class QGridLayout;

class FrameGrided : public QFrame
{
    Q_OBJECT
public:
    explicit FrameGrided(QWidget *parent = nullptr);
    ~FrameGrided();
public:
    QGridLayout * gridLayout() const;
private:
    QGridLayout * m_layout;
};

#endif // FRAMEGRIDED_H
