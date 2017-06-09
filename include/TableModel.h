#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "SeriesTable.h"

#include <QAbstractTableModel>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QColor>

/**
 * @struct Stats
 * @brief The Stats struct is the structure which stores the stats about table:
 * mean, number of series, n_1 and n_2, n, R_min, R_max and result whether there is
 * systematic error
 */
struct Stats final
{
    double mean;
    size_t numberOfSeries;
    size_t n[2];
    size_t len;
    bool depends;
    int Rmin, Rmax;

    /**
     * @brief Stats is the default ctor, calls {@link clear}
     */
    Stats();

    /**
     * @brief clear function which clears all fields of the structure
     */
    void clear();
};


/**
 * @class TableModel
 * @brief The TableModel class is a model (from MVC) for an QTableView
 *
 */
class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * @brief TableModel is the default ctor
     * @param parent is a pointer to the parent object
     */
    TableModel(QAbstractTableModel* parent = nullptr);

    /**
     * @brief fill the table model by file
     * @param file is a file to read from
     * @return if table was successfully filled returns true, false otherwise
     */
    bool fill(QFile& file);

    /**
     * @brief fill the table model by string buffer
     * @param string is a string to read from
     * @return if table was successfully filled returns true, false otherwise
     */
    bool fill(QString string);

    /**
     * @brief toStream flushs the table and values froms {@link stats} into text stream
     * @param out is a stream to write to
     */
    void toStream(QTextStream& out) const;

    /**
     * @brief execute calculates values and fill {@link Stats} structure
     * @return {@link Stats} structure with needed values
     */
    const Stats& execute();

    /**
     * @brief clear the table ans stats
     */
    void clear();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;

private:
    /**
     * @struct Row
     * @brief The Row struct is a structure to store single row of the table
     * it includes values, deviation from mean and type of deviation
     */
    struct Row
    {
        double value; // value
        double diff; // defiation from mean
        QChar type; // type of deviation
        QColor color;

        Row(double _value = 0) : value(_value), diff(0), type('\0'), color(255, 255, 255) {}

        /**
         * @brief setDiff sets deviation and type of the one
         * @param diff is a deviation from mean of the values
         */
        void setDiff(double diff);
    };


    /**
     * @brief rows is a vector of {@link Row} structure
     */
    QVector<Row> rows;

    /**
     * @brief stats is a instance of {@link Stats} structure
     */
    Stats stats;

    /**
     * @brief seriesTable is a instance of {@link SeriesTable} class
     */
    SeriesTable seriesTable;

    /**
     * @brief calculateMean calculates mean values
     * and sets it into {@link Stats} structure
     */
    void calculateMean();

    /**
     * @brief calculateDiff calculates deviation from mean and
     * sets it into {@link Stats} structure
     */
    void calculateDiff();

    /**
     * @brief calculateTheNumberOfSeries calculate the number of series and
     * sets in into {@link Stats} structure
     */
    void calculateTheNumberOfSeries();

    /**
     * @brief fillBackend is a backend of fill functions
     * @param textStream is a stream to read from
     * @return true on success, false otherwise
     */
    bool fillBackend(QTextStream& textStream);
};

#endif // TABLEMODEL_H
