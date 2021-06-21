#include "gadgets/gadgethelper.h"
#include <QMetaProperty>
#include <QMetaEnum>
#include <QJsonObject>



GadgetHelper::GadgetHelper(QMetaObject *metaGadget, QObject *parent)
    : QObject(parent)
    , m_metaGadget(metaGadget)
    , m_enum_key("NotAvailable")
{

}

QVariantList GadgetHelper::columnList() const
{
    QVariantList cols;
    for (int counter = m_metaGadget->propertyOffset();
                 counter < m_metaGadget->propertyCount(); ++counter)
    {
        QMetaProperty property = m_metaGadget->property(counter);
        if (property.isEnumType() == true
             || property.userType() == QMetaType::Float
             || property.userType() == QMetaType::Double
             || property.userType() == QMetaType::Bool
             || property.userType() == QMetaType::Int
             || property.userType() == QMetaType::UInt
             || property.userType() == QMetaType::Char
             || property.userType() == QMetaType::UChar
             || property.userType() == QMetaType::Short
             || property.userType() == QMetaType::UShort)
        {
            cols.append(property.name());
        }
    }
    return cols;
}

QJsonObject GadgetHelper::generateModelRow()
{
    QJsonObject row;
    for (int counter = m_metaGadget->propertyOffset();
                  counter < m_metaGadget->propertyCount(); ++counter)
    {
         QMetaProperty property = m_metaGadget->property(counter);
         if (property.isEnumType() == true) // enumerator type
         {
             if (m_enum_values.isEmpty() == true)
             {
                 auto metaEnum = property.enumerator();
                 for(int counter = 0; counter < metaEnum.keyCount(); ++counter)
                 {
                     m_enum_values.append(metaEnum.key(counter));
                 }
                 if (m_enum_values.isEmpty() == false)
                 {
                     m_enum_key = m_enum_values.first();
                 }
             }
             row.insert(property.name(), QJsonValue(m_enum_key));
         }
         else
         {
         // normal items
               switch(property.userType())
               {
                   case QMetaType::Bool:
                        row.insert(property.name(), QJsonValue(m_bool_value));
                   break;

                   case QMetaType::Float:     // create float type
                   case QMetaType::Double:
                        row.insert(property.name(), QJsonValue(m_float_value));
                   break;

                   case QMetaType::UInt:
                   case QMetaType::Int:
                        row.insert(property.name(), QJsonValue(m_int_value));
                   break;

                   case QMetaType::Char:
                   case QMetaType::UChar:
                   case QMetaType::SChar:
                        row.insert(property.name(), QJsonValue(m_char_value));
                   break;

                   case QMetaType::Short:
                   case QMetaType::UShort:
                        row.insert(property.name(), QJsonValue(m_short_value));
                   break;
                   default:  // create integer editor;
                   break;
               }
         }
     }
     generateFuzzyValues();
     return row;
}

void GadgetHelper::generateFuzzyValues()
{
    m_float_value += 0.5;
    m_char_value  += 1;
    m_short_value += 2;
    m_int_value   += 4;
    bool toggle_bool = !m_bool_value;
    m_bool_value = toggle_bool;
    if (++m_current_enum_index >= m_enum_values.count())
    {
        m_current_enum_index = 0;
    }
    if (m_enum_values.isEmpty() == false)
    {
        m_enum_key = m_enum_values.at(m_current_enum_index);
    }
}

