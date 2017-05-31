#include "InputDialog.h"
#include "ui_InputDialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    setWindowTitle("Ввод данных");
}

InputDialog::~InputDialog()
{
    delete ui;
}

QString InputDialog::getInput() const
{
    return ui->textEdit->toPlainText();
}
