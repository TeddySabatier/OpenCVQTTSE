
#include <qopengl.h>
#include <GL/glu.h>
#include <QDebug>
#include <QImage>

// Classe dediee pour la gestion de la voiture
class Spacebase
{
public:
    // Constructeur avec parametres
    Spacebase(float coordinates_[3]);

    // Destructeur
    ~Spacebase();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;

    //Met a jours les coordonnées
    void updateCoordinates(float coordinates_[3]);
    //Coordonnées de la base
    float coordinates[3];//x,y,z
    //Rotations de la base
    float rotation[4];//angle,x,y,z
    //Rayon de la base
    float rayon_base;
    //Quadrique pour dessiner la bases
    GLUquadric* mySpacebase;
};



