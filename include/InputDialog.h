#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

/**
 * @class InputDialog
 * @brief The InputDialog class represents a window to manually input of values
 */
class InputDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief InputDialog is a default ctor auto-generated by Qt
     * @param parent is pointer to the parent widget
     */
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();

    /**
     * @brief getInput returns the input sequence
     * @return Entered into textEdit text
     */
    QString getInput() const;
private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
