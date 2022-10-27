#include <qopengl.h>
#include <GL/glu.h>
#include <QDebug>
#include <QImage>
// Classe dediee pour la gestion de la voiture
class Spacestars
{
public:
    // Constructeur avec parametres
    Spacestars();

    // Destructeur
    ~Spacestars();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;
    //Quadrique pour afficher l'espace
    GLUquadric* spaceQ;
};
