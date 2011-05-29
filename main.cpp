#include <QApplication>
#include <QDesktopWidget>

#include <iostream>
#include "fichier.h"
#include "mainwindow.h"

using namespace TOWERDEFENSE;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setFixedSize(879,610);

        /*  CENTRER FENETRE PAR RAPPORT À L'ECRAN   */
    QDesktopWidget *widget = QApplication::desktop();
    int desktop_width = widget->width();
    int desktop_height = widget->height();
    int x = desktop_width / 2 - 879 / 2;
    int y = desktop_height / 2 - 610 / 2 - 25;
    w.move(QPoint(x, y));

    w.show();

    return app.exec();
}
