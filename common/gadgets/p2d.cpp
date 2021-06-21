#include "gadgets/p2d.h"
#include <QDebug>

P2D::~P2D()
{
    qDebug("%s this=%p", Q_FUNC_INFO, this);
}

float P2D::xPoint() const
{
    return m_x;
}

void P2D::setXpoint(float value)
{
    m_x = value;
    qDebug() << Q_FUNC_INFO << "m_x:" << m_x;
}

float P2D::yPoint() const
{
    return m_y;
}

void P2D::setYpoint(float value)
{
    m_y  = value;
    qDebug() << Q_FUNC_INFO << "m_y:" << m_y;
}

