#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "SeriesTable.h"

#include <QAbstractTableModel>
#include <QVector>
#include <QColor>
#include <QIODevice>
#include <QTextStream>
#include <qfile.h>

struct Stats final
{
    double mean;
    size_t numberOfSeries;
    size_t n[2];
    size_t len;
    bool depends;
    int Rmin, Rmax;

    Stats();
    void clear();
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QAbstractTableModel* parent = nullptr);
    bool fill(QFile& file);
    bool fill(QString string);
    void toStream(QTextStream& out) const;
    const Stats& execute();
    void clear();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;

private:
    struct Row
    {
        double value;
        double diff;
        QChar type;
        QColor color;

        Row(double _value = 0) : value(_value), diff(0), type('\0'), color(255, 255, 255) {}
        void setDiff(double diff);
    };

    QVector<Row> rows;
    Stats stats;
    SeriesTable seriesTable;

    void calculateMean();
    void calculateDiff();
    void calculateTheNumberOfSeries();

    bool fillBackend(QTextStream& textStream);
};

#endif // TABLEMODEL_H
