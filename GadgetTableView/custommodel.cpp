#include "custommodel.h"
#include "gadgets/gadgethelper.h"
#include <QJsonObject>
#include <QDebug>

CustomModel::CustomModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_gadgeHelper(GadgetHelper::getHelper())
{
   auto columnList = m_gadgeHelper->columnList().toVector();
   for(int counter=0; counter < columnList.count(); ++counter)
   {
       m_columns.append(columnList.value(counter).toByteArray());
   } 
}


int CustomModel::rowCount(const QModelIndex & index) const
{
    if (index.parent() != QModelIndex())
    {     
        return 0;
    }   
    return m_numberOfRows;
}


int CustomModel::columnCount(const QModelIndex & index) const
{      
    return m_columns.count();
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{   
    if (index.isValid() == true && role == Qt::DisplayRole)
    {
       auto cell =  m_rows.at(index.row()).at(index.column()); 
       return cell;
    }

    return QVariant();
}

QVariant CustomModel::headerData(int section, Qt::Orientation orientation, int role) const
{  
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
       auto display = m_columns.at(section);      
       return display;
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void CustomModel::setNumberOfRows(int rows)
{
    for(; m_numberOfRows < rows; ++m_numberOfRows)
    {
        QJsonObject fields = m_gadgeHelper->generateModelRow();       
        QVariantList values;
        for(int col=0; col < m_columns.count(); col++)
        {
            auto column = m_columns.at(col);
            auto value = fields.value(column);            
            values.append(value.toVariant());
        }
        m_rows.append(values);
    }
}

int CustomModel::numberOfRows() const
{  
    return m_numberOfRows;
}
