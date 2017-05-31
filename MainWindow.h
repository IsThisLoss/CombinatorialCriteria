#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "TableModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpenfileClicked();
    void onExecuteClicked();
    void onClearTableClicked();
    void onSaveToFileClicked();
    void setStats(const Stats& stats);
    void clearValues();
    void addValues();

private:
    Ui::MainWindow *ui;
    TableModel* tableModel;
};

#endif // MAINWINDOW_H
