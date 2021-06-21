#include "gadgets/player.h"

#include <QDebug>

/*!
 * for debbuging purposes initialize coordinates with randmic values
 */
#define INIT_COORDINATE_VALUES  1

Player::Player()
{

}

Player::~Player()
{
    qDebug("%s this=%p", Q_FUNC_INFO, this);
    reduceCoordinateItems(0);
}

float Player::speed() const
{
    return m_speed;
}

void Player::setSpeed(float speed)
{
    m_speed = speed;
    qDebug() << Q_FUNC_INFO << "m_speed:" << m_speed;
}

Player::PlayerType Player::playerType() const
{
    return m_playerType;
}

void Player::setPlayerType(PlayerType type)
{
    m_playerType = type;
    qDebug() << Q_FUNC_INFO << "m_playerType:" << m_playerType;
}

quint16 Player::ammunition() const
{
    return m_ammunition;
}

void Player::setAmmunition(quint16 value)
{
    m_ammunition = value;
    qDebug() << Q_FUNC_INFO << "m_ammunition" << m_ammunition;
}

bool Player::active() const
{
    return m_active;
}

void Player::setActive(bool value)
{
    m_active = value;
    qDebug() << Q_FUNC_INFO << "m_active:" << m_active;
}

quint8 Player::numberOfCoordinates() const
{
    return m_numberOfCoordinates;
}

void Player::setNumberOfCoordinates(quint8 value)
{
    if (value > m_numberOfCoordinates)
    {

        for(; m_numberOfCoordinates < value; m_numberOfCoordinates++)
        {
            P2D *item = new P2D();
#if INIT_COORDINATE_VALUES
            {
                static float defaultValue = 0.0;
                item->m_y = defaultValue;
                defaultValue += 0.5;
                item->m_x = defaultValue;
                defaultValue += 0.5;
            }
#endif
            m_coordinatesList[m_numberOfCoordinates] = item;
            qDebug("%s added item [%d] item=%p x=%f y=%f", Q_FUNC_INFO, m_numberOfCoordinates, item, item->m_x, item->m_y);
        }
    }
    else if (value < m_numberOfCoordinates)
    {
        reduceCoordinateItems(value);
    }   
}

void*  Player::coordinates()
{
    P2D** array = &m_coordinatesList[0];
    void* ptr = reinterpret_cast<void*>(array);
    qDebug() << Q_FUNC_INFO << "address:" << array;
    return ptr;
}

void Player::reduceCoordinateItems(int totalIems)
{
    for(; m_numberOfCoordinates > totalIems; m_numberOfCoordinates--)
    {
        P2D* item = m_coordinatesList[m_numberOfCoordinates -1];
        qDebug("%s deleting item[%d] address=%p", Q_FUNC_INFO, m_numberOfCoordinates -1, item);
        m_coordinatesList[m_numberOfCoordinates -1] = nullptr;
        delete item;
    }
}

