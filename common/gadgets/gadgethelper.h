#ifndef GADGEHELPER_H
#define GADGEHELPER_H

#include <QObject>
#include <QMetaObject>
#include <QVariantList>
#include <QJsonObject>
#include <QString>


class GadgetHelper : public QObject
{
    Q_OBJECT
public:
    explicit GadgetHelper(QMetaObject * metaGadget, QObject *parent = nullptr);   
    Q_INVOKABLE QVariantList      columnList() const;
    Q_INVOKABLE QJsonObject       generateModelRow();
private:
    void generateFuzzyValues();
private:
    QMetaObject * m_metaGadget        = nullptr;
    QStringList   m_enum_values;
    QString       m_enum_key;
    int           m_current_enum_index = 0;
    float         m_float_value = 0.0;
    bool          m_bool_value  = true;
    quint8        m_char_value  = 0;
    short         m_short_value = 0;
    int           m_int_value   = 0;
};


#endif // GADGEHELPER_H
