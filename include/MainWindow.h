#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "TableModel.h"

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main window of the application
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent is a pointer to the parent widget
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief onOpenfileClicked is the callback to the openFile button
     *
     * Opens window to choose input file, open the file and fill table by it
     */
    void onOpenfileClicked();

    /**
     * @brief onExecuteClicked is the callback to the execute button
     *
     * Calcutates needed values, such as mean, number of series etc,
     * and displays them into appropriate fields
     */
    void onExecuteClicked();

    /**
     * @brief onClearTableClicked is the callback to the clear button
     *
     * Resets all values and clear the table
     */
    void onClearTableClicked();

    /**
     * @brief onSaveToFileClicked is a callback to the save to file button
     *
     * Open window to choose location and filename to save and
     * write table and all stats into the file
     */
    void onSaveToFileClicked();

    /**
     * @brief setStats fill stats fiels such as mean, number of series, etc
     * @param stats is a instance of {@link Stat} structure with
     * needed values
     */
    void setStats(const Stats& stats);

    /**
     * @brief clearValues if mean-field is not empty, clean fields such as mean, number of series, etc
     */
    void clearValues();

    /**
     * @brief addValues open {@link InputDialog} to fill table manually
     */
    void addValues();

private:
    Ui::MainWindow *ui;
    TableModel* tableModel;
};

#endif // MAINWINDOW_H
