#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "include/InputDialog.h"
#include "include/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Комбинаторный критерий систематической погрешности");
    ui->execute->setDisabled(true);
    ui->saveToFile->setDisabled(true);

    tableModel = new TableModel;
    ui->table->setModel(tableModel);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(tableModel, &TableModel::dataChanged, this, &MainWindow::clearValues);

    connect(ui->openFile, &QPushButton::clicked, this, &MainWindow::onOpenfileClicked);
    connect(ui->execute, &QPushButton::clicked, this, &MainWindow::onExecuteClicked);
    connect(ui->saveToFile, &QPushButton::clicked, this, &MainWindow::onSaveToFileClicked);

    connect(ui->clearTable, &QPushButton::clicked, this, &MainWindow::onClearTableClicked);
    connect(ui->add, &QPushButton::clicked, this, &MainWindow::addValues);
}

MainWindow::~MainWindow()
{
    delete tableModel;
    delete ui;
}

void MainWindow::onOpenfileClicked()
{
    // http://doc.qt.io/qt-5/qfiledialog.html#details
    auto path = QFileDialog::getOpenFileName(this, "Выберете файл с входными данными",
                                                   QDir::homePath(), "Text files (*txt)");

    if (path.isEmpty())
        return;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Critical, "Ошибка", "Не удалось открыть файл").exec();
        return;
    }
    tableModel->fill(file);
    file.close();
    ui->execute->setEnabled(true);
}

void MainWindow::onExecuteClicked()
{
    ui->execute->setStyleSheet("font-weight: regular");

    setStats(tableModel->execute());
    ui->saveToFile->setEnabled(true);
}

void MainWindow::setStats(const Stats& stats)
{
    ui->mean->setText(QString::number(stats.mean));
    ui->numberOfSeries->setText(QString::number(stats.numberOfSeries));
    ui->n1->setText(QString::number(stats.n[0]));
    ui->n2->setText(QString::number(stats.n[1]));
    ui->n3->setText(QString::number(stats.len));
    ui->Rmin->setText(QString::number(stats.Rmin));
    ui->Rmax->setText(QString::number(stats.Rmax));


    switch (stats.depends)
    {
        case 1:
        {
            ui->result->setText("Здесь присутствует систематическая погрешность");
            ui->result->setStyleSheet("background-color: rgb(76, 175, 80)");
            break;
        }
        case 0:
        {
            ui->result->setText("Систематическая погрешность отсутствует");
            ui->result->setStyleSheet("background-color: rgb(244, 67, 54)");
            break;
        }
        default:
        {
            ui->result->setText("Невозможно определить наличие\nсистематической погрешности");
            ui->result->setStyleSheet("background-color: white");
            break;
        }
    }
}

void MainWindow::clearValues()
{
    if (!ui->mean->text().isEmpty())
    {
        ui->mean->clear();
        ui->numberOfSeries->clear();
        ui->n1->clear();
        ui->n2->clear();
        ui->n3->clear();
        ui->Rmin->clear();
        ui->Rmax->clear();

        ui->result->clear();
        ui->result->setStyleSheet("");

        ui->execute->setStyleSheet("font-weight: bold");
    }
}

void MainWindow::onClearTableClicked()
{
    clearValues();
    tableModel->clear();
    ui->execute->setDisabled(true);
    ui->saveToFile->setDisabled(true);
}

void MainWindow::onSaveToFileClicked()
{
    auto path = QFileDialog::getSaveFileName(this, "Сохранить", QDir::homePath(), "Text files (*txt)");

    QFile save(path);
    if (!save.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox(QMessageBox::Critical, "Ошибка", "Не удалось открыть файл для записи").exec();
        return;
    }
    QTextStream out(&save);
    tableModel->toStream(out);
    out << ui->result->text();
    save.close();
}

void MainWindow::addValues()
{
    InputDialog input;

    if (input.exec() == QDialog::Accepted)
    {
        if (tableModel->fill(input.getInput()))
            ui->execute->setEnabled(true);
        else
            QMessageBox(QMessageBox::Critical, "Ошибка", "Не удалось считать данные").exec();
    }
}
