#ifndef PLAYER_H
#define PLAYER_H

#include "gadgets/p2d.h"

#include <QObject>


struct Player
{
    Q_GADGET
 public:
    enum class PlayerType   // declared that embedded in order to have QMetaProperty::isEnumType() == true
    {
        NO_TYPE = 0,
        TANK,
        CHARACTER,
        SHIP
    };
    Q_ENUM(PlayerType)

    Player();
    virtual ~Player();

    Q_PROPERTY(PlayerType playerType READ playerType WRITE setPlayerType)
    Q_PROPERTY(float      speed READ speed WRITE setSpeed)
    Q_PROPERTY(quint16    ammunition READ ammunition WRITE setAmmunition)
    Q_PROPERTY(bool       active READ active WRITE setActive)
    Q_PROPERTY(quint8     numberOfCoordinates READ numberOfCoordinates WRITE setNumberOfCoordinates)
    Q_PROPERTY(void*      coordinates READ coordinates)

    Q_INVOKABLE float      speed() const;
    Q_INVOKABLE void       setSpeed(float speed);
    Q_INVOKABLE PlayerType playerType() const;
    Q_INVOKABLE void       setPlayerType(PlayerType type);
    Q_INVOKABLE quint16    ammunition() const;
    Q_INVOKABLE void       setAmmunition(quint16 value);
    Q_INVOKABLE bool       active() const;
    Q_INVOKABLE void       setActive(bool value);
    Q_INVOKABLE quint8     numberOfCoordinates() const;
    Q_INVOKABLE void       setNumberOfCoordinates(quint8 value);
    Q_INVOKABLE void*      coordinates();

    PlayerType m_playerType       = PlayerType::NO_TYPE;
    float m_speed                 = 0.0;
    quint16 m_ammunition          = 0;
    bool m_active                 = false;
    quint8 m_numberOfCoordinates  = 0;

 private:
    /*!
     * \brief m_coordinatesList is used to handle the list of elements
     */
    P2D * m_coordinatesList[256]  = {0};

    void  reduceCoordinateItems(int totalIems);
};
Q_DECLARE_METATYPE(Player)


#endif // PLAYER_H
