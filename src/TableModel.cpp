#include <QDataStream>
#include <QFile>
#include <QColor>
#include <QDebug>
#include <QColor>

#include "include/TableModel.h"

// Stats
Stats::Stats()
{
    clear();
}

void Stats::clear()
{
    mean = 0.0f;
    numberOfSeries = 0;
    len = 0;
    Rmin = 0;
    Rmax = 0;
    depends = false;
}

// TableModel::Row
void TableModel::Row::setDiff(double diff)
{
    this->diff = diff;
    if (diff > 0.0f)
    {
        type = QChar('>');
        color = QColor::fromRgb(76, 175, 80);
    }
    else if (diff < 0.0f)
    {
        type = QChar('<');
        color = QColor::fromRgb(244, 67, 54);
    }
    else
    {
        type = QChar('=');
    }
}


// TableModel private
void TableModel::calculateMean()
{
    stats.mean = 0.0f;
    stats.len = rows.size();
    for (auto& row : rows)
        stats.mean += row.value/stats.len;
}

void TableModel::calculateDiff()
{
    stats.n[0] = stats.n[1] = 0;
    for (int i = 0; i < rows.size(); i++)
    {
        rows[i].setDiff(rows[i].value - stats.mean);
        if (rows[i].diff  > 0.0f)
            stats.n[0]++;
        else if (rows[i].diff  < 0.0f)
            stats.n[1]++;
    }
}

void TableModel::calculateTheNumberOfSeries()
{
    stats.numberOfSeries = 0;
    for (int i = 1; i < rows.size(); i++)
        if (rows[i].diff == 0 || rows[i].diff * rows[i-1].diff < 0)
            stats.numberOfSeries++;
    stats.numberOfSeries++;
}

bool TableModel::fillBackend(QTextStream& textStream)
{
    double x = 0.0f;
    textStream.skipWhiteSpace();
    if (textStream.atEnd())
        return false;

    beginResetModel();
    while (true)
    {
        textStream >> x;
        if (textStream.status() == QTextStream::Ok)
            rows.push_back(Row(x));
        else
            break;
    }
    endResetModel();

    if (textStream.atEnd())
        return true;

    clear();
    return false;
}

// TableModel public
TableModel::TableModel(QAbstractTableModel* parent) : QAbstractTableModel(parent) {}

bool TableModel::fill(QFile& file)
{
    QTextStream textStream(&file);
    return fillBackend(textStream);
}

bool TableModel::fill(QString string)
{
    QTextStream textStream(&string);
    return fillBackend(textStream);
}

void TableModel::toStream(QTextStream& out) const
{
    out << tr("\tВходная\t\t\tОтклонение\t\tВид отклонения") << endl;
    out << tr("последовательность\tот среднего") << endl;
    for (auto& row : rows)
        out << '\t' << row.value << "\t\t\t\t\t" << row.diff << "\t\t\t\t" << row.type << endl;
    out << endl;
    out << tr("Среднее арифметическое: ") << stats.mean << endl;
    out << tr("Количество серий: ") << stats.numberOfSeries << endl;
    out << "n_1: " << stats.n[0] << " n_2: " << stats.n[1] << " n:" << stats.len << endl;
    out << "R_min: " << stats.Rmin << " R_max: " << stats.Rmax << endl;
}

const Stats& TableModel::execute()
{
    beginResetModel();
    calculateMean();
    calculateDiff();
    calculateTheNumberOfSeries();
    stats.depends = seriesTable.check(stats.n[0], stats.n[1], stats.numberOfSeries, stats.Rmin, stats.Rmax);
    endResetModel();
    return stats;
}

void TableModel::clear()
{
    beginResetModel();
    rows.clear();
    stats.clear();
    endResetModel();
}

// QAbstractItemModel interface
int TableModel::rowCount(const QModelIndex&) const
{
    return rows.size();
}

int TableModel::columnCount(const QModelIndex&) const
{
    if (!stats.len)
        return 1;
    else
        return 3;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
        case Qt::DisplayRole:
        {
            switch (index.column())
            {
                case 0: return QString::number(rows[index.row()].value);
                case 1: return rows[index.row()].type != '\0' ?
                        QString::number(rows[index.row()].diff): QVariant();
                case 2: return rows[index.row()].type;
            }
        }
        case Qt::BackgroundColorRole:
        {
            if (stats.len == 0)
                break;
            return rows[index.row()].color;
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0: return QString("Входная\nпоследовательность");
                case 1: return QString("Отклонение\nот среднего");
                case 2: return QString("Вид отклонения");
            }
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    switch (role)
    {
        case Qt::EditRole:
        {
            rows[index.row()] = Row(value.toDouble());
            emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), 2));
            break;
        }
    }
    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flag = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.column() == 0)
        flag |= Qt::ItemIsEditable;
    return flag;
}
