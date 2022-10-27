#include <qopengl.h>
#include <GL/glu.h>
#include <QDebug>
#include <QImage>
// Classe dediee pour la gestion de la voiture
class Spaceship
{
public:
    // Constructeur avec parametres
    Spaceship();

    // Destructeur
    ~Spaceship();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;

    //Quadrique pour afficher le vaisseau
    GLUquadric* mySpaceship;
};
