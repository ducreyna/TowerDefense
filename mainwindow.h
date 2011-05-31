#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <exception>

#include "fichier.h"
#include "myqgraphicsscene.h"
#include "eau.h"
#include "pierre.h"
#include "peinture.h"
#include "petanque.h"
#include "defense.h"
#include "joueur.h"

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

private:
    Ui::MainWindow *ui;
    MyQGraphicsScene * S;
    Joueur *J;
    Fichier f;
    QTimer * mainTimer;
    QTimer * vagueTimer;
    int counterVague;
    int** carte;
    QList<Defense*> defenses;
    QVector<Vague *> vagues;
    QList<int> * path;

    void verifierToursConstructibles();

private slots:
    /*!
      * Slot correspondant au clic sur le bouton "Charger carte"
      */
    void on_loadMap_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "Nouvelle vague"
      */
    void on_newWave_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "EAU"
      */
    void on_waterTowers_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "PIERRE"
      */
    void on_stoneTowers_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "PEINTURE"
      */
    void on_paintTowers_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "PETANQUE"
      */
    void on_petanqueTowers_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "Ameliorer"
      */
    void on_upButton_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "Vendre"
      */
    void on_sellButton_clicked();

    /*!
      * Slot correspondant au clic sur le bouton "Pause"
      */
    void on_pause_clicked();

public slots:
    /*!
      * Slot permettant d'ajouter une tour sur la scene
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param type le type de tour que l'on veut creer
      */
    void ajouterTour(int x, int y, std::string type);

    /*!
      * Slot permettant d'ajouter une tour temporairement reproduisant le mouseTracking
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param type le type de tour que l'on veut creer
      */
    void tourMouseTracking(int x, int y,std::string type);

    /*!
      * Slot permettant de renseigner la fenetre principale sur la tour selectionnee sur la scene
      * \param x l'emplacement de la tour suivant l'axe x
      * \param y l'emplacement de la tour suivant l'axe y
      * \param *tour pointeur sur la tour selectionnee
      */
    void tourSelectionnee(int x, int y, QGraphicsItem *tour);

    /*!
      * Slot mettant a jour la vague courante pour les defenses
      */
    void miseAJour();

    /*!
      * Slot indiquant la fin du jeu et donc le joueur a perdu
      */
    void finDuJeu();

signals:
    /*!
      * Signal permettant de diminuer l'argent du joueur suite a l'achat d'une tour
      * \param prix le prix de la tour
      */
    void achatTour(int prix);

    /*!
      * Signal permettant d'augmenter l'argent du joueur suite a la vente d'une tour
      * \param gain le gain engendre
      */
    void venteTour(int gain);
};

#endif // MAINWINDOW_H
