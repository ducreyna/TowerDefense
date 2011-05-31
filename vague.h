#ifndef VAGUE_H
#define VAGUE_H

#include <string>
#include "insecte.h"
#include "insectefactory.h"
#include <QVector>
#include <QTimer>
#include "myqgraphicsscene.h"

using namespace std;

namespace TOWERDEFENSE {

 class Vague : public QObject
{
     Q_OBJECT
public:
    Vague();

    /*!
      * Methode virtuelle pure construisant la vague
      * \param initX le depart selon l'axe x
      * \param initY le depart selon l'axe y
      * \param *path pointeur sur la liste contenant le path(chemin)
      * \param *scene pointeur sur la scene du jeu
      */
    virtual void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene* scene) = 0;

    /*!
      * Methode virtuelle pure renvoyant les insectes sur la scene
      * \param onlyOnScene insectes uniquement sur la scene
      * \return QVector<Insecte*> vecteur d'insectes present sur la scene
      */
    virtual QVector<Insecte *> getInsectes(bool onlyOnScene = false) = 0;

    /*!
      * Methode virtuelle pure permettant de lancer la vague d'ennemis sur la scene
      */
    virtual void launchVague() = 0;

    /*!
      * Methode virtuelle pure permettant de stopper la vague d'ennemis sur la scene
      */
    virtual void stopVague() = 0;

signals:
    /*!
      * Signal envoye quand les insectes sur la scene ont ete mis a jour
      */
    void miseAJour();

};

class VagueCompose : public Vague
{
Q_OBJECT
private:
    QVector<Vague *> composition;

public:
    /*!
      * Constructeur parametre
      * \param QVector<Vague*> liste des vagues qui composent cette vague
      */
    VagueCompose(QVector<Vague *>);

    /*!
      * Methode construisant la vague
      * \param initX le depart selon l'axe x
      * \param initY le depart selon l'axe y
      * \param *path pointeur sur la liste contenant le path(chemin)
      * \param *scene pointeur sur la scene du jeu
      */
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);

    /*!
      * Methode renvoyant les insectes sur la scene
      * \param onlyOnScene insectes uniquement sur la scene
      * \return QVector<Insecte*> vecteur d'insectes present sur la scene
      */
    QVector<Insecte *> getInsectes(bool onlyOnScene = false);

    /*!
      * Methode permettant de lancer la vague d'ennemis sur la scene
      */
    void launchVague();

    /*!
      * Methode permettant de stopper la vague d'ennemis sur la scene
      */
    void stopVague();
};

class VagueConcrete : public Vague
{ Q_OBJECT
private:
    int type;
    int nombre;
    double taille;
    int intervalle;
    int counterInsecte;
    QTimer * timer;
    string commentaire;
    QVector<Insecte *> insectes;
    MyQGraphicsScene * scene;

public:
    /*!
      * Constructeur parametre
      * \param type type de l'insecte a cree
      * \param nombre le nombre d'insectes a creer
      * \param intervalle intervalle entre chaque depart d'insecte
      * \param commentaire le commentaire sur la vague
      */
    VagueConcrete(int type, int nombre, double taille, int intervalle, string commentaire);

    /*!
      * Methode construisant la vague
      * \param initX le depart selon l'axe x
      * \param initY le depart selon l'axe y
      * \param *path pointeur sur la liste contenant le path(chemin)
      * \param *scene pointeur sur la scene du jeu
      */
    void buildVague(int initX,int initY, QList<int> * path, MyQGraphicsScene * scene);

    /*!
      * Methode renvoyant les insectes sur la scene
      * \param onlyOnScene insectes uniquement sur la scene
      * \return QVector<Insecte*> vecteur d'insectes present sur la scene
      */
    QVector<Insecte *> getInsectes(bool onlyOnScene = false);

    /*!
      * Methode permettant de lancer la vague d'ennemis sur la scene
      */
    void launchVague();

    /*!
      * Methode permettant de stopper la vague d'ennemis sur la scene
      */
    void stopVague();

public slots:
    /*!
      * Slot permettant d'ajouter une insecte sur la scene
      */
    void ajouterInsecte();

    /*!
      * Slot permettant d'ajouter des insectes enfants suite a la destruction d'un parent
      * \param type type de l'insecte a cree
      * \param taille la taille de l'insecte
      * \param x l'emplacement de l'insecte selon l'axe x
      * \param y l'emplacement de l'insecte selon l'axe y
      * \param *path pointeur sur la liste contenant le path(chemin)
      * \param counter compteur permettant de savoir où se positionner dans le path(chemin)
      * \param numEnfant le numero de l'enfant a creer
      */
    void ajouterInsecteEnfant(int type,double taille,int x, int y,QList<int> *path,int counter,int numEnfant);

    /*!
      * Slot permettant de supprimer un insecte de la scene
      * \param *I pointeur sur l'insecte a supprimer
      * \param vivant true = l'insecte a atteint le but    false = l'insecte a ete detruit par une tour
      */
    void supprimerInsecte(Insecte* I,bool vivant);

signals:
    /*!
      * Signal emis quand les defenses doivent être mis a jour
      */
    void miseAJour();
};

}

#endif // VAGUE_H
