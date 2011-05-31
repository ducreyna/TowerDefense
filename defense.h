#ifndef DEFENSE_H
#define DEFENSE_H

#include <QMessageBox>
#include <QTimer>
#include <QList>
#include <QObject>
#include <math.h>

#include "constantes.h"
#include "insecte.h"
#include "vague.h"
#include "entite.h"
#include "projectile.h"

namespace TOWERDEFENSE{

class Defense : public Entite
{
    Q_OBJECT
protected:
    double niveau;
    double  portee;
    double cadence;
    double frappe;
    int cout;
    int amelioration_1;
    int amelioration_2;
    Type_projectile projectile;
    double vitesse;
    bool isShooting;
    QTimer *shootTimer;
    Vague * currentWave;
    Insecte * currentTarget;
    QList<QPixmap*> etatTour;

    /*!
      * Methode permettant l'animation de l'item sur la scene
      * \param phase la phase d'appel de l'item
      */
    void advance(int phase);

public:
    /*!
      * Constructeur par defaut de la classe defense
      */
    Defense();

    /*!
      * Constructeur parametre de la classe defense
      * \param niveau le niveau de la defense lors de la creation
      * \param portee la portee de la defense
      * \param cadence la cadence de la defense
      * \param frappe les degats causes par un projectile issu de cette defense
      * \param cout le cout total d'une defense
      * \param amelioration_1 le cout de la premiere amelioration
      * \param amelioration_2 le cout de la deuxieme amelioration
      * \param vitesse la vitesse du projectile issu de la defense
      * \param parent l'item parent initialise a 0
      * \param projectile le type de projectile tire
      */
    Defense(const double niveau,const double portee,const double cadence, const double frappe,const int cout,const int amelioration_1,const int amelioration_2, const double vitesse,const Type_projectile projectile,QGraphicsItem *parent=0);

    /*!
      * Destructeur de la classe
      */
    virtual ~Defense();

    /*!
      * Methode virtuelle pure renvoyant la frappe de la defense
      * \return double la valeur de la frappe
      */
    virtual double attaquer() = 0;

    /*!
      * Methode virtuelle pure permettant d'ameliorer la defense
      * \return bool true = amelioration reussie    false = amelioration interdite
      */
    virtual bool ameliorer() = 0;

    /*!
      * Accesseur constant renvoyant le niveau de la defense
      * \return double le niveau de la defense
      */
    double getNiveau()const;

    /*!
      * Accesseur constant renvoyant la portee de la defense
      * \return double la portee de la defense
      */
    double getPortee()const;

    /*!
      * Accesseur constant inline renvoyant la valeur de la frappe (les degats causes)
      * \return double la valeur de la frappe
      */
    inline double getFrappe() const { return this->frappe; }

    /*!
      * Accesseur constant inline renvoyant la vitesse du projectile
      * \return double la vitesse du projectile
      */
    inline double getVitesseProjectile() const { return this->vitesse; }

    /*!
      * Accesseur constant inline renvoyant le type de projectile lance
      * \return Type_projectile le type de projectile
      */
    inline Type_projectile getTypeProjectile() const { return this->projectile; }

    /*!
      * Accesseur renvoyant le cout total de la defense
      * \return int le cout total de la defense
      */
    int getCout()const;

    /*!
      * Accesseur renvoyant le cout de la premiere amelioration
      * \return int le cout de la premiere amelioration
      */
    int getAmelioration_1()const;

    /*!
      * Accesseur renvoyant le cout de la deuxieme amelioration
      * \return int le cout de la deuxieme amelioration
      */
    int getAmelioration_2()const;

    /*!
      * Accesseur renvoyant la vague courante d'insectes
      * \return Vague* la vague courante
      */
    Vague* getCurrentWave()const;

    /*!
      * Accesseur modifiant la vague courante
      * \param *currWave la nouvelle vague courante
      */
    inline void setCurrentWave(Vague * currWave) { this->currentWave = currWave; }

    /*!
      * Accesseur modifiant la cible courante
      * \param *target le nouvelle insecte a cibler
      */
    inline void setCurrentTarget(Insecte * target) { this->currentTarget = target; }

    /*!
      * Accesseur constant inline renvoyant la cible courante
      * \return Insecte* un pointeur sur l'insecte cible
      */
    inline Insecte * getCurrentTarget() const { return this->currentTarget; }

    /*!
      * Methode activant le tir de la tour et donc le timer du projectile
      * \param state true = la tour tire    false = la tour arrete de tirer
      */
    void setIsShooting(bool state);

public slots:
    /*!
      * Slot creant le projectile lors du tir
      */
    void shootTarget();

    /*!
      * Slot engendrant les degats lors du crash d'une guepe sur les insectes rampant a portee
      * \param degats les degats a causer
      * \param *g la guepe qui se crash
      */
    void degatsCrashGuepe(double degats,Guepe *g);
};
}

#endif // DEFENSE_H
