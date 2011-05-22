#include "fichier.h"

namespace TOWERDEFENSE{

Fichier::Fichier()
{
    carte = new int*[16];
    vague = new double*[20];

    //initialisation de la carte
    for(int i = 0; i < 16; ++i)
    {
        carte[i] = new int[16];
        for(int j = 0; j < 16; ++j)
        {
            carte[i][j] = 0;
        }
    }

    //initialisation des vagues
    for(int i = 0; i < 20; ++i)
    {
        vague[i] = new double[5];
        for(int j = 0; j < 5; ++j)
        {
            vague[i][j] = 0;
        }
    }
}

Fichier::~Fichier()
{
    delete[] carte;
    delete[] vague;
}

int** Fichier::getCarte()const { return carte; }

double** Fichier::getVague()const { return vague; }

bool Fichier::chargerCarte(const std::string & chemin)
{
    std::ifstream fichier(chemin.c_str(), std::ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
            int i(0),j(0);

            while(!fichier.eof())
            {
                if(i == 16)
                {
                    ++j;
                    i = 0;
                }
                fichier >> carte[i][j];
                ++i;
            }

            fichier.close();  // on ferme le fichier
            return true;
        }
        else  return false;
}

bool Fichier::chargerVague(const std::string &chemin)
{
    std::ifstream fichier(chemin.c_str(), std::ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
            int l(0),c(0);
            int nbClassesEnnemis(0);
            int numeroVague(1);
            bool debutVague(false);
            std::string ligne;
            QString insecte;
            QString nombre;

            while(getline(fichier, ligne))
            {
                vague[l][c] = numeroVague;

                for(unsigned int j = 0; j < ligne.size(); ++j)
                {
                    if(debutVague)
                    {
                        while(ligne[j] != ':')
                        {
                            insecte.push_back(QChar(ligne[j]));
                            j++;
                        }
                        c++;

                        if(insecte == "fourmi")
                        {
                            vague[l][c] = 1;
                        }
                        else if(insecte == "cafard")
                        {
                            vague[l][c] = 2;
                        }
                        else if(insecte == "guepe")
                        {
                            vague[l][c] = 3;
                        }
                        else if(insecte == "moustique")
                        {
                            vague[l][c] = 4;
                        }
                        c++;
                        insecte.clear();
                        debutVague = false;
                        j++;
                    }

                    if(ligne[j] != ':' && ligne[j] != ';' && nbClassesEnnemis > 0)
                    {
                        nombre.push_back(QChar(ligne[j]));
                    }
                    else if(ligne[j] == ':' && nbClassesEnnemis > 0)
                    {
                        vague[l][c] = nombre.toDouble();
                        nombre.clear();
                        c++;
                    }

                    if(ligne[j] == ';')
                    {
                        if(nbClassesEnnemis > 0)
                        {
                            vague[l][c] = nombre.toDouble();
                            nombre.clear();
                            l++;
                            c = 0;
                            vague[l][c] = numeroVague;
                        }
                        nbClassesEnnemis++;
                        debutVague = true;
                    }
                }
                vague[l][c] = nombre.toDouble();
                nombre.clear();

                nbClassesEnnemis = 0;
                numeroVague++;
                l++;
                c = 0;
            }

            fichier.close();  // on ferme le fichier
            return true;
        }
        else  return false;
}

int Fichier::NombreVagues() const
{
    int i(0);

    while(vague[i][0] != 0) ++i;

    return i;
}

}
