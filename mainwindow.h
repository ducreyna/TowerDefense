#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>

#include <iostream>
#include "fichier.h"
#include "cafard.h"
#include "fourmi.h"
#include "myqgraphicsscene.h"
#include "eau.h"
#include "pierre.h"
#include "peinture.h"
#include "petanque.h"

using namespace TOWERDEFENSE;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ChargerGraphiques();

private:
    Ui::MainWindow *ui;
    MyQGraphicsScene * S;
    Fichier f;
    int** carte;
    double** vague;

    QTimer* timer;

private slots:
    void on_loadMap_clicked();
    void on_newWave_clicked();
    void on_waterTowers_clicked();
    void on_stoneTowers_clicked();
    void on_paintTowers_clicked();
    void on_petanqueTowers_clicked();

public slots:
    void ajouterTour(int x, int y, std::string type);
    void tourMouseTracking(int x, int y,std::string type);

};

#endif // MAINWINDOW_H
