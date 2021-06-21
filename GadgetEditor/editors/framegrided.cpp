#include "editors/framegrided.h"
#include <QGridLayout>
#include <QDebug>

FrameGrided::FrameGrided(QWidget *parent) : QFrame(parent)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Plain);
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
    m_layout->setColumnStretch(0,0);
    m_layout->setColumnStretch(1,1); 
    m_layout->setSpacing(3);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
}

FrameGrided::~FrameGrided()
{
   qDebug("%s this=%p", Q_FUNC_INFO, this);
}

QGridLayout * FrameGrided::gridLayout() const
{
    return m_layout;
}

