/**
 * @mainpage
 * @author <a href="http://github.com/isthisloss">
 *              IsThisLoss (a.k.a. Dmitry Kopturov)
 *         </a>
 * @copyright Do what you want, but you must reference to the original code
 * (this is it)
 * @version 0.9-rc
 *
 * @abstract This is a program to check whether input sequence of values
 * contains systematic error or not via combinatorial criteria.
 * @endabstract
 *
 */


#include "include/MainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
