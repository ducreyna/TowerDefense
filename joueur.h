#ifndef JOUEUR_H
#define JOUEUR_H

#include <QObject>

namespace TOWERDEFENSE{

class Joueur :public QObject
{
    Q_OBJECT
private:
    int argent;
    int vies;

public:
    Joueur(const int vies=10, const int argent=50);

    int getArgent()const;
    int getVies()const;

public slots:
    void gagnerArgent();
    void perdreVie();
    void achatTour(int prix);
    void venteTour(int gain);

signals:
    void argentModifie(int);
    void viesModifiees(int);
    void finDuJeu();
};
}

#endif // JOUEUR_H
