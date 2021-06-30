#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <QStringList>
#include <QAbstractTableModel>
#include <QHash>

class GadgetHelper;



class CustomModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int numberOfRows READ numberOfRows WRITE setNumberOfRows)

public:
    CustomModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,  int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
public:
    Q_INVOKABLE int numberOfRows() const;
public slots:
    void setNumberOfRows(int rows);
private:
    GadgetHelper      * m_gadgeHelper;
    QList<QByteArray>   m_columns;
    int                 m_numberOfRows = 0;
    QList<QVariantList> m_rows;  // each record is a QVariantList
};
#endif // CUSTOMMODEL_H
