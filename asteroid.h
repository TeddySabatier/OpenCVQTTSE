#include <qopengl.h>
#include <GL/glu.h>
#include <QDebug>
#include <QImage>
// Classe dediee pour la gestion de la voiture
class Asteroid
{
public:
    // Constructeur avec en paramètre la taille de l'astéroid
    Asteroid(float taille_asteroid_);
    // Constructeur de copie pour pouvoir créer un astéroid à partir d'un autre
    Asteroid(const Asteroid &Copy);
    // Destructeur
    ~Asteroid();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed) const;
    //Flottant contenant la taille de l'asteroid
    float taille_asteroid;
    //Flottant contenant le nombre de vertex que l'astéroid aura (Effet de texture)
    float nb_vertex;
    //Quadrique pour déssiner les sphères
    GLUquadric* asteroidQ;
};
